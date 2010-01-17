package SS::Builder;

use strict;
use Helpers;
use Param::Set;

use SS::Linear::Structure;
use SS::Linear::RIBOSUM;
use SS::Affine::Structure;
use SS::Affine::RIBOSUM;

sub new
{
	my ( $class, %args ) = @_;

	my $self = {};

	if    ( defined $args{'linear'} and defined $args{'structure'} )
	{
		$self->{'ss'} = SS::Linear::Structure->new();
	}
	elsif ( defined $args{'linear'} and defined $args{'ribosum'} )
	{
		$self->{'ss'} = SS::Linear::RIBOSUM->new();
	}
	elsif ( defined $args{'affine'} and defined $args{'structure'} )
	{
		$self->{'ss'} = SS::Affine::Structure->new();
	}
	elsif ( defined $args{'affine'} and defined $args{'ribosum'} )
	{
		$self->{'ss'} = SS::Affine::RIBOSUM->new();
	}
	else
	{
		return undef;
	}

	bless( $self, $class );

	return $self;
}

sub build_ss
{
	my ( $class, $ps ) = @_;

	$class->{'ss'}->init_delta();

	$class->{'ss'}->init_paramset($ps);
	
	$ps->parse();
	
	$class->{'ss'}->convert_paramset();
	
	return $class->{'ss'};
}

1;
