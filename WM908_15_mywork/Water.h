#pragma once
#include "GameObject.h"
class Water :public GameObject
{
public:
	int positionmap_x;//the position in Third-level pointer watermap
	int positionmap_y;//the position in Third-level pointer watermap
	Water() {
		positionmap_x = 0;
		positionmap_y = 0;
		image.load("../Resources/water.png");
		Tag = "water";
		collision.SetCollision(0, 0, 0, 0);

		
	
	}
	int getmapx() override{
		return positionmap_x;
	}
	int getmapy() override {
		return positionmap_y;
	}
	void save(json& obj) override {
		obj.push_back({
			{"Tag","water"},
			{"position_x",transform.GetPositionX()},
			{"position_y",transform.GetPositionY()},
			{"positionmap_x",positionmap_x},
			{"positionmap_y",positionmap_y},
			{"Active",this->Active}
			});
	}
	void load(json& obj) override {
		
		
		positionmap_x = obj["positionmap_x"];
		positionmap_y = obj["positionmap_y"];
		this->Active = obj["Active"];
	}
	
private:

};

