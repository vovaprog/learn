from pygments import highlight
from pygments.lexers import CppLexer
from pygments.formatters import TerminalFormatter


with open('./learn_exceptions.cpp', 'r') as content_file:
    code = content_file.read()

print highlight(code, CppLexer(), TerminalFormatter())