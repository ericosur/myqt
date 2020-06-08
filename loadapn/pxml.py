#!/usr/bin/python3
# coding: utf-8

'''
parse apns-full-conf.xml
'''

import sys
try:
    from bs4 import BeautifulSoup
except ImportError:
    print('use pip install beautifulsoup4')
    print('use pip install lxml')
    sys.exit(1)

def load_xml(fn):
    ''' load_xml '''
    c = None
    with open(fn, 'rt') as f:
        c = f.read()
    return c

def main():
    ''' main '''
    content = load_xml('apns-full-conf.xml')
    soup = BeautifulSoup(content, 'lxml')
    apns = soup.find_all('apn')
    apn_list = list()
    MAX_ITEMS = 5   # max no of items will output
    cnt = 0
    for n in apns:
        #print(n.attrs)
        d = dict()
        d['imsi'] = n.attrs['mcc'] + n.attrs['mnc']
        d['carrier'] = n.attrs['carrier']
        apn_list.append(d)
        cnt += 1
        if cnt > MAX_ITEMS:
            break

    for l in apn_list:
        print(l)

if __name__ == '__main__':
    main()
