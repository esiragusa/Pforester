package SS::Linear::RIBOSUM;

use base SS::Linear::Linear;

sub init_paramset
{
	my ( $class, $ps ) = @_;

	$class->{'ps'} = $ps;

	# Add params to ParamSet
	$class->{'ps'}->add_param( 'name' => 'sigma',	'cols' => 6 );
	$class->{'ps'}->add_param( 'name' => 'pmu' );
	$class->{'ps'}->add_param( 'name' => 'null',	'cols' => 4,	'rows' => 1 );
	$class->{'ps'}->add_param( 'name' => 'single',	'cols' => 4,	'rows' => 4 );
	$class->{'ps'}->add_param( 'name' => 'pair',	'cols' => 16,	'rows' => 16 );
	$class->{'ps'}->add_param( 'name' => 'tau' );

	return 1;
}

sub convert_paramset
{
	my ( $class ) = @_;
	
	my $pmu = $class->{'ps'}->get_param( 'name' => 'pmu' )->get();

	$class->{'values'}->{'bprep'}	= $class->convert_delta( 'P relabel',	1 );
	$class->{'values'}->{'bpindel'}	= $class->convert_delta( 'P extend',	1 );
	$class->{'values'}->{'bmatch'}	= $class->convert_delta( 'B relabel',	1 );
	$class->{'values'}->{'brep'}	= $class->convert_delta( 'B relabel',	1 );
	$class->{'values'}->{'bindel'}	= $class->convert_delta( 'B extend',	0.25 );

	return 1;
}

1;
