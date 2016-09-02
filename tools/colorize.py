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


def colorize_text(text, line_function):
    line_number = 1

    for line in cat_output.splitlines():
        out = line_function(line)
        print "{0:>6}: {1}".format(line_number, out)
        line_number += 1


file_name = sys.argv[1]

cat_output = subprocess.check_output(['cat', file_name])

fname = file_name.lower()
if fname.endswith('.cpp') or fname.endswith('.c') or fname.endswith('.cc') or fname.endswith('.h') or fname.endswith('.hpp') or fname.endswith('.hh'):
    colorize_text(cat_output, colorize_cpp)
elif fname.endswith('.py'):
    colorize_text(cat_output, colorize_python)
else:
    print "unknown file type!"
