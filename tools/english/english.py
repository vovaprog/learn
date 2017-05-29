#!/usr/bin/python3

import re
import random
import sys
from sys import stdin, stdout

fileName = "./english.txt"
direction = "en"

if len(sys.argv) > 1:
    direction = sys.argv[1]

if len(sys.argv) > 2:
    fileName = sys.argv[2]

with open(fileName, "r") as fl:
    lines = fl.readlines()

translations = []

for line in lines:
    m = re.search("^([^-:=]+)(:|=)(.*)$", line)
    pair = {}

    if m:
        pair["en"] = m.group(1).strip()
        pair["ru"] = m.group(3).strip()
        translations.append(pair)
    else:
        m = re.search("^(\w+)\s+(.*)$", line)
        if m:
            pair["en"] = m.group(1).strip()
            pair["ru"] = m.group(2).strip()
            translations.append(pair)
        elif len(line.strip()) > 0:
            print("warning: can't parse line: " + line)

print("press enter to print translation\npress ctrl+c to exit\n")

if direction == "en":
    source = "en"
    dest = "ru"
else:
    source = "ru"
    dest = "en"

while True:
    random.shuffle(translations)

    for trans in translations:
        stdout.write(trans[source])
        stdout.flush()
        stdin.readline()
        print(trans[source] + "   -   " + trans[dest] + "\n")
