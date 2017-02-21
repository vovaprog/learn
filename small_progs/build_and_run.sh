
PROGRAM=$1

printf "\n\n\n\n\n\n\n\n\n"
#time g++ -std=c++11 -I. -include stdc++.h ./$PROGRAM.cpp -o ./$PROGRAM -pthread && printf "\n\n" && ./$PROGRAM
#g++ -std=c++11 -I. -include stdc++.h -O2 ./$PROGRAM.cpp -o ./$PROGRAM || exit 1
#g++ -g -std=c++11 -I. -include stdc++.h -O3 ./$PROGRAM.cpp -o ./$PROGRAM -pthread || exit 1
g++ -std=c++11 -I. -include stdc++.h -O3 ./$PROGRAM.cpp -o ./$PROGRAM || exit 1

printf "\n\n\n\n\n\n\n\n\n"
./$PROGRAM
    