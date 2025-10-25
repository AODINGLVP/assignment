#pragma once
#include <mutex>

class Camera
{
public:
    // 获取唯一实例
    
    

    static Camera& GetCamera()
    {
        static Camera camera; 
        return camera;
    }

    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

    // 移动摄像机
    void Move(float dx, float dy)
    {
        offsetX += dx;
        offsetY += dy;
    }

    // 设置位置
    void SetPosition(float x, float y)
    {
        offsetX = x;
        offsetY = y;
    }

    // 获取位置
    float GetX()  {
        return offsetX;
    }
    float GetY()  {
        return offsetY;
    }

private:
    Camera() : offsetX(0), offsetY(0) {}
    ~Camera() {}
   

    float offsetX;
    float offsetY;
};
