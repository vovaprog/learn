import os
import re
import sys
from termcolor import colored

fileRegexp = "(.*\.cpp$)|(.*\.h$)|(.*\.c$)|(.*\.cc$)|(.*\.hh)|(.*\.hpp)"
fileRex = re.compile(fileRegexp, re.IGNORECASE)

def check_file(file_name):
    if fileRex.match(file_name):
        return True
    else:
        return False


def file_to_string(file_name):
    with open (file_name, "r") as myfile:
        return myfile.read()

def file_to_lines(file_name):
    with open (file_name, "r") as myfile:
        return myfile.readlines()



def process_file(file_name):
    first_print = True

    lines = file_to_lines(file_name)
    for i in range(len(lines)):
        if(textRex.match(lines[i])):
            if first_print:
                print "-------"
                first_print = False
            print "{0}:{1}:   {2}".format(colored(file_name, "magenta"), 
                  colored(str(i + 1), "green"), 
                  lines[i].strip())

            
textRegexp = sys.argv[1]
textRegexp = ".*"+textRegexp
textRex = re.compile(textRegexp, re.IGNORECASE)


for dirInfo in os.walk("."):
    dir_path = dirInfo[0]
    dir_names = dirInfo[1]
    file_names = dirInfo[2]

    for file_name in file_names:
        file_path = dir_path + "/" + file_name
        if check_file(file_path):
            process_file(file_path)


