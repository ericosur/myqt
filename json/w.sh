#!/bin/bash

/usr/bin/curl https://query.yahooapis.com/v1/public/yql \
    -d q='select * from weather.forecast where woeid in (select woeid from geo.places(1) where text="taipei") and u="c"' \
    -d 'format=json' 1>all.json 2>/dev/null

echo -e "output to all.json\n"

# pretty format and output to sample.json
python -m json.tool all.json > sample.json

