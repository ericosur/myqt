#!/usr/bin/env python3
# coding: utf-8

'''
    read seq.json, and
        * count items
        * ouput as one line data text (but unsort)
    does not effect the flow for twemoji
'''

import glob
import sys
from typing import List
from myutil import read_jsonfile


def main(argv: List) -> None:
    ''' main '''
    for f in argv:
        js = read_jsonfile(f)
        print(f'len of keys in file {f}: {len(js)}')


if __name__ == '__main__':
    if len(sys.argv) > 1:
        main(sys.argv[1:])
    else:
        main(glob.glob('*.json'))
