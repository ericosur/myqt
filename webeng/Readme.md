# Readme for webeng

---

[TOC]

---

webeng is a sample application to ultilize Qt WebEngineView. For flexible testing, it will read settings from [setting.json](./setting.json) at the current directory. Path/filename was defined at [webeng.pro](./webeng.pro). If such setting file is not found, lower panes would be empty and upper middle button is empty. **restore** button would be no function, neither.

## default values at main.qml

There are three parts at main UI, header caption with some buttons, lower left and lower right panes. At lower panes, it will load local pages to demo [siriwave][1] and [music dna][2] as default.

[1]: https://github.com/caffeinalab/siriwavejs
[2]: https://github.com/paullewis/music-dna

For upper pane buttons:
* left-hand-side:
  * restore - load original [siriwave][1], [music dna][2] local pages
  * random - random load one page from "items" of setting.js, make lower pane as one larger display area. Press **restore** button to default look.
* middle parts:
  * two buttons are defined in setting.json
* right-hand-side:
  * hard-coded button in main.qml

## content of setting.json

As the following, you may modify "name" and "url" at each object. "items" is a list with multiple "name"/"url". It could be variable-length. UI will pick "default.right", "default.left", and one item in "items".


## how to access data member in json file

There is a utility class "ReadJson" to help load external json file into a js object. It also provides some function to help caller to access data member more easily.

for example, in c++ to get a string from "default.left.url":
```cpp
ReadJson rj;
rj.loadFile("/tmp/setting.json");
qDebug() << rj.getLeafString("default.left.url");
```
javascript usage:
```javascript
console.log(obj['default']['left']['url']);
```

### Use Qt to read json file

Related class are:
* QJsonDocument
* QJsonObject
* QJsonValue
* QJsonArray

## appendix

@import "setting.json"
