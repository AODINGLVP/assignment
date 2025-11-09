#pragma once
#include "Bullet.h"
#include "json.hpp"
class Enemybullet:public Bullet
{
public:
	
	Enemybullet() {
		//is enemy bullet,the direct will be set by archer
		Tag = "Enemybullet";
		image.load("../Resources/bulletenemy.png");
		setdamage(5.f);
	}
	void save(json& obj) override {
		obj.push_back({
			{"Tag","Enemybullet"},
			{"position_x",transform.GetPositionX()},
			{"position_y",transform.GetPositionY()},
			{"dirextion_x",getdirectionX()},
			{"direction_y",getdirectionY()},
			{"damage",getdamage() },
			{"lifetime",this->getlifetime()}
			
			});
	}
	void load(json& obj) override {
		transform.SetPosition(obj["position_x"], obj["position_y"]);
		setdirection(obj["dirextion_x"], obj["direction_y"]);
		setdamage(obj["damage"]);
		setlifetime(obj["lifetime"]);
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY());
	}
	
};

