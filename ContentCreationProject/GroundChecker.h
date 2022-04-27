#pragma once
#include "Quad.h"

//template <class... ARGS>
class GroundChecker : public Quad
{
public:
	GroundChecker();
	~GroundChecker();
	void InitializeCollideCallback(std::function<void()> func);
};

