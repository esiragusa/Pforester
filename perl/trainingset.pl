#!/usr/bin/perl -w

use lib "lib";
use lib "perl/lib";

use strict;
use PerlIO;
use List::Util qw(shuffle);
use Data::Dumper;

main(@ARGV);

sub main
{
	my ( $dataset, $trainingset, $cutoff ) = @_;

	unless ( defined $dataset and defined $trainingset)
	{
		help();
		exit 1;
	}

	my $ds = dataset_load($dataset);
	die $! unless defined $ds;

	my $ts = trainingset_pairwise($ds);
	die $! unless trainingset_cutoff($ts, $cutoff);
	die $! unless trainingset_write($ts, $dataset, $trainingset);

	exit 0;
}

sub help
{
	print STDERR "usage: $0 <dataset dir> <trainingset file> [cutoff percent]\n";
}

sub dataset_load
{
	my ($dir) = @_;
	
	my $dataset = { map { $_ => [ listdir($dir.'/'.$_) ] } listdir($dir) };
	
	return $dataset;
}

sub trainingset_pairwise
{
	my ($ds) = @_;

	my $ts = { map { $_ => [] } keys %$ds };

	foreach my $family (keys %$ds)
	{
		print "Family $family: read " . (scalar @{$ds->{$family}}) * (scalar @{$ds->{$family}} -1) / 2 . " pairs\n";
		
		for ( my $i = 0; $i < $#{$ds->{$family}}; $i++ )
		{
			for ( my $j = $i+1; $j <= $#{$ds->{$family}}; $j++ )
			{
				push @{$ts->{$family}}, [ @{$ds->{$family}}[$i], @{$ds->{$family}}[$j] ];
			}
		}
	}
	
	return $ts;
}

sub trainingset_write
{
	my ( $ts, $dir, $file ) = @_;

	return unless open( my $fd, ">", $file );

	print $fd "# STOCKHOLM 1.0\n";

	foreach my $family (keys %$ts)
	{
		print $fd "\n\n#==== Family $family ====\n\n";

		foreach my $pair (@{$ts->{$family}})
		{
			print $fd "#=GF WT 1.0\n";
			
			foreach my $rna (@$pair)
			{
				my $ff = flatforest_read($dir.'/'.$family.'/'.$rna);
				print $fd $$ff[0] . "\n";
			}
			
			print $fd "//\n\n";	
		}
	}

	close($fd);

	return $ts;
}

sub trainingset_cutoff
{
	my ( $ts, $cutoff ) = @_;

	foreach my $family (keys %$ts)
	{
		$ts->{$family} = [ shuffle(@{$ts->{$family}}) ];

		$#{$ts->{$family}} = scalar @{$ts->{$family}} * $cutoff;

		print "Family $family: selected " . scalar @{$ts->{$family}} . " pairs\n";
	}

	return $ts;
}

sub flatforest_read
{
	my ($file) = @_;

	my $ff = [];

	return $ff unless open( my $fd, "<", $file );

	while ( my $line = <$fd> )
	{
		chomp $line;
		
		next if ( $line =~ /^\s*\#.*$/ );	# skip comments and annotations
		next unless ( $line =~ /\S+/ );		# skip blank lines
		last if ( $line =~ /\/\/.*/ );		# return on //
		
		push( @$ff, $line );
	}

	close($fd);

	return $ff;
}

sub listdir
{
	my ($dir) = @_;
	
	opendir( my $dh, $dir) or die $!;	
	my @list = grep {!m/^\./} readdir($dh);
	closedir($dh);
	
	return @list;
}
