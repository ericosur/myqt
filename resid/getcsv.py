#!/usr/bin/env python
# -*- coding: utf-8 -*-

import csv


def readCsvAndOutputDefine(input_fn, output_fn):
    cheader = """// string_defineid.h is auto generated by getcsv.py

#ifndef __COMMON_STRING_DEFINEID_H__
#define __COMMON_STRING_DEFINEID_H__

"""
    with open(output_fn, "w") as text_file, open(input_fn, 'rb') as csvin:
        text_file.write(cheader)
        cin = csv.DictReader(csvin, delimiter=',')
        for row in cin:
            d = "#define {0}\t\t{1}\n".format(row['defineid'], row['id'])
            text_file.write(d)
        text_file.write("\n#endif\n")
        text_file.close()
        csvin.close()


def readCsvAndOutputIni(input_fn, output_fn):
    with open(output_fn, "w") as text_file, open(input_fn, 'rb') as csvin:
        text_file.write("; auto generated by getcsv.py\n")
        for locale_name in ['zh_CN', 'en_US', 'ar_AE']:
            csvin.seek(0)
            cin = csv.DictReader(csvin, delimiter=',')
            group_name = "[{0}]\n".format(locale_name)
            text_file.write(group_name)
            for row in cin:
                item = "{0}={1}\n".format(row['id'], row[locale_name])
                text_file.write(item)
    text_file.close()
    csvin.close()

if __name__ == '__main__':
    readCsvAndOutputDefine('test - translate.csv', 'strdef.h')
    readCsvAndOutputIni('test - translate.csv', 'strdef.ini')