
g++ -Wall -O2 -std=c++11 -I../../tools ./server.cpp ../../tools/NetworkUtils.cpp -o ./server -pthread
g++ -Wall -O2 -std=c++11 -I../../tools ./client.cpp ../../tools/NetworkUtils.cpp -o ./client -pthread
