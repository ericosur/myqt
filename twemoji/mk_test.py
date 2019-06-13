#!/usr/bin/env python3
# coding: utf-8

'''
helper script to output emoji codepoint to json
'''

import json

def main():
    ''' main '''
    arr = [
    '\U0001f1e7\U0001f1ff\U0001f365\x39\u20e3\u26f9\ufe0f\u200d\u2642\ufe0f\u26bd\x23\u20e3',
    'girl:\U0001f9df\u200d\u2640\ufe0f,\U0001f9df\U0001f3fd\u200d\u2640\ufe0f \U0001f603',
    '3\x23\u20e34\x31\u20e39\xa9M\x38\xae9\u20e3',
    '他 \u2764\ufe0f \U0001F1F9\U0001F1FC 且他 \U0001f3c8 时 \U0001f64b\u200d\u2640\ufe0f 会帮加油'
    '0\U0001f17f0\U0001f19a0\U0001f1e6\U0001f1ff0\U0001f1e60',
    'M\U0001f31dM\U0001f383M\U0001f385M\U0001f385\U0001f3fb',
    'G\u26f9\U0001f3fe\u200d\u2642\ufe0fG'
    ]

    with open('test.json', 'wt', encoding='UTF-8') as ofh:
        ofh.write(json.dumps(arr))

if __name__ == '__main__':
    main()
