#!/usr/bin/perl -w

use lib "lib";
use lib "perl/lib";

use strict;

use Getopt::Long;
use RNA;

my $argh = {};

GetOptions( $argh, 'iformat=s', 'ifile=s', 'oformat=s', 'ofile=s' );

main($argh);

sub main
{
	my ($argh) = @_;
	
	unless ( defined $argh->{'ifile'} and defined $argh->{'ofile'} )
	{
		_help();
		exit 1;
	}
	
	my $input  = RNA::IO->new( -format => $argh->{'iformat'}, -file => $argh->{'ifile'} );
	my $output = RNA::IO->new( -format => $argh->{'oformat'}, -file => $argh->{'ofile'} );

	exit 1 unless ( defined $input and defined $output );

	my @structures = $input->read();

	$output->write(@structures);

	exit 0;
}

sub _help
{
	print STDERR "usage: $0 [-iformat format] -ifile file [-oformat format] -ofile file\n";
}
