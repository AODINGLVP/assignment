#pragma once
#include "GameObject.h"
#include "json.hpp"
class powerup_lineattack:public GameObject
{public:
	powerup_lineattack(float x,float y) {
		//powerup project about line attack
		image.load("../Resources/powerup_lineattack.png");
		transform.SetPosition(x, y);
		collision.SetCollision(x, y, 25, 25);
		Tag = "powerup_lineattack";
	}
	void save(json& obj) override {
		obj.push_back({
			{"Tag","powerup_lineattack"},
			{"position_x",transform.GetPositionX()},
			{"position_y",transform.GetPositionY()},

			});
	}
	void load(json& obj) override {
		transform.SetPosition(obj["position_x"], obj["position_y"]);

		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY());
	}
};

