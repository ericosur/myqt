Readme of scandir
=================

**scandir** is a tiny CLI utility that helps to scan recursively into folder to search wanted folders and files. If one folder has no target files in it, it will be ignored by scandir.


Configuration
-------------

**scandir** MUST correctly reads setting from scandir.ini to
run properly. Or it will abort to run with no correct output.

Usually it reads default config file from *tmp/scandir.ini*
Or you may specify CLI option while invoke it.

```
$ scandir -c /path/to/scandir.ini
```

It will output scanned results to "outputpath" in *scandir.ini*
Default value for "outputpath" is */tmp*

Values for
"basedirid1"
"basefileid1"


Folder and file id
------------------

From spec from RSE integration, id is a three-byte (24bit) integer. Each type/folder/file has its own unique id and SHOULD NOT be the same.

May refer to sample scandir.ini.

```
thread1=music
filter1=*.mp3, *.wav, *.aac, *.m4a, *.wma, *.flac, *.ogg, *.ape
basedirid1=2097152
basefileid1=4194304
```

For music media files, thread1 will be named "music". It will search for file
extensition as "filter1". Folder which contains music files will be given an id
from 2097152 (0x200000) to 4194303 (0x3FFFFF). The left-hand-side 3-bit is
designed to tell from each type of id.

Every type of id is listed as the following table:

media type | sub type  | LHS 3bit* | min id (dec) | min id (hex) | max id (dec) | max id (hex)  |
---------- | --------- | :-------: | -----------: | -----------: | -----------: | ------------: |
music      | folder    |  001      | 2,097,152    | 0x200000     | 4,194,303    | 0x3FFFFF      |
music      | file      |  010      | 4,194,304    | 0x400000     | 6,291,455    | 0x5FFFFF      |
video      | folder    |  011      | 6,291,456    | 0x600000     | 8,388,607    | 0x7FFFFF      |
video      | file      |  100      | 8,388,608    | 0x800000     | 10,405,759   | 0x9FFFFF      |
picture    | folder    |  101      | 10,485,760   | 0xA00000     | 12,582,911   | 0xBFFFFF      |
picture    | file      |  110      | 12,582,912   | 0xC00000     | 14,680,063   | 0xDFFFFF      |

note 1: LHS (left hand side) 3bit mean the most significant bits. (little endian)

**scandir** uses three different threads to search different media type.
It is possible that one folder may contain music and video files, and such folder
has its own music folder id, and its own video folder id. It is also possible if
one file is identified both as music and video. Two different id will refer to
the same file.

So if one folder has a music folder id, it is certain such folder contains music
files.

The short point for such id system: only 2,097,151 files/folder for each media
type. **scandir** will refuse to record id/path if id is used up.
