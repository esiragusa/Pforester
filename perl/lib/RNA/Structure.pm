package RNA::Structure;

use strict;

sub new
{
	my ( $class, %args ) = @_;

	my $self = {
				 'name'     => undef,
				 'base'  	=> [],
				 'basepair' => [],
				 'length'   => 0
	};

	bless( $self, $class );

	return $self;
}

sub get_name
{
	my ($class) = @_;

	return $class->{'name'};
}

sub set_name
{
	my ( $class, $name ) = @_;

	$class->{'name'} = $name;
}

sub get_length {
	my ($class) = @_;

	return $class->{'length'};	
}

sub set_length {
	my ( $class, $length ) = @_;

	$class->{'length'} = $length;	
}

sub get_primary_structure
{
	my ($class) = @_;
		
	return join( '', @{ $class->{'base'} } );
}

sub set_primary_structure
{
	my ( $class, $ps ) = @_;

	$class->set_length( length($ps) );
	
	$class->{'base'} = [ split( //, $ps ) ];
	
	$class->del_secondary_structure();
}

sub get_secondary_structure
{
	my ($class) = @_;
	
	my $ss = '';

	my $pos1 = 0;
	foreach my $pos2 ( @{ $class->{'basepair'} } )
	{
		$pos1++;
		
		if ($pos2 == 0)
		{
			$ss .= '.';
		}
		elsif ($pos1 < $pos2)
		{
			$ss .= '(';
		}
		elsif ($pos1 > $pos2)
		{
			$ss .= ')';
		}
	}
	
	return $ss;
}

sub set_secondary_structure
{
	my ( $class, $ss ) = @_;

	return unless length($ss) == $class->get_length();
	
	$class->del_secondary_structure();

	my @stack = ();

	my $pos = 0;
	foreach my $c ( split( //, $ss ) )
	{
		$pos++;
		
		if ( $c =~ /(\(|\<|\{)/ )
		{
			push( @stack, $pos );
		}
		elsif ( $c =~ /(\)|\>|\})/ )
		{
			$class->set_basepair( $pos, pop(@stack) );
		}
		else
		{
			$class->del_basepair( $pos, $pos );
		}
	}
}

sub del_secondary_structure
{
	my ($class) = @_;

	$class->{'basepair'} = [];
}

sub get_basepair
{
	my ( $class, $pos ) = @_;

	return $class->{'basepair'}[ $pos - 1 ];
}

sub set_basepair
{
	my ( $class, $pos1, $pos2 ) = @_;
	
	if ( $pos2 > 0 )
	{
		$class->{'basepair'}[ $pos1 - 1 ] = $pos2;
		$class->{'basepair'}[ $pos2 - 1 ] = $pos1;
	}
	else
	{
		$class->{'basepair'}[ $pos1 - 1 ] = 0;
	}
}

sub del_basepair
{
	my ( $class, $pos1, $pos2 ) = @_;

	$class->{'basepair'}[ $pos1 - 1 ] = 0;
	$class->{'basepair'}[ $pos2 - 1 ] = 0;
}

sub get_base
{
	my ( $class, $pos ) = @_;

	return $class->{'base'}[ $pos - 1 ];
}

sub set_base
{
	my ( $class, $pos, $val ) = @_;

	$class->{'base'}[ $pos - 1 ] = $val;
}

1;
