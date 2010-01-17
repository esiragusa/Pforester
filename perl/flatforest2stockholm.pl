#!/usr/bin/perl -w

use lib "lib";
use lib "perl/lib";

use strict;
use Stockholm;

main(@ARGV);

sub main
{
	my (@files) = @_;

	if ( $#files != 1 )
	{
		_help();
		return 1;
	}

	my $ifile = shift @files;
	my $ofile = shift @files;


	my ( $ff, $score ) = _read_ff($ifile);
	my $consensus_ff = _build_consensus_ff($ff);
	
	my $stk = [];
	foreach my $ff_ (@$ff)
	{
		push ( @$stk, _build_stk( $consensus_ff, $ff_ ) );
	}
	
	_write_stk( $ofile, $stk, $score );
	
	exit 0;
}

sub _help
{
	print STDERR "usage: $0 flatforest stockholm\n";
}

sub _read_ff
{
	my ($file) = @_;

	my $stk = Stockholm->from_file( $file );

	my @ff;

	foreach my $seqname ( @{$stk->{'seqname'}} )
	{
		my $ff = {
					'name'		=> $seqname,
					'length'	=> length($stk->{'seqdata'}->{$seqname}),
					'ff'		=> [ split( '', $stk->{'seqdata'}->{$seqname} ) ] 
		};

		push( @ff, $ff );
	}
	
	my $score = $stk->get_gf ('SC');
	
	return ( \@ff, $score );
}

sub _build_consensus_ff
{
	my ($ff) = @_;
	
	my @consensus_ff;
	
	my $length = ${@$ff}[0]->{'length'};
	
	for ( my $col=0; $col<$length; $col++ )
	{
		push( @consensus_ff, _get_consensus_col( $ff, $col ) );  
	}
	
	return \@consensus_ff;
}

sub _get_consensus_col
{
	my ( $ff, $i ) = @_;
	
	foreach my $ff_ (@$ff)
	{
		if    ( $ff_->{'ff'}[$i] eq '(' )
		{
			return '(';
		}
		elsif ( $ff_->{'ff'}[$i] eq ')' )
		{
			return ')';
		}
	}
	
	return 'B';
}

sub _build_stk
{
	my ( $consensus_ff, $ff ) = @_;
	
	my $stk = {
		'name'	=> $ff->{'name'},
		'ps'	=> '',
		'ss'	=> '',
	};
	
	_ff_to_stk( $consensus_ff, $ff, $stk, 0 );
	
	return $stk;
}

sub _ff_to_stk
{
	my ( $consensus_ff, $ff, $stk, $i ) = @_;
	
	while ( $i < $ff->{'length'} )
	{
		if    ( ${@$consensus_ff}[$i] eq '(' )
		{
			$stk->{'ss'} .= ${@{$ff->{'ff'}}}[$i];
			$stk->{'ps'} .= ${@{$ff->{'ff'}}}[$i+1];
			
			$i = _ff_to_stk( $consensus_ff, $ff, $stk, $i+2 ) +1;			
		}
		elsif ( ${@$consensus_ff}[$i] eq ')' )
		{
			chop $stk->{'ss'};
			$stk->{'ss'} .= ${@{$ff->{'ff'}}}[$i];
			
			last;
		}
		else
		{
			if ( ${@{$ff->{'ff'}}}[$i] eq '-' )
			{
				$stk->{'ss'} .= '-';
				$stk->{'ps'} .= '-';			
			}
			else
			{
				$stk->{'ss'} .= '.';
				$stk->{'ps'} .= ${@{$ff->{'ff'}}}[$i];
			}
			$i++;
		}
	}
	
	return $i;
}

sub _write_stk
{
	my ( $file, $stk, $score ) = @_;
	
	my $stkf = Stockholm->new();

	foreach my $stki (@$stk)
	{
		my ($name) = split( '/', $stki->{'name'}, 2 );
		
		$stkf->add_row( $name, $stki->{'ps'} );
		$stkf->{'gr'}->{'SS'}->{$name} = $stki->{'ss'};
	}

	$stkf->add_gf( 'SC', $score );

	$stkf->to_file( $file, 10000 );
}
