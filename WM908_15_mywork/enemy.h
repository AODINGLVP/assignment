class enemiesmanager;
#pragma once
#include <iostream>
using namespace std;
#include "gameobject.h"
class enemy: public GameObject
{
public:
	
	enemy(float x,float y,float movespeed,float health,float damage) {
		this->Tag = "enemy";
		image.load("../Resources/enemy1.png");
		collision.SetCollisionOffest(0.f, 0.f);
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY(), image.width, image.height);
		transform.SetPosition(x, y);
		this->movespeed = movespeed;
		this->health = health;
		this->damage = damage;
	}
	void setmovespeed(float speed) {
		this->movespeed = speed;
	}
	void setdamage(float damage) {
		this->damage = damage;
	}
	void sethealth(float health) {
		this->health = health;
	}
	void makedamage(float damage) override{
		health -= damage;
		cout << "Enemy health: " << health << endl;
	}
	bool dead() {
		if(health <= 0) {
			return true;
		}
		return false;
	}
	float getmovespeed() {
		return movespeed;
	}
	float gethealth() {
		return health;
	}
	float getdamage() {
		return damage;
	}

	
private:
	float movespeed;
	float health;
	float damage;







};

