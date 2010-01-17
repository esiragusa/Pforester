package RNA::IO::flatforest;

use strict;
use Data::Dumper;

use base qw(RNA::IO::IO);

use Stockholm;

sub read
{
	my ($class) = @_;

	my $stk = Stockholm->from_file( $class->{'file'} );

	my @structures = ();
	
	foreach my $seqname ( @{ $stk->{'seqname'} } )
	{
		my $ff = $class->_ungapped( $stk->{'seqdata'}->{$seqname} );
		
		my $structure = RNA::Structure->new();
		$structure->set_name($seqname);
		
		my @stack = ();
		
		my $pos = 0;
		foreach my $c ( split( //, $ff ) )
		{		
			if ( $c =~ /(\(|\<|\{)/ )
			{
				push( @stack, $pos+1 );
			}
			elsif ( $c =~ /(\)|\>|\})/ )
			{
				$structure->set_basepair( $pos, pop(@stack) );
			}
			else
			{
				$pos++;
				$structure->set_base( $pos, $c );
				$structure->del_basepair( $pos, $pos );
			}
		}
		
		print STDERR "Unbalanced FlatForest\n" if( scalar @stack );
		
		$structure->set_length( $pos-1 );
		
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
		
		my $ff = '';
		
		for ( my $pos1 = 1; $pos1 <= $structure->get_length(); $pos1++ )
		{
			my $c = $structure->get_base( $pos1 );
			my $pos2 = $structure->get_basepair( $pos1 );
			
			if ( $pos2 == 0 )
			{
				$ff .= $c;
			}
			elsif ( $pos1 < $pos2 )
			{
				$ff .= '(' . $c;
			}
			elsif ( $pos1 > $pos2 )
			{
				$ff .= $c . ')';				
			}
		}
		
		$stk->add_row( $seqname, $ff );
	}

	$stk->to_file( $class->{'file'}, 10000 );
}

1;
