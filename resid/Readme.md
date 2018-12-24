# Generation resid table for reference

## steps

* prepare a spreadsheet for locale, and its translation
  (please refer to translation.csv)

* run script to generate header and data file, it needs translation.csv at the
  current directory
```
$ python getcsv.py
```
  you will get:
  * strdef.h
  * strdef.ini
  * strdef.json

> NOTE: these generated files may not checked in code base

At host, copy strdef.[ini|json] to **/tmp/**, or it will complain no string id file.

* compile and execute
```
$ mkdir -p b; cd b
$ qmake ..
$ make -j
$ ln -s ../strdef.ini
$ ./resid
```
