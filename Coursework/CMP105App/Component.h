#pragma once
#include "Framework/GameObject.h"

class Entities;

class Component
{
public:

	virtual ~Component(){}
	virtual void update(Entities& obj, float dt) = 0;
};


