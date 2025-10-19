#pragma once
#include <mutex>

class Camera
{
public:
    // 获取唯一实例
    Camera camera() {
		
  }
    

    static Camera& GetCamera()
    {
        static Camera camera; 
        return camera;
    }

   

    // 移动摄像机
    void Move(int dx, int dy)
    {
        offsetX += dx;
        offsetY += dy;
    }

    // 设置位置
    void SetPosition(int x, int y)
    {
        offsetX = x;
        offsetY = y;
    }

    // 获取位置
    int GetX() const { 
        return offsetX;
    }
    int GetY() const { 
        return offsetY;
    }

private:
    Camera() {}             
    ~Camera() {}
   

    int offsetX = 0;
    int offsetY = 0;
};
