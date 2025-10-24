#pragma once
class Rigidbody
{public:
	Rigidbody() {
		movespeed = 10.f;
	};
	float getmovespeed() { return movespeed; };
	void setmovespeed(float speed) { movespeed = speed; };
	~Rigidbody();
private:
	float movespeed;

};

