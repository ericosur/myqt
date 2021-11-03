#!/usr/bin/env python3
# coding: utf-8

''' helper to generate emoji.qrc '''

from glob import glob
import sys
import re

def output_qrc(arr, fn='emoji.qrc') -> None:
    ''' emoji.qrc '''
    header = '''<RCC>
    <qresource prefix="/">'''
    footer = '''    </qresource>
</RCC>'''
    with open(fn, 'wt', encoding='utf8') as fobj:
        print(header, file=fobj)
        for f in arr:
            print(f'        <file>{f}</file>', file=fobj)
        print(footer, file=fobj)
    print('output to:', fn)


def output_list(arr, fn='parse_list/list.txt') -> None:
    ''' output arr '''
    with open(fn, 'wt', encoding='utf8') as fobj:
        for f in arr:
            r = re.sub(r'^72x72\/(.+)\.png', r'\1', f)
            print(r, file=fobj)
    print('output to:', fn)

def main() -> None:
    ''' main '''
    arr = glob('72x72/*.png')
    #print('len:', len(arr))
    if not arr:
        sys.exit(1)
    arr.sort()

    output_qrc(arr)
    output_list(arr)

if __name__ == '__main__':
    main()
