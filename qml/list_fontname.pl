#!/usr/bin/env perl
#
# use fc-list to list all fonts and shows sorted font name
#

use strict;

my %hh = {};
my $ret = qx('fc-list');
my $cnt = 0;
while ( $ret =~ m/([^\n]+)\n/g ) {
    my $line = $1;
    #print $line,"\t";
    if ($line =~ m/:\s*([^:]+)\s*:/ ) {
        #print $1,"\n";
        $hh{$1} ++;
    }
    $cnt ++;
}

foreach my $kk (sort(keys(%hh))) {
    print $kk, "\n";
}
