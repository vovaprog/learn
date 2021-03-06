#g++ -std=c++11 -Winvalid-pch -x c++-header -g -O2 -o ./stdc++.h.gch /usr/include/i386-linux-gnu/c++/4.9/bits/stdc++.h

#ubuntu 14.04:
#g++ -std=c++11 -Winvalid-pch -x c++-header -g -O2 -o ./stdc++.h.gch /usr/include/x86_64-linux-gnu/c++/4.8/bits/stdc++.h
#g++ -std=c++11 -Winvalid-pch -x c++-header -g -O2 -pthread -o ./stdc++.h.gch /usr/include/x86_64-linux-gnu/c++/4.8/bits/stdc++.h

#ubuntu 16.04
g++ -std=c++11 -Winvalid-pch -x c++-header -O3 -o ./stdc++.h.gch /usr/include/x86_64-linux-gnu/c++/5/bits/stdc++.h #-pthread

#g++ -std=c++11 -Winvalid-pch -x c++-header -O2 -Wall -march=native -pthread -o ./learn_signals_include.h.gch ./learn_signals_include.h 

printf "\nbuild time: $SECONDS\n"
