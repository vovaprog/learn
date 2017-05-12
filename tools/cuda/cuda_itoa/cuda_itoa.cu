#include <stdio.h>

struct StringData {
	char str[11];
};

unsigned int *devDataInput;
StringData *devStringDataOutput;
unsigned int dataCount;

bool cdInit(unsigned int dataCountArg)
{
	dataCount = dataCountArg;
	
	cudaError_t cudaStatus;
    
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaSetDevice error: %d\r\n", (int)cudaStatus);
        return false;
    }

    cudaStatus = cudaMalloc((void**)&devDataInput, dataCount * sizeof(unsigned int));
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMalloc error: %d\r\n", (int)cudaStatus);
		return false;
	}

    cudaStatus = cudaMalloc((void**)&devStringDataOutput, dataCount * sizeof(StringData));
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMalloc error: %d\r\n", (int)cudaStatus);
		return false;
	}
	
	return true;
}


__device__ void uintToStringDevice(unsigned int x, char *output)
{
	const int bufSize = 11;
	char buf[bufSize];
	buf[bufSize - 1] = 0;
	int ind = bufSize - 2;
	
	do {
		buf[ind] = '0' + x % 10;
		x /= 10;
		--ind;
	} while (x != 0);

	++ind;

	int i;
	for(i = 0; buf[ind] != 0; ++i, ++ind)
	{
		output[i] = buf[ind];
	}
	output[i] = 0;
}


__global__ void cdItoaDevice(unsigned int *dataInput, StringData *stringDataOutput)
{
	int threadIndex = blockIdx.x * blockDim.x + threadIdx.x;
	
	uintToStringDevice(dataInput[threadIndex], stringDataOutput[threadIndex].str);	
}


bool cdItoa(unsigned int *dataInput, StringData *stringDataOutput)
{
	cudaError_t cudaStatus=cudaSuccess;
	
    cudaStatus = cudaMemcpy(devDataInput, dataInput, dataCount * sizeof(unsigned int), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMemcpy error: %d\r\n", (int)cudaStatus);
		return false;
	}
	
	int numberOfBlocks = 1024;
	int threadsPerBlock = dataCount / numberOfBlocks;

	cdItoaDevice<<<numberOfBlocks, threadsPerBlock>>>(devDataInput, devStringDataOutput);
	
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) 
    {
        fprintf(stderr, "cuda error: %s\r\n", cudaGetErrorString(cudaStatus));
        return false;
    }
    
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaDeviceSynchronize error: %d %s\r\n", (int)cudaStatus, cudaGetErrorString(cudaStatus));
        return false;
    }	

    cudaStatus = cudaMemcpy(stringDataOutput, devStringDataOutput, dataCount * sizeof(StringData), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMemcpy error: %d\r\n", (int)cudaStatus);
		return false;
	}
	
    return true;
}

