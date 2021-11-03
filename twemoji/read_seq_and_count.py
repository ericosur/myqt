#!/usr/bin/env python3
# coding: utf-8

'''
    read seq.json, and
        * count items
        * ouput as one line data text (but unsort)
    does not effect the flow for twemoji
'''

from typing import List
from myutil import read_jsonfile

def output_as_list(js : List) -> None:
    ''' output as list.txt '''
    ofn = '/tmp/unsort.txt'
    with open(ofn, 'wt', encoding='utf8') as fout:
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
