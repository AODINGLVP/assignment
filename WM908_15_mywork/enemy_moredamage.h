#pragma once
#include "enemy.h"
class enemy_moredamage :public enemy
{
public:
	enemy_moredamage(float x, float y) :enemy(x, y, 50.f, 100, 20) {
		
		image.load("../Resources/xixuegui.png");
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY(), image.width, image.height);
	}
	void save(json& obj) override {
		obj.push_back({
			{"Tag","enemy_moredamage"},
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

