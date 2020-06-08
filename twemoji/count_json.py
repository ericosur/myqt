#!/usr/bin/env python3
# coding: utf-8

'''
    read seq.json, and
        * count items
        * ouput as one line data text (but unsort)
    does not effect the flow for twemoji
'''

import glob
import json
import os
import sys

def read_jsonfile(fn, debug=False):
    '''
    specify json filename and return whole json object
    '''
    if debug:
        print('load json from {}'.format(fn))
    if not os.path.exists(fn):
        print('file not found')
        return None
    # read from json file
    data = json.load(open(fn))
    return data



def main(argv):
    ''' main '''
    for f in argv:
        js = read_jsonfile(f)
        print('len of keys in file {}: {}'.format(f, len(js)))


if __name__ == '__main__':
    if len(sys.argv) > 1:
        main(sys.argv[1:])
    else:
        main(glob.glob('*.json'))
