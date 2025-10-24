class GameObjectManager;
#pragma once
#include <string>
#include "Transform.h"
#include "Collision.h"
#include "GamesEngineeringBase.h"
#include "Rigidbody.h"


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
		registerobj(this);
	
		



	}
	  int Update(float dt) {
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY()); 
	
			return 0;
	}

	void registerobj (GameObject* obj);
	void removeobj(GameObject* obj);

	virtual void makedamage(float damage) {};
	virtual void suicide() {};

		 ~GameObject() {}
private:
	
	
	





};

