package SS::Linear::Linear;

use base SS::SS;

sub init_delta
{
	my ( $class ) = @_;
	
	$class->{'delta'}->{'P relabel'} =
	[
		{ 'name' => 'sigma', 'col' => 1 }
	];

	$class->{'delta'}->{'P open'} =
	[
	];

	$class->{'delta'}->{'P extend'} =
	[
		{ 'name' => 'sigma', 'col' => 2 },
		{ 'name' => 'sigma', 'col' => 3 }
	];

	$class->{'delta'}->{'B relabel'} =
	[
		{ 'name' => 'sigma', 'col' => 4 }
	];

	$class->{'delta'}->{'B open'} =
	[
	];

	$class->{'delta'}->{'B extend'} =
	[
		{ 'name' => 'sigma', 'col' => 5 },
		{ 'name' => 'sigma', 'col' => 6 }
	];	
}


1;
