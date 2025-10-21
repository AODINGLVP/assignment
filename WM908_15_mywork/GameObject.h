#pragma once
#include <string>
#include "Transform.h"
#include "Collision.h"

using namespace std;
class GameObject
{
public:
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



	}
	void updata(float dt) {
		collision.SetCollision()
	}
		 ~GameObject() {}
private:
	
	
	





};

