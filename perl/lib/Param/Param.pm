package Param::Param;

use strict;
use PerlIO;

sub new
{
	my ( $class, %args ) = @_;

	$args{'rows'} = 1 unless defined $args{'rows'};
	$args{'cols'} = 1 unless defined $args{'cols'};

	my $self = {
				'rows'		=> $args{'rows'},
				'cols'		=> $args{'cols'},
				'values'	=> []
	};

	bless( $self, $class );

	return $self;
}

sub parse
{
	my ( $class, $fd ) = @_;

	for ( 1 .. $class->{'rows'} )
	{
		if ( my $line = <$fd> )
		{
			chomp $line;
			
			my @line = split ( /\s+/, $line, $class->{'cols'} );

			push @{$class->{'values'}}, \@line; 
		}
		else
		{
			return 0;
		}
	}

	return 1;	
}

sub get
{
	my ( $class, %args ) = @_;

	$args{'row'} = 1 if $class->{'rows'} == 1; 
	$args{'col'} = 1 if $class->{'cols'} == 1;

	return undef unless ( defined $args{'row'} and defined $args{'col'} ); 

	return $class->{'values'}[$args{'row'}-1][$args{'col'}-1];
}

1;
