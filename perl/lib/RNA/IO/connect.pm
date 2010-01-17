package RNA::IO::connect;

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
		next unless $line =~ /^\s*(\d+)\s+ENERGY\s*=\s*(\d+)\s+(\S+)/;
		
		my $structure = RNA::Structure->new();
		
		$structure->set_length($1);
		$structure->set_name($3);
		
		return $structure;
	}
	
	return undef;	
}

sub _write_header
{
	my ( $class, $ct, $structure ) = @_;
	
	print $ct $structure->get_length() .' ENERGY = 0 '. $structure->get_name() ."\n";
}

sub _read_structure
{
	my ( $class, $ct, $structure ) = @_;

	my $length = $structure->get_length();
	
	my $pos = 1;
	while ( my $line = <$ct> )
	{
		last unless $pos <= $length;
		
		next unless $line =~ /^\s*(\d+)\s+(\w)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)/;
		
		$structure->set_basepair( $1, $5 );
		$structure->set_base( $1, $2 );

		$pos++;
	}
}

sub _write_structure
{
	my ( $class, $ct, $structure ) = @_;
	
	for ( my $pos1 = 1, my $length = $structure->get_length(); $pos1 <= $length; $pos1++ )
	{
		my $base = $structure->get_base( $pos1 );
		my $pos2 = $structure->get_basepair( $pos1 );
		
		print $ct $pos1 ."\t". $base ."\t". ($pos1-1) ."\t". ($pos1+1) ."\t". $pos2 ."\t". $pos1 ."\n";
	}
	
	print $ct "\n";
}

1;
