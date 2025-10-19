#pragma once
#include <string>
using namespace std;
class Transform
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
    float GetPositionY() {
        return rotation[1];

    }
    void SetPosition(float x, float y) {
        position[0] = x;
        position[1] = y;
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
    float position[2] = {0,0};
	float rotation[2]{ 0,0 };
	float scale=1;

};

