package RNA::IO::stockholm;

use strict;
use Data::Dumper;

use base qw(RNA::IO::IO);

use Stockholm;

sub read
{
	my ($class) = @_;

	my $stk = Stockholm->from_file( $class->{'file'} );

	my @structures = ();

	foreach my $seqname ( @{$stk->{'seqname'}} )
	{
		my $ps = $stk->{'seqdata'}->{$seqname};
		my $ss = $stk->{'gr'}->{'SS'}->{$seqname};

		my $structure = RNA::Structure->new();
		$structure->set_name($seqname);
		$structure->set_primary_structure( $class->_ungapped($ps) );
		$structure->set_secondary_structure( $class->_ungapped($ss) );

		push( @structures, $structure );
	}
	
	return @structures;
}

sub write
{
	my ( $class, @structures ) = @_;

	return unless $#structures >= 0;
	
	my $stk = Stockholm->new();

	foreach my $structure (@structures)
	{
		my $seqname = $structure->get_name();
		$stk->add_row( $seqname, $structure->get_primary_structure() );
		$stk->{'gr'}->{'SS'}->{$seqname} = $structure->get_secondary_structure();
	}

	$stk->to_file( $class->{'file'}, 10000 );
}

1;
