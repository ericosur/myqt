#!/usr/bin/env perl


my $file = "citieslist.txt";
my %hh = ();

sub list_tz()
{
    open my $fh, $file or die;
    while (<$fh>) {
        s/[\r\n]//;
        if ( m/([^\t]+)\t([^\t]+)\t([^\t]+)\t([^\t]+)\t([^\t]+)/ ) {
            #print $1,"\t",$4,"\n";
            $hh{$4} = 1;
        }
    }
    close $fh;
}

sub main()
{
    list_tz();
    foreach my $kk (sort(keys(%hh))) {
        print $kk,"\n";
    }
}

main;
