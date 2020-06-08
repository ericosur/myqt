#!/usr/bin/env python3
# coding: utf-8

'''
    read seq.json, and
        * count items
        * ouput as one line data text (but unsort)
    does not effect the flow for twemoji
'''

import os
import json

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


def output_as_list(js):
    ''' output as list.txt '''
    ofn = '/tmp/unsort.txt'
    with open(ofn, 'wt') as fout:
        for j in js:
            for k in js[j]:
                print('-'.join(k), file=fout)
    print('output file: ', ofn)


def main():
    ''' main '''
    js = read_jsonfile('seq.json')
    print('len of keys: ', len(js))
    count = 0

    for k in js:
        count += len(js[k])

    print('total values: ', count)
    output_as_list(js)


if __name__ == '__main__':
    main()
