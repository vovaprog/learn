aclocal
autoconf
automake --add-missing --foreign

function build_program {
    mkdir -p ./build
    cd ./build
    ../configure
    make
}

build_program

