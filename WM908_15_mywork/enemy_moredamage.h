#pragma once
#include "enemy.h"
class enemy_moredamage :public enemy
{
public:
	enemy_moredamage(float x, float y) :enemy(x, y, 50.f, 100, 20) {
		
		image.load("../Resources/xixuegui.png");
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY(), image.width, image.height);
	}
};

