# Small test prototype with Qt

## command line options

-d                      toggle debug
-e [test string]        percent encoding
-f                      perform testdir
-t                      perform timezone tests
-h                      help message


## note

* [fake.ini](./fake.ini) is a smiple ini format file, used to test if no section name in ini file, how QSettings will read.

* [gettz.cpp](./gettz.cpp) and [gettz.h](./gettz.h) provides a function to retrieve current timezone from system.

* [gtz.cpp](./get.cpp) provides a function which only uses standard time() to get timezone info.
