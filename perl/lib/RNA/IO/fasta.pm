package RNA::IO::fasta;

use strict;
use Data::Dumper;

use base qw(RNA::IO::IO);

use PerlIO;

sub read
{
	my ($class) = @_;
	
	return undef unless open ( my $ct, "<", $class->{'file'} );
	
	my @structures = ();

	while( my $structure = $class->_read_header( $ct ) )
	{
		$class->_read_structure( $ct, $structure );
		
		push( @structures, $structure );	
	}
	
	close( $ct );
	
	return @structures;
}

sub write
{
	my ( $class, @structures ) = @_;

	return unless $#structures >= 0;

	open ( my $ct, ">", $class->{'file'} );

	foreach my $structure (@structures)
	{
		$class->_write_header( $ct, $structure );
		$class->_write_structure( $ct, $structure );
	}
	
	close ( $ct );
}

sub _read_header
{
	my ( $class, $ct ) = @_;
	
	while( my $line = <$ct> )
	{
		next unless $line =~ /^>\s*(\w*)/;
		
		my $structure = RNA::Structure->new();
		
		$structure->set_name( $1 );
		
		return $structure;
	}
	
	return undef;	
}

sub _write_header
{
	my ( $class, $ct, $structure ) = @_;
	
	print $ct '> '. $structure->get_name() ."\n";
}

sub _read_structure
{
	my ( $class, $ct, $structure ) = @_;

	my $ps = <$ct>;
	my $ss = <$ct>;
	
	chomp $ps;
	chomp $ss;
	
	$structure->set_primary_structure( $class->_ungapped($ps) );
	$structure->set_secondary_structure( $class->_ungapped($ss) );
}

sub _write_structure
{
	my ( $class, $ct, $structure ) = @_;
	
	print $ct $structure->get_primary_structure() ."\n";
	print $ct $structure->get_secondary_structure() ."\n";	
	print $ct "\n";
}

1;
