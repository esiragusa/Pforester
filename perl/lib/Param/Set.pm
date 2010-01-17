package Param::Set;

use strict;
use PerlIO;
use Param::Param;

sub new
{
	my ( $class, %args ) = @_;

	return undef unless defined $args{'file'};

	my $self = {
					'file'	 => $args{'file'},
					'params' => [],
					'names'  => {}
	};

	bless( $self, $class );

	return $self;
}

sub add_param
{
	my ( $class, %args ) = @_;

	my $name = delete $args{'name'} or return 0;
	
	push @{ $class->{'params'} }, Param::Param->new( %args );
	$class->{'names'}->{$name} = @{$class->{'params'}}-1;
	
	return 1;
}

sub get_param
{
	my ( $class, %args ) = @_;
	
	if ( defined $args{'name'} )
	{
		my $index = $class->{'names'}->{$args{'name'}};
		return $class->{'params'}[$index];
	}
	elsif ( defined $args{'index'} )
	{
		my $index = $args{'index'}-1;
		return $class->{'params'}[$index];
	}
	else
	{
		return undef;
	}
}

sub parse
{
	my ( $class ) = @_;

	return 0 unless open( my $fd, "<", $class->{'file'} );

	foreach my $param ( @{ $class->{'params'} } )
	{
		$param->parse($fd);
	}

	close($fd);

	return 1;
}


1;
