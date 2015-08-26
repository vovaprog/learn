#pragma once

#include <vector>
#include <memory>

#include "body.h"
#include "spaceship.h"

using namespace std;

class Model{
//private:	
public:
	vector<unique_ptr<Body> > bodies;

public:
	void init()
	{
		bodies.push_back(unique_ptr<Body>(new Body()));
		bodies.push_back(unique_ptr<Body>(new Body()));
		bodies.push_back(unique_ptr<Body>(new Body()));
		bodies.push_back(unique_ptr<Body>(new Spaceship("cassini")));
		bodies.push_back(unique_ptr<Body>(new Spaceship("new horizons")));
	}

};

