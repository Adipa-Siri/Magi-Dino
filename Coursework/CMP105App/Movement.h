#pragma once
#include "Component.h"
#include "Entities.h"
class Movement : public Component
{
public:

	Movement(float sp);
	void Walk();
	void Jump();
	void update(Entities& obj, float dt) override;
	~Movement() {}
private:
	float m_speed;
	Entities m_entity;
};

