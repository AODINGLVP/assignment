#pragma once
class Collision
{
public:
	Collision() {
		x = 0;
		y = 0;
		w = 0;
		h = 0;

	};
	void SetCollision(float x1, float y1, float w1,float h1) {
		x = x1;
		y = y1;
		w = w1;
		h = h1;


	}
	float getcollisionX() {
		return x;
	}
	float getcollisionY() {
		return y;

	}
	float getcollisionW() {
		return w;
	}
	float getcollisionH() {
		return h;
	}
	~Collision() {

	}
	bool isColliding(Collision& a,Collision& b) {
		return !(a.x + a.w < b.x ||  b.x + b.w < a.x ||  a.y + a.h < b.y ||  b.y + b.h < a.y);   
	}
private:
	float x, y, w, h;

};

