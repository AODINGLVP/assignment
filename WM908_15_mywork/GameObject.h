#pragma once
#include <string>
#include "Transform.h"
#include "Collision.h"
#include "GamesEngineeringBase.h"


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

	GameObject() {
		Name = "";
		Active = true;
		Tag = "";
		Layer = 0;
		//GameObjectManager::getInstance().add(this);
		



	}
	/*virtual int Update(float dt) {
		collision.SetCollision(transform.GetPositionX(), transform.GetPositionY(), image.width, image.height);
	}*/
		 ~GameObject() {}
private:
	
	
	





};

