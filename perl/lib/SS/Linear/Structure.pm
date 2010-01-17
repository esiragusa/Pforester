package SS::Linear::Structure;

use base SS::Linear::Linear;

sub init_paramset
{
	my ( $class, $ps ) = @_;

	$class->{'ps'} = $ps;

	# Add params to ParamSet
	$class->{'ps'}->add_param( 'name' => 'sigma', 'cols' => 6 );
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

	$class->{'values'}->{'bprep'}	= $class->convert_delta( 'P relabel',	1 );
	$class->{'values'}->{'bpindel'}	= $class->convert_delta( 'P extend',	1 );
	$class->{'values'}->{'bmatch'}	= $class->convert_delta( 'B relabel',	$mu );
	$class->{'values'}->{'brep'}	= $class->convert_delta( 'B relabel',	1-$mu );
	$class->{'values'}->{'bindel'}	= $class->convert_delta( 'B extend',	0.25 );

	return 1;
}

1;
