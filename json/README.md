# Qt read json file example

Use [w.sh](./w.sh) to query yahoo weather for current weather status, output as:
  * [all.json](./all.json) - compact json object
  * [sample.json](./sample.json) - indented json object for reading

class ReadJson [header](./readjson.h), [source](./readjson.cpp)
demo how to read json from file and follow object
path to get value from json object.


## command line options for json

* option -h to see help messages
* option -a will use "select \*" to query, default is
  "item.condition"
* option -d will turn on all debug message to check
* will output query result to "/tmp/a.json"
* option -f to specify json file to read


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

* At sublime text 3, may use package 'Pretty Json' to rearrange json result.
* Use python json.tool
```
$ python -mjson.tool compact.json > indented.json
```

### all.json

copy / paste the following line if no network access

```
{"query":{"count":1,"created":"2017-09-26T03:24:19Z","lang":"en-US","results":{"channel":{"units":{"distance":"km","pressure":"mb","speed":"km/h","temperature":"C"},"title":"Yahoo! Weather - Taipei City, Taipei City, TW","link":"http://us.rd.yahoo.com/dailynews/rss/weather/Country__Country/*https://weather.yahoo.com/country/state/city-2306179/","description":"Yahoo! Weather for Taipei City, Taipei City, TW","language":"en-us","lastBuildDate":"Tue, 26 Sep 2017 11:24 AM CST","ttl":"60","location":{"city":"Taipei City","country":"Taiwan","region":" Taipei City"},"wind":{"chill":"93","direction":"250","speed":"11.27"},"atmosphere":{"humidity":"61","pressure":"33559.12","rising":"0","visibility":"25.91"},"astronomy":{"sunrise":"5:44 am","sunset":"5:46 pm"},"image":{"title":"Yahoo! Weather","width":"142","height":"18","link":"http://weather.yahoo.com","url":"http://l.yimg.com/a/i/brand/purplelogo//uh/us/news-wea.gif"},"item":{"title":"Conditions for Taipei City, Taipei City, TW at 10:00 AM CST","lat":"25.086","long":"121.560997","link":"http://us.rd.yahoo.com/dailynews/rss/weather/Country__Country/*https://weather.yahoo.com/country/state/city-2306179/","pubDate":"Tue, 26 Sep 2017 10:00 AM CST","condition":{"code":"30","date":"Tue, 26 Sep 2017 10:00 AM CST","temp":"33","text":"Partly Cloudy"},"forecast":[{"code":"30","date":"26 Sep 2017","day":"Tue","high":"35","low":"27","text":"Partly Cloudy"},{"code":"30","date":"27 Sep 2017","day":"Wed","high":"36","low":"26","text":"Partly Cloudy"},{"code":"4","date":"28 Sep 2017","day":"Thu","high":"33","low":"27","text":"Thunderstorms"},{"code":"47","date":"29 Sep 2017","day":"Fri","high":"31","low":"26","text":"Scattered Thunderstorms"},{"code":"47","date":"30 Sep 2017","day":"Sat","high":"33","low":"26","text":"Scattered Thunderstorms"},{"code":"30","date":"01 Oct 2017","day":"Sun","high":"34","low":"26","text":"Partly Cloudy"},{"code":"34","date":"02 Oct 2017","day":"Mon","high":"35","low":"26","text":"Mostly Sunny"},{"code":"39","date":"03 Oct 2017","day":"Tue","high":"31","low":"26","text":"Scattered Showers"},{"code":"11","date":"04 Oct 2017","day":"Wed","high":"30","low":"25","text":"Showers"},{"code":"30","date":"05 Oct 2017","day":"Thu","high":"32","low":"25","text":"Partly Cloudy"}],"description":"<![CDATA[<img src=\"http://l.yimg.com/a/i/us/we/52/30.gif\"/>\n<BR />\n<b>Current Conditions:</b>\n<BR />Partly Cloudy\n<BR />\n<BR />\n<b>Forecast:</b>\n<BR /> Tue - Partly Cloudy. High: 35Low: 27\n<BR /> Wed - Partly Cloudy. High: 36Low: 26\n<BR /> Thu - Thunderstorms. High: 33Low: 27\n<BR /> Fri - Scattered Thunderstorms. High: 31Low: 26\n<BR /> Sat - Scattered Thunderstorms. High: 33Low: 26\n<BR />\n<BR />\n<a href=\"http://us.rd.yahoo.com/dailynews/rss/weather/Country__Country/*https://weather.yahoo.com/country/state/city-2306179/\">Full Forecast at Yahoo! Weather</a>\n<BR />\n<BR />\n<BR />\n]]>","guid":{"isPermaLink":"false"}}}}}}
```
