# Readme

[TOC]


## description

- **mk_test.py** helps to generates **test.json** that contains test strings
  array for display/test.

- **test.json** is

## steps for twemoji resources

* fetch twitter/twemoji from github
```
git clone https://github.com/twitter/twemoji.git
```

* copy latest images from twemoji
```
cp -f v/12.1.5/72x72/*.png $TOP/72x72/
```

* to generate **emoji.qrc** and **parse_list/list.txt** from 72x72/
```
python3 mkqrc.py
```

* use git diff to generate test.json
    * first, generate **n.txt**
```
git diff parse_list/list.txt | \grep ^+ | sed 's/\+//' > n.txt
```

###### tags: ```emoji``` ```unicode``` ```qt``` ```qml```