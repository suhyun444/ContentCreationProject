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