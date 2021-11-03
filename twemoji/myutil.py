'''
provide common function
'''

import os
import json

def read_jsonfile(fn, debug=False):
    '''
    specify json filename and return whole json object
    '''
    if debug:
        print(f'load json from {fn}')
    if not os.path.exists(fn):
        print('file not found')
        return None
    # read from json file
    with open(fn, "rt", encoding='utf8') as fobj:
        data = json.load(fobj)
    return data
