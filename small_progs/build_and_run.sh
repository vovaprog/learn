
PROGRAM=$1

printf "\n\n\n\n\n\n\n\n\n"
time g++ -std=c++11 ./$PROGRAM.cpp -o ./$PROGRAM -pthread && printf "\n\n" && ./$PROGRAM