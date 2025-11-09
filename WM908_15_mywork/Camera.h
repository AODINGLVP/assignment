#pragma once
#include <mutex>
#include "json.hpp"
using json = nlohmann::json;
class Camera
{
public:
   
    
    

    static Camera& GetCamera()
    {
        static Camera camera; 
        return camera;
    }//singleton pattern

 

    
    void Move(float dx, float dy)
    {
        offsetX += dx;
        offsetY += dy;
    }

    
    void SetPosition(float x, float y)
    {
        offsetX = x;
        offsetY = y;
    }
    void SetPositionX(float x) {
        offsetX = x;
    }
    void SetPositionY(float x) {
        offsetY = x;
    }

  
    float GetX()  {
        return offsetX;
    }
    float GetY()  {
        return offsetY;
    }
    void save(json& camera) {
        camera.push_back({
            {"Tag","camera"},
            {"offestX",offsetX },
            {"offestY",offsetY}

            });
    }
    void load(json& camera) {
        offsetX = camera["offestX"];
        offsetY = camera["offestY"];
	}

private:
    Camera() : offsetX(0), offsetY(0) {}
    ~Camera() {}
   

    float offsetX;
    float offsetY;
};
