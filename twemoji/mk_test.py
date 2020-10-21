#!/usr/bin/env python3
# coding: utf-8

'''
helper script to output emoji codepoint to json
output: test.json
'''

import json
import os

def read_text_file(fn):
    ''' read text file and return arr '''
    VERBOSE = False
    arr = list()
    # cnt = 0
    with open(fn, 'rt') as f:
        for ln in f.readlines():
            # cnt += 1
            # if cnt > 3:
            #     break
            ch = ln.strip()
            if VERBOSE:
                print('input:', ch)
            chs = ch.split('-')
            s = str()
            for cc in chs:
                s += chr(int(cc, 16))
            if VERBOSE:
                print('output:', s)
            arr.append(s)
    # for aa in arr:
    #     print(aa)
    print('loading {} lines'.format(len(arr)))
    return arr

def get_default_arr():
    ''' return default arr '''
    arr = [
        "\u2764\uFE0F\u1F1E7\u1F1F4\u1F64B\u200D\u2640\uFE0F\u1F3C8\u1F603",
        '\U0001f1e7\U0001f1ff\U0001f365\x39\u20e3\u26f9\ufe0f\u200d\u2642\ufe0f'
        '\u26bd\x23\u20e3',
        'z:\U0001f9df\u200d\u2640\ufe0f,\U0001f9df\U0001f3fd\u200d\u2640\ufe0f'
        ' \U0001f603',
        'n:3\x23\u20e34\x31\u20e39\xa9M\x38\xae9\u20e3',
        '他 \u2764\ufe0f \U0001F1F9\U0001F1FC 且他 \U0001f3c8 时 \U0001f64b\u200d\u2640\ufe0f'
        ' 会帮加油\U0001f17f0\U0001f19a0\U0001f1e6\U0001f1ff0\U0001f1e60',
        '跪 \U0001f9ce\u200d\u2640\ufe0f \U0001f3ec \U0001F461 \U0001f457 \U0001f460 \U0001f97f',
        'M\U0001f31dM\U0001f383M\U0001f385M\U0001f385\U0001f3fb',
        'G\u26f9\U0001f3fe\u200d\u2642\ufe0fG\U0001F3F4\U000E0067\U000E0062\U000E0077'
        '\U000E006C\U000E0073\U000E007F'
    ]
    return arr

def main(fn):
    ''' main '''
    arr = read_text_file(fn)
    test_json = 'test_updated.json'
    with open(test_json, 'wt', encoding='UTF-8') as ofh:
        ofh.write(json.dumps(arr))
    print('output to:', test_json)
    print('[notice] twemoji executable read **test.json**, not {}'.format(test_json))

if __name__ == '__main__':
    #DEFAULT_FN = 'parse_list/since-12.1.5-to-13.0.0-new-added.txt'
    DEFAULT_FN = 'parse_list/update-13.0.0-to-13.0.1.txt'
    main(DEFAULT_FN)
