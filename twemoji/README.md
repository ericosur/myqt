# Readme

[TOC]

###### tags: ```emoji``` ```unicode``` ```qt``` ```qml``` ```twemoji```

## revision

2020-06-08 update image assests from twemoji (v13.0.0)

## note

Emoji images used in this application <img src="https://mirrors.creativecommons.org/presskit/buttons/88x31/png/by.png" width=88 height=31>
- Graphics licensed under CC-BY 4.0: https://creativecommons.org/licenses/by/4.0/
    - credit to: https://github.com/twitter/twemoji
    - none of images is modified or renamed

## files description

- **[mk_test.py](./mk_test.py)** helps to generates **test.json** that contains test strings array for display/test.

- **[test.json](./test.json)** for test appliaction to show string within json array

### steps for update twemoji image resource

* fetch twitter/twemoji from github
```
git clone https://github.com/twitter/twemoji.git
```

* copy latest images from twemoji

Note:
    - 2020-06-08: checking, there is v13.0.0 available
    - 2020-10-12: updated to v13.0.1
    - 2021-11-03: updated to v13.1.0


```
cd $TWEMOJI_DIR
git checkout v13.1.0
cp -f $TWEMOJI_DIR/assets/72x72/*.png $TOP/72x72/
```

* to generate **emoji.qrc** and **parse_list/list.txt** from 72x72/

```
python3 mkqrc.py
```
  It will output __emoji.qrc__ and __parse_list/list.txt__.

* ```cd $TOP/parse_list/``` and run __pp.pl__.

* use git diff to generate test.json (automatically)
    * execute **[mk_test.py](./mk_test.py)**

```bash
$ python3 mk_test.py
```
then you get a refreshed test.json

```base
cd parse_list/
python3 mk_seqjson.py
```

will update *seq.json*.

## examples

