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
	void makedamage(float damage) override {
		health -= damage;

	}
	void updataability(float dt) {
		abilitytimecount += dt;
		
	}
	int getabilitymax() { return abilitymax; }
	void setabilitymax(int max) { abilitymax = max; }
	void setabilitycooldown(float cooldown) { abilitycooldown = cooldown; }
	float getabilitycooldown() { return abilitycooldown; }
	void setabilitytimecount(float timecount) { abilitytimecount = timecount; }
	float getabilitytimecount() { return abilitytimecount; }
	void shot(float dt,Hero &hero);
	void save(json& obj) override {
		obj.push_back({
			{"Tag","hero"},
			{"position_x",transform.GetPositionX()},
			{"position_y",transform.GetPositionY()},
			{"health",health  },
			{"movespeed",movespeed },
			{"pojectilespeed",pojectilespeed },
			{"abilitytimecount",abilitytimecount },
			{"abilitymax",abilitymax },
			{"abilitycooldown",abilitycooldown }
			
			});
	}

	void load(json& obj) override {
		transform.SetPosition(obj["position_x"], obj["position_y"]);
		health = obj["health"];
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY());
		movespeed = obj["movespeed"];
		pojectilespeed = obj["pojectilespeed"];
		abilitytimecount = obj["abilitytimecount"];
		abilitymax = obj["abilitymax"];
		abilitycooldown = obj["abilitycooldown"];
	}
private :
	Hero() {
		collision.SetCollisionOffest(15.f, 10.f);
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY() , 90, 120);
		image.load("../Resources/Hero.png");
		health = 100;
		length = 10000;
		movespeed = 150.f;
		pojectilespeed = 1.0f;
		Tag = "hero";
		cooldown = 0;

	};
	float cooldown;
	float health;
	float movespeed;
	float pojectilespeed;
	int length;
	int cloest;
	float abilitycooldown=10.f;
	float abilitytimecount=0.f;
	int abilitymax=5;

	
	
	float getDirectionX(GameObject* A, GameObject* B) {
		float x = B->transform.GetPositionX() - A->transform.GetPositionX();
		float y = B->transform.GetPositionY() - A->transform.GetPositionY();
		float length = sqrt(x * x + y * y);
		return x / length;


	}
	float getDistance(GameObject* A, GameObject* B) {
		float x = B->transform.GetPositionX() - A->transform.GetPositionX();
		float y = B->transform.GetPositionY() - A->transform.GetPositionY();
		float length = sqrt(x * x + y * y);
		return length;


	}
	float getDirectionY(GameObject* A, GameObject* B) {
		float x = B->transform.GetPositionX() - A->transform.GetPositionX();
		float y = B->transform.GetPositionY() - A->transform.GetPositionY();
		float length = sqrt(x * x + y * y);
		return y / length;


	}



};

