#!/usr/bin/env python3
# coding: utf-8

'''
helper script to output emoji codepoint to json
'''

import json

def main():
    ''' main '''
    arr = [
    '3\x23\u20e34\x31\u20e39\xa9M\x38\xae9\u20e3',
    '0\U0001f17f0\U0001f19a0\U0001f1e6\U0001f1ff0\U0001f1e60',
    'M\U0001f31dM\U0001f383M\U0001f385M\U0001f385\U0001f3fb',
    'G\u26f9\U0001f3fe\u200d\u2642\ufe0fG'
    ]



    with open('test.json', 'wt', encoding='UTF-8') as ofh:
        ofh.write(json.dumps(arr))

if __name__ == '__main__':
    main()
