class GameObjectManager;
#pragma once
#include <string>
#include "Transform.h"
#include "Collision.h"
#include "GamesEngineeringBase.h"
#include "Rigidbody.h"
#include "Camera.h"
#include <json.hpp>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class GameObject
{
public:
	//the baisc class for all unites
	GamesEngineeringBase::Image image;
	string Name;//useless
	bool Active;
	string Tag;
	int Layer;//uesless
	Transform transform;
	Collision collision;
	
	//Rigidbody rigidbody;//did not achieve


	GameObject() {
		Name = "";
		Active = true;
		Tag = "";
		Layer = 0;
		transform.SetPosition(0, 0);
		collision.SetCollision(0, 0, 0, 0);
		registerobj(this);
		//auto regist to GameObjectManager
	
		



	}
	  int Update(float dt,Camera& camera) {
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY()); 
		transform.SetPosition(transform.GetPositionX(), transform.GetPositionY() );//It might have been useful during the production process, but it probably doesn't serve any purpose now.
	
			return 0;
	}
	  void Update() {
		  collision.SetCollision(transform.GetPositionX(), transform.GetPositionY());
		  transform.SetPosition(transform.GetPositionX(), transform.GetPositionY());
		  
	  }//for update collision box position
	  //in fact ,the Update with dt and camera  is no different with the no variable one ,but for the chaos development ,is not convenience to change it 

	void registerobj (GameObject* obj);
	void removeobj(GameObject* obj);
	virtual float getattack() { return 5.f; };
	//is for Hero and Enemy
	virtual void makedamage(float damage) {};
	//is for Hero and Enemy
	virtual void suicide() {};
	//for every subclass
	virtual void save(json& obj) {
		
	};
	//every subclass need it to save
	virtual void load(json& obj) {};
	//every subclass need it to load
	virtual int getmapx() {
		return 0;
	};//is for Water
	virtual int getmapy() {
		return 0;
	};//is for Water
	
	~GameObject() {};

private:
	
	
	





};

