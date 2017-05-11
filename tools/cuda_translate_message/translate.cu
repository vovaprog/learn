#include <stdio.h>

#include "data.h"

VenueData *devVenueInput;
ClientData *devClientOutput;
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

    cudaStatus = cudaMalloc((void**)&devVenueInput, dataCount * sizeof(VenueData));
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMalloc error: %d\r\n", (int)cudaStatus);
		return false;
	}

    cudaStatus = cudaMalloc((void**)&devClientOutput, dataCount * sizeof(ClientData));
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMalloc error: %d\r\n", (int)cudaStatus);
		return false;
	}
	
	return true;
}


__device__ void llToStringDevice(unsigned long long int x, char *output)
{
	const int bufSize = 30;
	char buf[bufSize];
	buf[bufSize - 1] = 0;
	int ind = bufSize - 2;
	
	do {
		buf[ind] = '0' + x % 10;
		x /= 10;
		--ind;
		
	} while (x != 0);
	
	for(int i=0;buf[ind]!=0;++i, ++ind)
	{
		output[i] = buf[ind];
	}
}


__device__ void translateVenueToClientDevice(const VenueData &v, ClientData &c)
{
	//sprintf(c.id, "%llu", (unsigned long long int)v.id);
	llToStringDevice(v.id, c.id);
	c.price = v.price * 100;
	c.quantity = v.quantity;
	memcpy(c.userName, v.userName, sizeof(v.userName));
		
	switch(v.orderType) {
	case VenueOrderType::Market: c.orderType = ClientOrderType::Market; break;
	case VenueOrderType::Limit: c.orderType = ClientOrderType::Limit; break;
	case VenueOrderType::Pegged: c.orderType = ClientOrderType::Pegged; break;
	}
}


__global__ void cdTranslateDevice(VenueData *devVenueInput, ClientData *devClientOutput)
{
	int threadIndex = blockIdx.x * blockDim.x + threadIdx.x;
	
	translateVenueToClientDevice(devVenueInput[threadIndex], devClientOutput[threadIndex]);	
}


bool cdTranslateVenueToClient(VenueData *venueInput, ClientData *clientOutput)
{
	cudaError_t cudaStatus=cudaSuccess;
	
    cudaStatus = cudaMemcpy(devVenueInput, venueInput, dataCount * sizeof(VenueData), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMemcpy error: %d\r\n", (int)cudaStatus);
		return false;
	}
	
	int numberOfBlocks = 512;
	int threadsPerBlock = dataCount / numberOfBlocks;

	cdTranslateDevice<<<numberOfBlocks, threadsPerBlock>>>(devVenueInput, devClientOutput);
	
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

    cudaStatus = cudaMemcpy(clientOutput, devClientOutput, dataCount * sizeof(ClientData), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMemcpy error: %d\r\n", (int)cudaStatus);
		return false;
	}
	
    return true;
}

bool cdTranslateVenueToClientStart(VenueData *venueInput)
{
	cudaError_t cudaStatus=cudaSuccess;
	
    cudaStatus = cudaMemcpy(devVenueInput, venueInput, dataCount * sizeof(VenueData), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMemcpy error: %d\r\n", (int)cudaStatus);
		return false;
	}
	
	int numberOfBlocks = 512;
	int threadsPerBlock = dataCount / numberOfBlocks;

	cdTranslateDevice<<<numberOfBlocks, threadsPerBlock>>>(devVenueInput, devClientOutput);
	
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) 
    {
        fprintf(stderr, "cuda error: %s\r\n", cudaGetErrorString(cudaStatus));
        return false;
    }
    
    return true;
}

bool cdTranslateVenueToClientEnd(ClientData *clientOutput)
{    
	cudaError_t cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "cudaDeviceSynchronize error: %d %s\r\n", (int)cudaStatus, cudaGetErrorString(cudaStatus));
        return false;
    }	

    cudaStatus = cudaMemcpy(clientOutput, devClientOutput, dataCount * sizeof(ClientData), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMemcpy error: %d\r\n", (int)cudaStatus);
		return false;
	}
	
    return true;
}


