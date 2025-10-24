#pragma once
class Collision
{
public:
	Collision() {
		x = 0;
		y = 0;
		w = 0;
		h = 0;
		offestx = 0;
		offesty = 0;
		istrigger = false;

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
	void setistrigger(bool chose) {
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
	bool isColliding(Collision& a,Collision& b) {
		return !(a.x + a.w < b.x ||  b.x + b.w < a.x ||  a.y + a.h < b.y ||  b.y + b.h < a.y);   
	}
private:
	float x, y, w, h, offestx, offesty;
	bool istrigger;

};

