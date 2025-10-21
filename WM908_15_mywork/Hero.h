#pragma once
#include"GameObject.h"
#include"GamesEngineeringBase.h"
class Hero :public GameObject
{
public:
	
	
	Hero() {
		
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY(), 80, 160);
		image.load("../Resources/Hero.png");
		health = 100;
		movespeed = 110.f;
		pojectilespeed = 1.0f;
		
	};
	float getMoveSpeed() { return movespeed; }
	float getProjectileSpeed() { return pojectilespeed; }
	float getHealth() { return health; }
	float setHealth(int damage) { return health -= damage; }
	float setMoveSpeed(float speed) { return movespeed = speed; }
	float setProjectileSpeed(float speed) { return pojectilespeed = speed; }
private :
	
	int health;
	float movespeed;
	float pojectilespeed;
	
	




};

