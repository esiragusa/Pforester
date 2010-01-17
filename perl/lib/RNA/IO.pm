package RNA::IO;

use strict;
use Helpers;


sub new
{
	my ( $class, %args ) = @_;

	return undef unless defined $args{-file};
	
	$args{-format} = $class->_guess_format( $args{-file} ) unless defined $args{-format}; 

	my $module = $class->_load_format_module( $args{-format} );

	return $module->new(%args) if defined $module;

	return undef;
}

sub _load_format_module
{
	my ( $class, $format ) = @_;
	
	if ( defined $format and $format ne 'IO' )
	{	
		my $module = $class . '::' . $format;
	
		return $module if Helpers::load_module($module);	
	};

	print STDERR "Format $format not supported\n";
	return undef;
}

sub _guess_format
{
	my $class = shift;
	return undef unless $_ = shift;

	return 'fasta'      if /\.(fasta|fast|fas|seq|fa|fsa|nt|aa|fna|faa)$/i;
	return 'connect'    if /\.(ct|ct2)$/i;
	return 'stockholm'  if /\.stk$/i;
	return 'flatforest' if /\.ff$/i;

	return 'genbank' if /\.(gb|gbank|genbank|gbk|gbs)$/i;
	return 'embl'    if /\.(embl|ebl|emb|dat)$/i;

	return undef;
}

1;
