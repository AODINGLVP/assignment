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
	void changecooldown(float x) {
		cooldown = cooldown * (1 - x);
	}
	void changemax(int x) {
		abilitymax = abilitymax + x;
	}
	float getMoveSpeed() { return movespeed; }
	float getProjectileSpeed() { return pojectilespeed; }
	float getHealth() { return health; }
	void setHealth(int hel) {  health =hel; }
	float setMoveSpeed(float speed) { return movespeed = speed; }
	float setProjectileSpeed(float speed) { return pojectilespeed = speed; }
	void makedamage(float damage) override {
		if (!invincible) {
			health -= damage;
			invincible = true;
			invincibletimecount = -1.f;
		}
		
	}
	void reflashinvincible() {
		invincible = false;
	}
	void updataability(float dt) {
		abilitytimecount += dt;
		
		
	}
	void updateinvincible(float dt) {
		invincibletimecount += dt;
		if (invincibletimecount >= 0 && invincible) {
			invincible = false;
		}
	}
	int getabilitymax() { return abilitymax; }
	void setabilitymax(int max) { abilitymax = max; }
	void setabilitycooldown(float cooldown) { abilitycooldown = cooldown; }
	float getabilitycooldown() { return abilitycooldown; }
	void setabilitytimecount(float timecount) { abilitytimecount = timecount; }
	float getabilitytimecount() { return abilitytimecount; }
	void shot(float dt,Hero &hero);
	float getshottimecount() {
		return shottimecount;
	}
	float getcooldown() {
		return cooldown;
	}
	void addbulletmovespeed(float x) {
		bulletmovespeed += x;
	}
	float getbulletmovespeed() {
		return bulletmovespeed;
	}
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
			{"abilitycooldown",abilitycooldown },
			{"bulletmovespeed",bulletmovespeed},
			{"cooldown",cooldown},
			{"shottimecount",shottimecount},
			{"invincible",invincible},
			{"invincibletimecount",invincibletimecount}
			
			});
	}
	float getdamage() {
		return bulletdamage;
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
		bulletmovespeed = obj["bulletmovespeed"];
		cooldown = obj["cooldown"];
		shottimecount = obj["shottimecount"];
		invincible = obj["invincible"];
		invincibletimecount = obj["invincibletimecount"];
	}
private :
	Hero() {
		collision.SetCollisionOffest(15.f, 10.f);
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY() , 90, 120);
		image.load("../Resources/Hero.png");
		health = 100;
		length = 10000;
		movespeed = 150.f;
		bulletmovespeed = 300.f;
		pojectilespeed = 1.0f;
		Tag = "hero";
		cooldown = 0.5f;
		shottimecount = 0.f;
		bulletdamage = 30.f;

	};
	float invincibletimecount = 0.f;
	float shottimecount;
	float bulletdamage;
	float cooldown;
	float health;
	float movespeed;
	float pojectilespeed;
	int length;
	int cloest;
	float abilitycooldown=10.f;
	float abilitytimecount=0.f;
	int abilitymax=5;
	float bulletmovespeed = 300.f;
	bool invincible = false;

	
	
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

