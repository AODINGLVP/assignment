#pragma once
#include "enemy.h"
class enemy_morehealth :public enemy
{
public:
	enemy_morehealth(float x,float y) :enemy(x, y, 50.f, 200, 5) {
		
		image.load("../Resources/wolfman.png");
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY(), image.width, image.height);
	}
	void save(json& obj) override {
		obj.push_back({
			{"Tag","enemy_morehealth"},
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

