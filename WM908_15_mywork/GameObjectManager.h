#pragma once
#include "GameObject.h"
#include<iostream>
using namespace std;


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
               // delete obj;
				//obj = nullptr;
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
                if (i == 1) {
                  
                }
                objects[i]->Update(dt);
                
               
            }
        }
        for(int i=0;i<count;i++){

            for (int j = 0; j < count; j++) {
                if (objects[i]->Tag == "hero") {
                    if (objects[j]->Tag == "enemy") {
                        if(objects[i]->collision.isColliding(objects[i]->collision,objects[j]->collision)) {
                            objects[i]->makedamage(5);
							cout << "hero hit" << endl;
                            //something happed
						}
                      
                        //something happed
                    }
                }
                if (objects[i]->Tag == "bullet") {
                    if( objects[j]->Tag == "enemy") {
                        if (objects[i]->collision.isColliding(objects[i]->collision, objects[j]->collision)) {
                           objects[j]->makedamage(5);
						   objects[i]->suicide();
                           if (objects[i] != nullptr) {//在子弹被删除后判断他是不是最后一个obj，如过不是跳过这个循环并从原来的位置继续
                               i--;
                           }
                           break;
                            //something happed
                        }
                        //something happed
					}
                }
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
