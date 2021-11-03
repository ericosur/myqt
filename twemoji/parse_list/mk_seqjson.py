#!/usr/bin/env python3
# coding: utf-8

'''
sanilize list.txt and generate seq.json
'''

import re
import json

def main():
    ''' main '''
    fn = 'list.txt'
    arr = []
    with open(fn, 'rt', encoding='UTF-8') as fh:
        arr = fh.readlines()
    p = re.compile(r'([0-9a-f]+)')
    cp_dict = {}
    cnt = 0
    for v in arr:
        cnt += 1
        m = p.findall(v)
        if not m:
            continue
        #print('type(m):{},m:{}'.format(type(m), m))
        # if len(m) == 1:
        #     m.append('null')
        k = m[0]
        if not k in cp_dict:
            cp_dict[k] = []
        cp_dict[k].append(m)

    print('unique heading key:', len(cp_dict))
    print('total cnt:', cnt)

    tot = 0
    for ii, v in enumerate(cp_dict):
        if cp_dict[v]:
            tot += len(cp_dict[v])
        else:
            tot += 1
        print(f'{ii}: {cp_dict[v]}')
    print('go through cp_dict, len:', tot)

    #print(cp_dict['1f935'])
    #print(cp_dict['1fa92'])

    out_json_file = '../seq.json'
    with open(out_json_file, 'wt', encoding='UTF-8') as ofh:
        ofh.write(json.dumps(cp_dict, indent=2, sort_keys=True))
    print('output json file:', out_json_file)

if __name__ == '__main__':
    main()
