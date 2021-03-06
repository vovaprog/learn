#!/usr/bin/python

import sys
import Image


#=====================================================================

import os
import errno
import fcntl

def open_file_write_exclusive(file_name):
    """
    If file is available - returns file object.
    If file is locked - returns None.
    If error occured - throws error.
    Truncates opened file.
    """

    fl = open(file_name, 'w')

    try:        
        fcntl.flock(fl, fcntl.LOCK_EX | fcntl.LOCK_NB)

    except IOError as e:
        if e.errno == errno.EAGAIN:
            return None
        else:
            raise

    fl.truncate(0)

    return fl

#=====================================================================


fl = open_file_write_exclusive("./test.png")

print "file: " + str(fl)
fl2 = open_file_write_exclusive("./test.png")
print "file2: " + str(fl2)


if fl is None:
    print "none returned"
    exit(0)

if len(sys.argv) > 1 and sys.argv[1] == "lock": 
    input = raw_input("press enter: ")
    fl.close()
    input = raw_input("press enter 2: ")
else:    
    try:
        
        im = Image.open("./test.jpg")
        im.thumbnail((100, 100), Image.ANTIALIAS)
        im.save(fl, "PNG")
    finally:
        fl.close()



