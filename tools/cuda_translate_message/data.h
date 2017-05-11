#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdint.h>

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

#endif

