#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <cstdlib>
#include <ctime>

#include <IncPerSecond.h>
#include <data.h>

bool cdInit(unsigned int dataCount);
bool cdTranslateVenueToClient(VenueData *venueInput, ClientData *clientOutput);
bool cdTranslateVenueToClientStart(VenueData *venueInput);
bool cdTranslateVenueToClientEnd(ClientData *clientOutput);

void llToString(unsigned long long int x, char *output)
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
	
	strcpy(output, buf + ind + 1);
}


void translateVenueToClient(const VenueData &v, ClientData &c)
{
	llToString(v.id, c.id);
	//sprintf(c.id, "%llu", (unsigned long long int)v.id);
	c.price = v.price * 100;
	c.quantity = v.quantity;
	memcpy(c.userName, v.userName, sizeof(v.userName));
		
	switch(v.orderType) {
	case VenueOrderType::Market: c.orderType = ClientOrderType::Market; break;
	case VenueOrderType::Limit: c.orderType = ClientOrderType::Limit; break;
	case VenueOrderType::Pegged: c.orderType = ClientOrderType::Pegged; break;
	default:
		printf("error 1!\n");
		exit(-1);		
	}
}

void translateClientToVenue(const ClientData &c, VenueData &v)
{
	//v.id = atoll(c.id);
	v.id = 0;
	v.price = c.price / 100;
	v.quantity = c.quantity;
	memcpy(v.userName, c.userName, sizeof(v.userName));
		
	switch(c.orderType) {
	case ClientOrderType::Market: v.orderType = VenueOrderType::Market; break;
	case ClientOrderType::Limit: v.orderType = VenueOrderType::Limit; break;
	case ClientOrderType::Pegged: v.orderType = VenueOrderType::Pegged; break;
	default:
		printf("error 2!\n");
		exit(-1);
	}		
}

void translateVenueToClient(VenueData *input, ClientData *output, int count)
{
	for(int i=0;i<count;++i)
	{
		translateVenueToClient(input[i], output[i]);
	}
}

void translateClientToVenue(ClientData *clientInput, VenueData *venueOutput, int count)
{
	for(int i=0;i<count;++i)
	{
		translateClientToVenue(clientInput[i], venueOutput[i]);	
	}
}

VenueData* generateVenueData(int count)
{
	VenueData *vs = new VenueData[count];
	
	srand(time(NULL));
	
	uint32_t venueOrderTypes[] = { VenueOrderType::Market, VenueOrderType::Limit, VenueOrderType::Pegged };
	
	for(int i=0;i<count;++i)
	{
		//vs[i].id = rand();
		vs[i].id = 0;
		vs[i].price = rand();
		vs[i].quantity = rand();
		strcpy(vs[i].userName, "test");
		vs[i].orderType = venueOrderTypes[rand() % 3];
	}
	
	return vs;
}

static const int dataCount = 1024 * 256;
static VenueData *venueData, *venueDataBack;
static ClientData *clientData;
static IncPerSecond incPerSecond(1024);

void cpuInit()
{
	venueData = generateVenueData(dataCount);
	clientData = new ClientData[dataCount];
	venueDataBack = new VenueData[dataCount];
}

void cpuRun()
{
	while(true)
	{
		translateVenueToClient(venueData, clientData, dataCount);
		incPerSecond.addAndPrint(dataCount);
	}
}

void cdRun()
{
	while(true)
	{
		cdTranslateVenueToClient(venueData, clientData);
		incPerSecond.addAndPrint(dataCount);
	}
}

void bothRun()
{
	while(true)
	{
		cdTranslateVenueToClientStart(venueData);
		translateVenueToClient(venueData, clientData, dataCount);
		cdTranslateVenueToClientEnd(clientData);		
		incPerSecond.addAndPrint(dataCount * 2);
	}
}


void cpuCheck()
{
	translateVenueToClient(venueData, clientData, dataCount);
	
	translateClientToVenue(clientData, venueDataBack, dataCount);
	
	if(memcmp(venueData, venueDataBack, sizeof(VenueData) * dataCount) != 0)
	{
		printf("error!\n");
		exit(-1);
	}	
}

void cdCheck()
{
	memset(clientData, 0, sizeof(ClientData) * dataCount);
	
	cdTranslateVenueToClient(venueData, clientData);

	if(memcmp(venueData, venueDataBack, sizeof(VenueData) * dataCount) != 0)
	{
		printf("cuda error!\n");
		exit(-1);
	}		
}


int main()
{
	cpuInit();	
	cpuCheck();
	
	cdInit(dataCount);
	cdCheck();
		
	//cpuRun();
	//cdRun();
	bothRun();
	
	/*char output[100];
	llToString(12345, output);
	printf("result: %s\n", output);*/
	
	return 0;
}
	

