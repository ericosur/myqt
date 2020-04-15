# README for loadapn


## experiment

On raspberry pi 3B+ (a relative slow device...)


| method            |  ms | ratio |
|-------------------|-----|-------|
|loadApnDatabase_old| 166 | 2.371 |
|loadApnDatabase_new| 110 | 1.571 |
|load_apn_re        |  70 | 1.000 |
|load_apn_re_bad    | 143 | 2.043 |

## notice on regular expression

RegExp engine is kind of heavy loading parsing engine. Avoid to compile a RE pattern within a repeatly used function. Initial it at ctor and re-use.

Here we use such regular expression:
```regexp
(?<key>[A-Z]+)=(?<val>([^;]+)?);
```
