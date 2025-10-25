#pragma once
#include "GameObject.h"
class Water :public GameObject
{
public:
	Water() {
		image.load("../Resources/water.png");
		Tag = "water";
		collision.SetCollision(0, 0, 0, 0);

		
	
	}
private:

};

