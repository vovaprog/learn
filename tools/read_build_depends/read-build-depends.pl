#!/usr/bin/perl

#read Build-Depends packages from deb package "control" file.

use strict;
use warnings;

my $file = $ARGV[0];

open my $info, $file or die "Could not open $file: $!";

my $result = "";
my $state = 0;

while( my $line = <$info>)
{
    if($line =~ /^Build-Depends:(.*)$/)
    {
        $state = 1;

        my $tail = $1; 
        
        my @words = split(/,/,$tail);        
        foreach my $word (@words)
        {
            $word =~ /^([^(]+)/;
            $result = "$result $1";    
        }
    }
    elsif($line =~ /^[A-Za-z-]+:(.*)$/)
    {
        $state = 0;
    }
    elsif($state != 0)
    {
        my @words = split(/,/,$line);        
        foreach my $word (@words)
        {
            $word =~ /^([^(]+)/;
            $result = "$result $1";    
        }        
    }
}

close $info;

if(($#ARGV+1 > 1) and ($ARGV[1] =~ /^install$/))
{
    system("apt-get -y install $result");    
}
else
{
    print "$result\n";
}

