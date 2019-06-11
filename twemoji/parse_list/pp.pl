#!/usr/bin/env perl
#

use strict;

my $cnt = 0;
my $aa = 0;
my $bb = 0;
my $cc = 0;

open my $fh2, "> cp2.txt" or die;
open my $fh4, "> cp4.txt" or die;
open my $fh5, "> cp5.txt" or die;
open my $fh, "list.txt" or die;
my $hh5 = {};

while (<$fh>) {
    $cnt ++;
    s/[\r\n]//;

    if ( m/^[0-9a-f]{2}\b/ ) {
        $aa ++;
        print $fh2 "$_\n";
    }
    if ( m/^[0-9a-f]{4}\b/ ) {
        $bb ++;
        print $fh4 "$_\n";
    }
    if ( m/^[0-9a-f]{5}\b/ ) {
        $cc ++;
        print $fh5 "$_\n";
    }
}
close $fh;
close $fh2;
close $fh4;
close $fh5;

printf("aa: %d\n", $aa);
printf("bb: %d\n", $bb);
printf("cc: %d\n", $cc);
printf("sum: %d\n", $aa+$bb+$cc);
