#!/bin/bash

/usr/bin/curl https://query.yahooapis.com/v1/public/yql \
    -d q='select * from weather.forecast where woeid in (select woeid from geo.places(1) where text="taipei")' \
    -d 'format=json'

echo -e "\n"
