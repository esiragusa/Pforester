package RNA::IO::IO;

use strict;
use Data::Dumper;

#use base qw(RNA::IO);
use RNA::Structure;

sub new
{
	my ( $class, %args ) = @_;

	return undef unless defined $args{-file};

	my $self = { 'file' => $args{-file} };

	bless( $self, $class );

	return $self;
}

sub read
{
	my ($class) = @_;

	return [];
}

sub write
{
	my ( $class, @structures ) = @_;

}

sub _ungapped
{
	my ( $class, $seq ) = @_;

	$seq =~ tr/\-\_//d;
	
	return $seq;
}

1;
