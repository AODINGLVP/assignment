#pragma once
#include "enemy.h"
class enemy_fastspeed:public enemy
{
	public:
		enemy_fastspeed(float x,float y) : enemy(x,y,100.f,100,5.f) {
			
			setdamage(3.f);
			setmovespeed(100.f);
			sethealth(60.f);
			image.load("../Resources/goblin_100.png");
			collision.SetCollision(transform.GetPositionX(), transform.GetPositionY(), image.width,image.height);
		}
		float getattack() override {
			return 5.f;
		}
		void save(json& obj) override {
			obj.push_back({
				{"Tag","enemy_fastspeed"},
				{"position_x",transform.GetPositionX()},
				{"position_y",transform.GetPositionY()},
				{"health",gethealth() }
				});
		}
		void load(json& obj) override {
			transform.SetPosition(obj["position_x"], obj["position_y"]);
			sethealth(obj["health"]);
			collision.SetCollision(transform.GetPositionX(), transform.GetPositionY());
		}
	
};

