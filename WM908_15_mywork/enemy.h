class enemiesmanager;
#include <random>
#pragma once
#include <iostream>
using namespace std;
#include "gameobject.h"
#include "powerup_lineattack.h"
#include "powerup_maxnumber.h"
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
			std::random_device rd;  // 真随机种子（来自硬件）
			std::mt19937 gen(rd()); // Mersenne Twister 伪随机数引擎
			std::uniform_int_distribution<> dist(0, 10); // 均匀分布 [0,9]
			int r = dist(gen);
			if (r == 3) {
				powerup_lineattack* scv = new powerup_lineattack(transform.GetPositionX(), transform.GetPositionY());

			}
			if (r == 4) {
				powerup_maxnumber* scv = new powerup_maxnumber(transform.GetPositionX(), transform.GetPositionY());
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
	void enemyregister(enemy* scv);

	
private:
	float movespeed;
	float health;
	float damage;







};

