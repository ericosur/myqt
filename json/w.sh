#!/bin/bash

OUTFILE=all.json
READABLE_FILE=sample.json
RT=999

function run_curl {
    /usr/bin/curl https://query.yahooapis.com/v1/public/yql \
        -d q='select * from weather.forecast where woeid in (select woeid from geo.places(1) where text="taipei") and u="c"' \
        -d 'format=json' 1>$OUTFILE 2>/dev/null ; RT=$?
}

function check_curl {
    if [ $RT -ne 0 ] ; then
        echo -e "\ncurl something wrong..."
        echo -e "curl return code: $RT\n"
    fi
}

function create_zero_byte_file {
    rm $OUTFILE
    touch $OUTFILE
}

function make_readable {
    # pretty format and output to sample.json
    python -m json.tool $OUTFILE > $READABLE_FILE \
        && echo -e "readable file $READABLE_FILE created"
}

rm $OUTFILE
run_curl
check_curl

if [ -e $OUTFILE ] ; then
    if [ -s $OUTFILE ] ; then
        echo -e "output to all.json"
        make_readable
    else
        echo "file size is zero"
    fi
else
    echo "no output file"
fi

