# readme

## samples

This projects contains two parts, one is perl script "gen_testdata.pl" and the
other is "qtline". Both reads settings from setting.json for input/output file.

qtline demos how to read lines from a text file.

## settings

**.common.data_file** is specified data file
Perl script will read **.perl.item_number**, generate lines of
numbers as specified.

```
{
    "common": {
        "data_file": "strings.txt"
    },
    "perl": {
        "item_number": 20
    }
}
```

## first pass

run perl script to generate data file

```
$ perl gen_testdata.pl
```

## 2nd pass
run qtline to read data file
```
$ ./qtline
```
