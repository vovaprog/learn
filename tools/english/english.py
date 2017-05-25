#!/usr/bin/python3

import re
import random
from sys import stdin, stdout

with open("./english.txt", "r") as fl:
    lines = fl.readlines()

translations = []

for line in lines:
    m = re.search("^([^-:=]+)(-|:|=)(.*)$", line)
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

while True:
    random.shuffle(translations)

    for trans in translations:
        stdout.write(trans["en"])
        stdout.flush()
        stdin.readline()
        print(trans["en"] + "   -   " + trans["ru"] + "\n")
