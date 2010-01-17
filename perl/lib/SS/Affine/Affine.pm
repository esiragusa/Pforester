package SS::Affine::Affine;

use base SS::SS;

sub init_delta
{
	my ( $class ) = @_;
	
	$class->{'delta'}->{'P relabel'} =
	[
		{ 'name' => 'sigma_nn', 'col' => 1 },
		{ 'name' => 'sigma_pn', 'col' => 1 },
		{ 'name' => 'sigma_sn', 'col' => 1 },
		{ 'name' => 'sigma_ps', 'col' => 1 },
		{ 'name' => 'sigma_np', 'col' => 1 },
		{ 'name' => 'sigma_ns', 'col' => 1 },
		{ 'name' => 'sigma_sp', 'col' => 1 },		
	];

	$class->{'delta'}->{'P open'} =
	[
		{ 'name' => 'sigma_nn', 'col' => 2 },
		{ 'name' => 'sigma_nn', 'col' => 3 },
		{ 'name' => 'sigma_pn', 'col' => 2 },
		{ 'name' => 'sigma_sn', 'col' => 2 },
		{ 'name' => 'sigma_np', 'col' => 3 },
		{ 'name' => 'sigma_ns', 'col' => 3 },
	];

	$class->{'delta'}->{'P extend'} =
	[
		{ 'name' => 'sigma_pn', 'col' => 3 },
		{ 'name' => 'sigma_sn', 'col' => 2 },
		{ 'name' => 'sigma_ps', 'col' => 2 },
		{ 'name' => 'sigma_ps', 'col' => 3 },
		{ 'name' => 'sigma_np', 'col' => 2 },
		{ 'name' => 'sigma_ns', 'col' => 2 },
		{ 'name' => 'sigma_sp', 'col' => 2 },
		{ 'name' => 'sigma_sp', 'col' => 3 },
	];

	$class->{'delta'}->{'B relabel'} =
	[
		{ 'name' => 'sigma_nn', 'col' => 4 },
		{ 'name' => 'sigma_pn', 'col' => 4 },
		{ 'name' => 'sigma_sn', 'col' => 4 },
		{ 'name' => 'sigma_ps', 'col' => 4 },
		{ 'name' => 'sigma_np', 'col' => 4 },
		{ 'name' => 'sigma_ns', 'col' => 4 },
		{ 'name' => 'sigma_sp', 'col' => 4 },		
	];

	$class->{'delta'}->{'B open'} =
	[
		{ 'name' => 'sigma_nn', 'col' => 5 },
		{ 'name' => 'sigma_nn', 'col' => 6 },
		{ 'name' => 'sigma_pn', 'col' => 5 },
		{ 'name' => 'sigma_sn', 'col' => 5 },
		{ 'name' => 'sigma_np', 'col' => 6 },
		{ 'name' => 'sigma_ns', 'col' => 6 },
	];

	$class->{'delta'}->{'B extend'} =
	[
		{ 'name' => 'sigma_pn', 'col' => 6 },
		{ 'name' => 'sigma_sn', 'col' => 5 },
		{ 'name' => 'sigma_ps', 'col' => 5 },
		{ 'name' => 'sigma_ps', 'col' => 6 },
		{ 'name' => 'sigma_np', 'col' => 5 },
		{ 'name' => 'sigma_ns', 'col' => 5 },
		{ 'name' => 'sigma_sp', 'col' => 5 },
		{ 'name' => 'sigma_sp', 'col' => 6 },
	];	
}

1;
