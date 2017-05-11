
all:
	nvcc -c ./translate.cu
	g++ -O3 -march=native -std=c++11 -I. ./translate.cpp ./translate.o -o ./translate -lcuda -lcudart
	
