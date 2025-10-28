#pragma once
#include "Bullet.h"
class Enemybullet:public Bullet
{
public:
	
	Enemybullet() {
		
		Tag = "Enemybullet";
		image.load("../Resources/bulletenemy.png");
	}
	
};

