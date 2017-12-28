#!/usr/bin/env perl

use strict;
use JSON;
use Data::Dumper;

# read setting from setting.json
my $setting_file = "setting.json";

# two settings as global variables
my $data_file;
my $item_number;

sub read_file_into_str($)
{
    my $fn = shift;
    open my $fh, $fn or die;
    my $str;
    while (<$fh>) {
        $str = $str . $_;
    }
    close $fh;
    return $str;
}

sub read_setting()
{
    my $str = read_file_into_str($setting_file);
    my $j = decode_json($str);
    #print Dumper($j);

    my $tmp = $j->{'common'}->{'data_file'};
    $data_file = defined($tmp) ? $tmp : "strings.txt";

    $tmp = $j->{'perl'}->{'item_number'};
    $item_number = defined($tmp) ? $tmp : 10;
}

sub gen_datafile()
{
    my $str;
    open my $ofh, "> $data_file" or die;
    for (1..$item_number) {
        # '09' + '12345678'
        $str = sprintf("09%08d\n", int(rand(99999999)));
        print $ofh $str;
    }
    close $ofh;
}

sub main()
{
    read_setting();
    #printf("f:%s\ni:%d\n", $data_file, $item_number);
    printf("output to: %s\n", $data_file);
    gen_datafile();
}

main();
