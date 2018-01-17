alias astyle_my='astyle --indent=spaces=4 --pad-oper --style=allman --suffix=none --unpad-paren --pad-header'
alias autopep='autopep8 -i -v'
alias cdl="cd ~/git/learn"
alias cdg="cd ~/git"

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
