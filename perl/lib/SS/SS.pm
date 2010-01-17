package SS::SS;

use strict;
use Param::Set;

sub new
{
	my ( $class, %args ) = @_;

	my $self = {
					'ps'		=>	undef,
					'values'	=> {},
					'deltas'	=> {}
	};

	bless( $self, $class );

	return $self;
}

sub init_delta
{
}

sub init_paramset
{
}

sub convert_delta
{
	my ( $class, $name, $mul ) = @_;
	
	my $value = 0;

	foreach my $delta ( @{$class->{'delta'}->{$name}} )
	{
		$value += $class->{'ps'}->get_param( 'name' => $delta->{'name'} )->get( 'col' => $delta->{'col'} );
	}
	
	$value *= ( $mul / @{$class->{'delta'}->{$name}} );
	
	return log($value);
}

sub convert_paramset
{
}

sub to_string
{
	my ( $class ) = @_;

	my $string = '';
		
	while ( my ($name, $value) = each %{$class->{'values'}} )
	{
		$string .= "--$name $value ";
	}
	
	chop $string;
	
	return $string;
}

1;
