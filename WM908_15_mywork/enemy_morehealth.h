#pragma once
#include "enemy.h"
class enemy_morehealth :public enemy
{
public:
	enemy_morehealth(float x,float y) :enemy(x, y, 50.f, 200, 5) {
		image.load("../Resources/wolfman.png");
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY(), image.width, image.height);
	}
};

