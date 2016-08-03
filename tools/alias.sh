#==============================================================================================

export JAVA_HOME=~/tools/java8/bin
alias astyle_allman_spaces='~/tools/astyle --attach-namespaces --indent=spaces=4 --pad-header --pad-oper --style=allman --suffix=none'
alias astyle_gate='~/tools/astyle --attach-namespaces --indent=tab=4 --pad-header --pad-oper --style=kr --suffix=none'
alias autopep='autopep8 -i -v'
alias clangf='clang-format-3.6 -i --style="{BasedOnStyle: mozilla, IndentWidth: 4, BreakBeforeBraces: Allman, ColumnLimit: 100, AccessModifierOffset: -4}"'
alias cpplint='python ~/tools/cpplint.py --filter=-whitespace,-legal'
alias mk="make -j 6"
alias cmk="cmake .."

findcode() {
    if [ -z "$1" ]
    then
        echo "USAGE: findcode search_pattern show_lines"
    fi
    if [ -z "$2" ]
    then
        find . -type f -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp" \
                    -o -iname "*.py" -o -iname "*.pl" -o -iname "Makefile" -o -iname "*.CMakeLists.txt" -o -iname "*.sh" | xargs grep -in --color=auto $1        
    else
        find . -type f -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp" \
                    -o -iname "*.py" -o -iname "*.pl" -o -iname "Makefile" -o -iname "*.CMakeLists.txt" -o -iname "*.sh" | xargs grep -in --color=auto -C $2 $1                    
    fi
}

findc() {
    if [ -z "$1" ]
    then
        echo "USAGE: findc search_pattern show_lines"
    fi
    if [ -z "$2" ]
    then
      find . -type f -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp"  | xargs grep -in --color=auto $1
    else
      find . -type f -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp"  | xargs grep -in --color=auto -C $2 $1
    fi    
}
