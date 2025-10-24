class Bulletmanager;
#pragma once
#include<iostream>
#include"GameObject.h"
#include <random>
class Bullet:public GameObject
{public:

	Bullet() {
		movespeed = 300;
		damage = 20;
		collision.SetCollisionOffest(0.f, 0.f);
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY(), 30, 30);
	
		collision.setistrigger(true);
		Tag = "bullet";
		lifetime = 3.f;
		regisetbulletmanager(this);
		
		
		image.load("../resources/bullet.png");

	}
	void move(float dt) {
		transform.SetPosition((dt * movespeed * 1) + transform.GetPositionX(), (dt * movespeed * 1) + transform.GetPositionY());
		
	}
	 
	void updatelifetime(float dt) {
		lifetime -= dt;
		if(lifetime <= 0) {
			removed(this);
			removeobj(this);
			delete this;
		}
		

	}
	void regisetbulletmanager(Bullet* bullet);
	void removed(Bullet* bullet);
	~Bullet() {

	}
private:
	float movespeed;
	float damage;
	float lifetime;

};

