
all:
	nvcc -c ./cuda_itoa.cu
	g++ -O3 -march=native -std=c++11 -I. ./main.cpp ./cuda_itoa.o -o ./cuda_itoa -lcuda -lcudart


	
	
