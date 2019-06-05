#!/usr/bin/env perl
#

use strict;

open my $fh, "list.txt" or die;
while (<$fh>) {
    s/[\r\n]//;
    if ( m/^2764-fe0f/ ) {
        print;
    }
}
close $fh;
