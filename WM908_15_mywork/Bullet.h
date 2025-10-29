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
		directX = 1.f;
		directY = 1.f;
		
		
		image.load("../resources/bullet.png");

	}
	void move(float dt) {
		transform.SetPosition((dt * movespeed * directX) + transform.GetPositionX(), (dt * movespeed * directY) + transform.GetPositionY());
		
	}
	float getlifetime () {
		return lifetime;
	}
	void setlifetime(float time) {
		lifetime = time;
	}
	void setdamage(float damage) {
		this->damage = damage;
	}
	float getdamage() {
		return damage;
	}
	void setdirection(float x, float y) {
		directX = x;
		directY = y;
	}
	float getdirectionX() {
		return directX;
	}
	float getdirectionY() {
		return directY;
	}
	void findenemy() {

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
	void suicide() {
		removed(this);
		removeobj(this);
		delete this;
	};
	void save(json& obj) override{
		obj.push_back({
			{"Tag","bullet"},
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
	~Bullet() {

	}
private:
	float movespeed;
	float damage;
	float lifetime;
	float directX;
	float directY;

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

