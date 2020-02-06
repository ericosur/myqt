# Readme

[TOC]

###### tags: ```emoji``` ```unicode``` ```qt``` ```qml``` ```twemoji```

## note

Emoji images used in this application <img src="https://mirrors.creativecommons.org/presskit/buttons/88x31/png/by.png" width=88 height=31>
- Graphics licensed under CC-BY 4.0: https://creativecommons.org/licenses/by/4.0/
    - credit to: https://github.com/twitter/twemoji
    - none of images is modified or renamed

## files description

- **[mk_test.py](./mk_test.py)** helps to generates **test.json** that contains test strings
  array for display/test.

- **[test.json](./test.json)** for test appliaction to show string within json array

### steps for update twemoji image resource

* fetch twitter/twemoji from github
```
git clone https://github.com/twitter/twemoji.git
```

* copy latest images from twemoji (current latest is v12.1.5)
```
cp -f v/12.1.5/72x72/*.png $TOP/72x72/
```

* to generate **emoji.qrc** and **parse_list/list.txt** from 72x72/
```
python3 mkqrc.py
```

* use git diff to generate test.json (automatically)
    * execute **[mk_test.py](./mk_test.py)**
```bash
$ python3 mk_test.py
```
then you get a refreshed test.json

## examples
