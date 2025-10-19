#pragma once
#include <string>
#include "Transform.h"

using namespace std;
class GameObject
{
public:
		GameObject() {}
		 ~GameObject() {}
private:
	string Name;
	bool Active;
	string Tag;
	int Layer;
	Transform transform;
	





};

