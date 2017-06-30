# Qt read json file example

[sample.json](./sample.json) is an answer from yahoo weather query, may use [w.sh](./w.sh) to query current weather status.

class ReadJson [header](./readjson.h), [source](./readjson.cpp)
demo how to read json from file and follow object
path to get value from json object.

## command line options for json

* You may use -h to see help messages.
* option -a will use "select \*" to query, default is
  "item.condition"
* option -d will turn on all debug message to check
* will output query result to "/tmp/a.json"


## Yahoo Weather

Refer to [yahoo weather](https://developer.yahoo.com/weather/#curl)

It returns Fahrenheit scale, so application will convert it to Celsius.

Using curl to query yahoo weather:
```bash
#!/bin/bash

/usr/bin/curl https://query.yahooapis.com/v1/public/yql \
    -d q='select * from weather.forecast where woeid in (select woeid from geo.places(1) where text="taipei")' \
    -d 'format=json'
```

## Appendix

### Letter for Celsius
U+2103 ==> ℃
U+00B0 U+0043 ==> °C

### Note
At sublime text 3, may use package 'Pretty Json' to rearrange json result.
