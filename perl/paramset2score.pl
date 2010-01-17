#!/usr/bin/perl -w

use lib "lib";
use lib "perl/lib";

use strict;

use Getopt::Long;
use SS::Builder;


my $argh = {};

GetOptions( $argh, 'linear', 'affine', 'structure', 'ribosum', 'ifile=s' );

main($argh);

sub main
{
	my ($argh) = @_;
	
	unless ( ( defined $argh->{'linear'}    or defined $argh->{'affine'}  ) and
			 ( defined $argh->{'structure'} or defined $argh->{'ribosum'} ) )
	{
		_help();
		exit 1;
	}

	my $ifile = delete $argh->{'ifile'};
	
	my $ps = Param::Set->new( 'file' => $ifile );

	my $builder = SS::Builder->new( %$argh );
	my $ss = $builder->build_ss( $ps );
	
	print STDOUT $ss->to_string() ."\n";
	
	exit 0;
}

sub _help
{
	print STDERR "usage: $0 {--linear|--affine} {--structure|--ribosum} -ifile paramset\n";
}
