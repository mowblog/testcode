#!/usr/bin/env python3
#-*- coding:utf-8 -*-

import os
import sys
import sqlite3

def peach_log_statistic(path="."):
    for i in os.walk(path):
        if "test.db" in i[2][0]:
            database = os.path.join(i[0], i[2][0])
            print(database)
            conn = sqlite3.connect(database)
            # c = conn.cursor()
            cursor = conn.execute("SELECT id, name, address, salary  from COMPANY")
            for row in cursor:
                print ("ID = ", row[0])
                print ("NAME = ", row[1])
                print ("ADDRESS = ", row[2])
                print ("SALARY = ", row[3], "\n")
            conn.close()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: ./script path ")
        sys.exit(-1)
    peach_log_statistic(sys.argv[1])