package Helpers;

use strict;
#use Module::Load;

#sub load_module
#{
#	my ($package) = @_;
#	
#	eval { load $package; };
#
#	if ($@)
#	{
#		print $@;
#		return 0;
#	}
#
#	return 1;
#}

sub load_module
{
	my ($package) = @_;

	$package =~ s/::/\//g;
	$package .= '.pm';

	eval { require $package; };
	if ($@)
	{
		print $@;
		return 0;
	}

	return 1;
}

1;
