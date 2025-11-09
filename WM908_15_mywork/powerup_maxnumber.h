#pragma once
#include "GameObject.h"
#include "json.hpp"
class powerup_maxnumber:public GameObject
{public:
	powerup_maxnumber(float x, float y) {
		//power poject about AOE max number
		image.load("../Resources/powerup_maxnumber.png");
		transform.SetPosition(x, y);
		collision.SetCollision(x, y, 25, 25);
		Tag = "powerup_maxnumber";
	}
	void save(json& obj) override {
		obj.push_back({
			{"Tag","powerup_maxnumber"},
			{"position_x",transform.GetPositionX()},
			{"position_y",transform.GetPositionY()},
			
			});
	}
	void load(json& obj) override {
		transform.SetPosition(obj["position_x"], obj["position_y"]);
		
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY());
	}
};

