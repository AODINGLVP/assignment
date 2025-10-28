#pragma once
#include "enemy.h"
#include "Hero.h"
#include "Enemybullet.h"
class Archr:public enemy
{
public:
	float cooldown =1.f;
	float timecount = 0;
	Archr(float x,float y) :enemy(x,x, 50, 100, 0) {
		
		Tag = "Archr";
		image.load("../Resources/archr.png");
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY(),image.width,image.height);

	}
	void fire(float dt) {
		cout << "fire"<<endl;
		timecount += dt;
		if(timecount>=cooldown) {
			timecount = 0;
			Enemybullet* bullet = new Enemybullet();
			bullet->transform.SetPosition(transform.GetPositionX(),transform.GetPositionY());
			bullet->setdirection(getDirectionX(this, &Hero::getInstance()), getDirectionY(this, &Hero::getInstance()));

		}

	}
	void updatetime(float dt) override {
		fire(dt);
	}
private:
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

