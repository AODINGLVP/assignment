#pragma once
#include "json.hpp"
class Rigidbody
{public:
	//not achieved 
	Rigidbody() {
		movespeed = 10.f;
	};
	float getmovespeed() { return movespeed; };
	void setmovespeed(float speed) { movespeed = speed; };
	~Rigidbody();
private:
	float movespeed;

};

