#pragma once
#include"GameObject.h"
#include"GamesEngineeringBase.h"
#include "Bullet.h"
#include<iostream>
class Hero :public GameObject
{
public:
	
	static Hero& getInstance() {
		static Hero instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}
	
	float getMoveSpeed() { return movespeed; }
	float getProjectileSpeed() { return pojectilespeed; }
	float getHealth() { return health; }
	float setHealth(int damage) { return health -= damage; }
	float setMoveSpeed(float speed) { return movespeed = speed; }
	float setProjectileSpeed(float speed) { return pojectilespeed = speed; }
	
	void shot(float dt) {
		cooldown += dt;
		cout << cooldown << endl;
		if(cooldown >=0.5f) {
			cout << "shot" << endl;
			cooldown -= 0.5f;
			Bullet* bullet = new Bullet();
			bullet->transform.SetPosition(this->transform.GetPositionX() + 40, this->transform.GetPositionY() + 60);

			
			
		}

	}
private :
	Hero() {
		collision.SetCollisionOffest(15.f, 10.f);
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY() , 90, 120);
		image.load("../Resources/Hero.png");
		health = 100;
		movespeed = 150.f;
		pojectilespeed = 1.0f;
		Tag = "hero";
		cooldown = 0;

	};
	float cooldown;
	int health;
	float movespeed;
	float pojectilespeed;
	
	




};

