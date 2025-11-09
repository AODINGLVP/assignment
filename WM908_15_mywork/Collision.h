#pragma once
class Collision
{
public:
	bool stopmove = false;
	Collision() {
		x = 0;
		y = 0;
		w = 0;//width
		h = 0;//height

		offestx = 0;
		offesty = 0;
		istrigger = false;//in fact, it only be checked in Water

	};
	void SetCollision(float x1, float y1, float w1,float h1) {
		x = x1+offestx;
		y = y1+offesty;
		w = w1;
		h = h1;


	}
	void SetCollision(float x1, float y1) {
		x = x1 + offestx;
		y = y1 + offesty;
	}
	void SetCollisionOffest(float x3, float y3) {
		offestx = x3;
		offesty = y3;
	}
	void setistrigger(bool chose) {//never been used
		istrigger = chose;
	}
	float getcollisionoffestX() {
		return offestx;
	}
	float getcollisionoffestY() {
		return offesty;
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
	bool isColliding(Collision& a,Collision& b) {//AABB check
		return !(a.x + a.w < b.x ||  b.x + b.w < a.x ||  a.y + a.h < b.y ||  b.y + b.h < a.y);   
	}

private:
	float x, y, w, h, offestx, offesty;
	
	bool istrigger;

};

