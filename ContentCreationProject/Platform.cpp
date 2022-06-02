#include "Platform.h"
#include <iostream>
Platform::Platform()
{
	curAnimationState = "Sand" + to_string((rand() % 3) + 1) + ".png";
	scale = Vector3f(0.5f, 0.2f, 1.0f);
}
Platform::~Platform()
{

}