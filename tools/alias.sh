export DEB_BUILD_OPTIONS="parallel=6"
export JAVA_HOME=~/tools/java8/bin
alias astyle_allman_spaces='~/tools/astyle --attach-namespaces --indent=spaces=4 --pad-header --pad-oper --style=allman --suffix=none'
alias astyle_gate='~/tools/astyle --attach-namespaces --indent=tab=4 --pad-header --pad-oper --style=kr --suffix=none'
alias astyle_my='astyle --indent=spaces=4 --pad-oper --style=allman --suffix=none --unpad-paren'
alias autopep='autopep8 -i -v'
alias clangf='clang-format-3.6 -i --style="{BasedOnStyle: mozilla, IndentWidth: 4, BreakBeforeBraces: Allman, ColumnLimit: 100, AccessModifierOffset: -4}"'
alias cpplint='python ~/tools/cpplint.py --filter=-whitespace,-legal'
alias mk='printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" && make -j 6'
alias cmk="cmake .."
alias nospace='sed -i "s/[[:blank:]]*$//"'
alias blamec='~/tools/git-blame-colored.py'
alias p='printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"'
alias pmake='printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" && make'
alias findspace='grep -r -n "if(\|while(\|for(\|switch(\|[[:blank:]]$" .'
alias cdl="cd ~/git/learn"
alias cdlt="cd ~/git/learn/text"

findcode() {
    if [ -z "$1" ]
    then
        echo "USAGE: findcode search_pattern show_lines"
    fi
    if [ -z "$2" ]
    then
        find . -type f -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp" \
                    -o -iname "*.py" -o -iname "*.pl" -o -iname "Makefile" -o -iname "CMakeLists.txt" -o -iname "*.sh" | sort | xargs grep -in --color=auto $1
    else
        find . -type f -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp" \
                    -o -iname "*.py" -o -iname "*.pl" -o -iname "Makefile" -o -iname "CMakeLists.txt" -o -iname "*.sh" | sort | xargs grep -in --color=auto -C $2 $1
    fi
}

findc() {
    if [ -z "$1" ]
    then
        echo "USAGE: findc search_pattern show_lines"
    fi
    if [ -z "$2" ]
    then
        find . -type f -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp"  | sort | xargs grep -in --color=auto $1
    else
        find . -type f -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp"  | sort | xargs grep -in --color=auto -C $2 $1
    fi    
}

findcw() {
    if [ -z "$1" ]
    then
        echo "USAGE: findcw search_pattern show_lines"
    fi
    if [ -z "$2" ]
    then
        find . -type f -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp"  | sort | xargs grep -inw --color=auto $1
    else
        find . -type f -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp"  | sort | xargs grep -inw --color=auto -C $2 $1
    fi    
}


