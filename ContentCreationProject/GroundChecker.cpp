#include "GroundChecker.h"
GroundChecker::GroundChecker()
{

}
GroundChecker::~GroundChecker()
{

}
void GroundChecker::InitializeCollideCallback(std::function<void()> func)
{
	collideCallback += func;
}

void GroundChecker::Collide(Mesh* collision)
{
	if (collision->Tag() == "Ground")
	{
		collideCallback();
	}
}
