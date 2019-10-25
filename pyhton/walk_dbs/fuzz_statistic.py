import os
import sys
import sqlite3

for i in os.walk(sys.argv[1]):
    if "test.db" in i[2][0]:
        database = i[0] +"/" + i[2][0]
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