package SS::Affine::Structure;

use base SS::Affine::Affine;

sub init_paramset
{
	my ( $class, $ps ) = @_;

	$class->{'ps'} = $ps;

	# Add params to ParamSet
	$class->{'ps'}->add_param( 'name' => 'sigma_nn', 'cols' => 6 );
	$class->{'ps'}->add_param( 'name' => 'sigma_pn', 'cols' => 6 );
	$class->{'ps'}->add_param( 'name' => 'sigma_sn', 'cols' => 6 );
	$class->{'ps'}->add_param( 'name' => 'sigma_ps', 'cols' => 6 );
	$class->{'ps'}->add_param( 'name' => 'sigma_np', 'cols' => 6 );
	$class->{'ps'}->add_param( 'name' => 'sigma_ns', 'cols' => 6 );
	$class->{'ps'}->add_param( 'name' => 'sigma_sp', 'cols' => 6 );
	$class->{'ps'}->add_param( 'name' => 'pmu' );
	$class->{'ps'}->add_param( 'name' => 'mu' );
	$class->{'ps'}->add_param( 'name' => 'tau' );

	return 1;
}

sub convert_paramset
{
	my ( $class ) = @_;

	my $mu  = $class->{'ps'}->get_param( 'name' => 'mu' )->get();
	my $pmu = $class->{'ps'}->get_param( 'name' => 'pmu' )->get();

	$class->{'values'}->{'bprep'}		= $class->convert_delta( 'P relabel',	1 );
	$class->{'values'}->{'bpindel'}		= $class->convert_delta( 'P extend',	1 );
	$class->{'values'}->{'bmatch'}		= $class->convert_delta( 'B relabel',	$mu );
	$class->{'values'}->{'brep'}		= $class->convert_delta( 'B relabel',	1-$mu );
	$class->{'values'}->{'bindel'}		= $class->convert_delta( 'B extend',	0.25 );
	$class->{'values'}->{'bpindelopen'}	= $class->convert_delta( 'P open',		1 );
	$class->{'values'}->{'bindelopen'}	= $class->convert_delta( 'B open',		1 );
	
	return 0;
}

1;
