class GameObjectManager;
#pragma once
#include <string>
#include "Transform.h"
#include "Collision.h"
#include "GamesEngineeringBase.h"
#include "Rigidbody.h"
#include "Camera.h"
#include <json.hpp>
using json = nlohmann::json;
using namespace std;
class GameObject
{
public:
	GamesEngineeringBase::Image image;
	string Name;
	bool Active;
	string Tag;
	int Layer;
	Transform transform;
	Collision collision;
	
	//Rigidbody rigidbody;


	GameObject() {
		Name = "";
		Active = true;
		Tag = "";
		Layer = 0;
		transform.SetPosition(0, 0);
		collision.SetCollision(0, 0, 0, 0);
		registerobj(this);
	
		



	}
	  int Update(float dt,Camera& camera) {
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY()); 
		transform.SetPosition(transform.GetPositionX(), transform.GetPositionY() );
	
			return 0;
	}
	  void Update() {
		  collision.SetCollision(transform.GetPositionX(), transform.GetPositionY());
		  transform.SetPosition(transform.GetPositionX(), transform.GetPositionY());
	  }

	void registerobj (GameObject* obj);
	void removeobj(GameObject* obj);
	
	virtual void makedamage(float damage) {};
	virtual void suicide() {};
	virtual void save(json& obj) {
		
	};
	virtual void load(json& obj) {};
	virtual int getmapx() {
		return 0;
	};
	virtual int getmapy() {
		return 0;
	};
	
	~GameObject() {};

private:
	
	
	





};

