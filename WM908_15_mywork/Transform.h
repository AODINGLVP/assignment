#pragma once
#include <string>
#include "json.hpp"
using namespace std;
class Transform
    //just about position

{
public:
    Transform() {
        
    }
       

    ~Transform() {}
    float GetPositionX() {
        return position[0];

    }
    float GetPositionY() {
        return position[1];

    }
    float GetrotationX() {
        return rotation[0];

    }
    float GetrotationY() {
        return rotation[1];

    }
    void SetPosition(float x, float y) {
        position[0] = x;
        position[1] = y;
	}
    void SetPositionX(float x) {
        position[0] = x;
    }
    void SetPositionY(float x) {
        position[1] = x;
    }
    void SetRotation(float x, float y) {
		rotation[0] = x;
		rotation[1] = y;
    }
    void SetScale(float s) {
		scale = s;
    }
    float GetScale() {
        return scale;
    }

    // …Ë÷√Œª÷√
private:
    float position[2] = {0.f,0.f};
	float rotation[2]{ 0.f,0.f };//useless
	float scale=1;//useless

};

