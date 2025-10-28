#pragma once
#include "enemy.h"
class enemy_fastspeed:public enemy
{
	public:
		enemy_fastspeed(float x,float y) : enemy(x,y,100.f,100,5.f) {
			
			setdamage(3.f);
			setmovespeed(100.f);
			sethealth(60.f);
			image.load("../Resources/goblin_100.png");
			collision.SetCollision(transform.GetPositionX(), transform.GetPositionY(), image.width,image.height);
		}
	
};

