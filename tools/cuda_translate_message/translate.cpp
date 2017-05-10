#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <cstdlib>
#include <ctime>

struct VenueOrderType {
	enum {
		Market = 10,
		Limit = 20,
		Pegged = 30
	};
};

struct ClientOrderType {
	enum {
		Market = 300,
		Limit = 200,
		Pegged = 100
	};
};

struct VenueData {
	uint64_t id; // to string
	uint64_t price; // arithm
	uint32_t quantity; // copy
	char userName[32]; // copy
	uint32_t orderType;
};

struct ClientData {
	char id[32];
	uint64_t price;
	uint32_t quantity;
	char userName[32];
	uint32_t orderType;
};

void translateVenueToClient(const VenueData &v, ClientData &c)
{
	sprintf(c.id, "%llu", (unsigned long long int)v.id);
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
	v.id = atoll(c.id); 
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
	//memset(vs, 0, count * sizeof(VenueData));
	
	srand(time(NULL));
	
	uint32_t venueOrderTypes[] = { VenueOrderType::Market, VenueOrderType::Limit, VenueOrderType::Pegged };
	
	for(int i=0;i<count;++i)
	{
		vs[i].id = rand();
		vs[i].price = rand();
		vs[i].quantity = rand();
		strcpy(vs[i].userName, "test");
		vs[i].orderType = venueOrderTypes[rand() % 3];
	}
	
	return vs;
}

void test()
{
	int dataCount = 100;
	
	VenueData *venueData = generateVenueData(dataCount);
	ClientData *clientData = new ClientData[dataCount];
	translateVenueToClient(venueData, clientData, dataCount);
	
	VenueData *venueDataBack = new VenueData[dataCount];
	//memset(venueDataBack, 0, dataCount * sizeof(VenueData));
	translateClientToVenue(clientData, venueDataBack, dataCount);
	
	if(memcmp(venueData, venueDataBack, sizeof(VenueData) * dataCount) != 0)
	{
		printf("error!\n");
		exit(-1);
	}
}

int main()
{
	test();
	
	return 0;
}
	

