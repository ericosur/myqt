# readme for qflip

qflip is a demo Qt GUI/qml application.

## cli options

There are two command line options to assign width and/or height for this
application.

  * -w    width
  * -h    height

for example:
```
$ ./qflip -w 800 -h 600
```

## demo how to use javascript within qml

[fact.js](./fact.js) is an external javascript contained a function. At
[main.qml](./main.qml) will import it and call function "fact".

Press the upper steelblue area to invoke this function.

## flip images

click on the image at the lower part of UI, it shows flipping transition

