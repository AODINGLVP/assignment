#pragma once
#include "GameObject.h"


class GameObjectManager {
public:
    static GameObjectManager& getInstance() {
        static GameObjectManager instance;
        return instance;
    }

    void add(GameObject* obj) {
        if (count >= capacity)
            expand();
        objects[count++] = obj;
    }

    void remove(GameObject* obj) {
        for (int i = 0; i < count; i++) {
            if (objects[i] == obj) {
                // 移动数组元素覆盖删除对象
                for (int j = i; j < count - 1; j++)
                    objects[j] = objects[j + 1];
                objects[count - 1] = nullptr;
                count--;
                break;
            }
        }
    }

    void UpdateAll(float dt) {
        for (int i = 0; i < count; i++) {
            if (objects[i]) {
                objects[i]->Update(dt);
               
            }
        }
    }
     GameObject** getobjects() {
		return objects;
    }
     int GetCount() {
         return count;
     }

private:
    GameObjectManager() {
        objects = new GameObject * [capacity]();
    }

    ~GameObjectManager() {
        delete[] objects; // 如果管理器不负责对象生命周期
    }

    void expand() {
        capacity *= 2;
        GameObject** newArray = new GameObject * [capacity]();
        for (int i = 0; i < count; i++)
            newArray[i] = objects[i];
        delete[] objects;
        objects = newArray;
    }

    GameObjectManager(const GameObjectManager&) = delete;
    GameObjectManager& operator=(const GameObjectManager&) = delete;

    GameObject** objects;
    int count = 0;
    int capacity = 100;
};
