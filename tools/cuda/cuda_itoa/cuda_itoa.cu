#include <stdio.h>

struct StringData {
	char str[11];
};

unsigned int *devDataInput;
StringData *devStringDataOutput;
unsigned int dataCount;

template< typename T >
void check(T result, char const *const func, const char *const file, int const line)
{
    if (result)
    {
        fprintf(stderr, "CUDA error at %s:%d code=%d(%s) \"%s\" \n",
                file, line, static_cast<unsigned int>(result), cudaGetErrorString(result), func);        
        // Make sure we call CUDA Device Reset before exiting
        cudaDeviceReset();
        exit(EXIT_FAILURE);
    }
}

#define checkCudaErrors(val)           check ( (val), #val, __FILE__, __LINE__ )

bool cdInit(unsigned int dataCountArg, void **hostInputMemory, void **hostOutputMemory, bool allocPinnedMemory)
{
	dataCount = dataCountArg;
	
	cudaError_t cudaStatus;
    
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaSetDevice error: %d\r\n", (int)cudaStatus);
        return false;
    }

    if(allocPinnedMemory)
    {
    	checkCudaErrors(cudaHostAlloc((void **)hostInputMemory, dataCount * sizeof(unsigned int), cudaHostAllocWriteCombined));
    	checkCudaErrors(cudaHostAlloc((void **)hostOutputMemory, dataCount * sizeof(StringData), 0));
    }
    else
    {
    	*hostInputMemory = (void *)malloc(dataCount * sizeof(unsigned int));
    	*hostOutputMemory = (void *)malloc(dataCount * sizeof(StringData));
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

