class enemiesmanager;
#include <random>
#pragma once
#include <iostream>
using namespace std;
#include "gameobject.h"
#include "powerup_lineattack.h"
#include "powerup_maxnumber.h"
#include "json.hpp"
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
		enemyregister(this);
		//auto registe to enemiesmanager 
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
			std::random_device rd;  
			std::mt19937 gen(rd()); 
			std::uniform_int_distribution<> dist(0, 10); 
			int r = dist(gen);
			if (r == 3) {
				powerup_lineattack* scv = new powerup_lineattack(transform.GetPositionX(), transform.GetPositionY());
				//Random drop powerup 1
			}
			if (r == 4) {
				powerup_maxnumber* scv = new powerup_maxnumber(transform.GetPositionX(), transform.GetPositionY());
				//Random drop powerip 2
			}
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
	virtual void updatetime(float dt) {};
	//is for all subclass to update
	void enemyregister(enemy* scv);

	
private:
	float movespeed;
	float health;
	float damage;







};

