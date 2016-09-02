#!/usr/bin/python

import sys
import subprocess
import re
import time
from termcolor import colored
import keyword

def colorize(line, keys, types, vals, preps):
    words = re.split('(\W+)', line)
    out = ""
    for word in words:
        if word in keys:
            out += colored(word, 'blue')
        elif word in types:
            out += colored(word, 'red')
        elif re.match('^[0-9]+(\.[0-9]+)?$', word) or word in vals:
            out += colored(word, 'green')
        elif word in preps:
            out += colored(word, 'magenta')
        else:
            out += word
    return out


def colorize_cpp(line):
    keys_string = """auto   const   struct
break  continue  else    for            switch   void
case   default   enum    goto   register  sizeof  typedef  volatile
char        do            extern     if     return     static  union   while
asm         dynamic_cast  namespace  reinterpret_cast  try
explicit    new           static_cast       typeid
catch       operator      template          typename
class       friend        private    this              using
const_cast  inline        public     throw             virtual
delete      mutable       protected                
and      bitand   compl   not_eq   or_eq   xor_eq
and_eq   bitor    not     or       xor"""

    keys = keys_string.split()    
    types = ['int', 'char', 'short', 'long', 'double', 'float', 'void', 'unsigned', 'signed', 'bool', 'wchar_t']
    vals = ['true', 'false']
    preps = ['include', '#', 'define', 'ifdef', 'ifndef']

    return colorize(line, keys, types, vals, preps)

def colorize_python(line):
    keys = keyword.kwlist    
    types = ['int', 'float', 'bool', 'str']
    vals = ['True', 'False']
    preps = []    

    return colorize(line, keys, types, vals, preps)

reload(sys)
sys.setdefaultencoding('utf8')

file_name = sys.argv[1]
fname = file_name.lower()

blame_output = subprocess.check_output(
    ['git', 'blame', '--line-porcelain', file_name])


author_color = {}

colors = ['grey', 'red', 'green',  'yellow',
          'blue', 'magenta', 'cyan', 'white']
color_index = 0

line_number = 1
max_author = 0

for line in blame_output.splitlines():
    m = re.search("^author\s+(.*)$", line)
    if m:
        author = m.group(1)
        author = author.strip().decode()
        if len(author) > max_author:
            max_author = len(author)

        if not author in author_color:
            color_index = (color_index + 1) % len(colors)
            author_color[author] = colors[color_index]

        continue
    m = re.search("^author-time\s+(.*)$", line)
    if m:
        author_time = m.group(1)
        author_time = time.ctime(int(author_time))
        author_time = author_time.encode('utf-8')
        continue
    m = re.search("^\t(.*)$", line)
    if m:
        code = m.group(1)
        
        if fname.endswith('.cpp') or fname.endswith('.c') or fname.endswith('.cc') or fname.endswith('.h') or fname.endswith('.hpp') or fname.endswith('.hh'):
            code = colorize_cpp(code)
        elif fname.endswith('.py'):
            code = colorize_python(code)
            
        print(str.format("{0}   {1}   {2:>5}: {3}", author_time, colored(
            author.ljust(max_author + 1), author_color[author]), line_number, code))
        line_number += 1
        continue
