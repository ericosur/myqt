# help to clean extra lines/chars from git-diff result
#
#   for example
#
#+1f468-1f3fc-200d-2764-fe0f-200d-1f468-1f3fe
#
#   to
#1f468-1f3fc-200d-2764-fe0f-200d-1f468-1f3fe
#

use strict;

open my $fh, "diff.txt" or die;
while (<$fh>) {
    if ( m/^\+[0-9a-f]+/ ) {
        s/^\+(.+)$/$1/;
        print;
    }
}
close $fh;
