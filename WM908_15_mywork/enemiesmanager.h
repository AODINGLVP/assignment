class Hero;
#pragma once
#include "enemy.h"
#include "Hero.h"
#include<iostream>
#include "GameObjectManager.h"
#include <cmath>
#include <random>
using namespace std;

class enemiesmanager
{
public:
    static enemiesmanager& getInstance() {
        static enemiesmanager instance;
        return instance;
    }

    void add(enemy* obj) {
        if (count >= capacity)
            expand();
        enemies[count++] = obj;
    }

    void remove(enemy* obj) {
        for (int i = 0; i < count; i++) {
            if (enemies[i] == obj) {
                // 移动数组元素覆盖删除对象
                for (int j = i; j < count - 1; j++)
                    enemies[j] = enemies[j + 1];
                enemies[count - 1] = nullptr;
                count--;
                break;
            }
        }
    }
    void createenemy(float x, float y, float speed, int health, int damage);
    enemy** getenemies() {
        return enemies;
	}
    int getcount() {
        return count;
	}
    void updateall(float dt) {
		timecount += dt;
        if (timecount >= cooldown) {
			timecount -= cooldown;
			createenemy(Hero::getInstance().transform.GetPositionX() + 100, Hero::getInstance().transform.GetPositionY() + 100, 50.f, 100, 5);
        }
        for (int i = 0; i < count; i++) {

			enemies[i]->transform.SetPosition(enemies[i]->transform.GetPositionX() +( getDirectionX(enemies[i], &Hero::getInstance())*dt*enemies[i]->getmovespeed()), enemies[i]->transform.GetPositionY() + (getDirectionY(enemies[i], &Hero::getInstance()) * dt * enemies[i]->getmovespeed()));
            for (int j = 0; j < count; j++) {
                if (j != i) {
                    enemies[i]->Update();
                    if (enemies[i]->collision.isColliding(enemies[i]->collision, enemies[j]->collision)) {
                        enemies[i]->transform.SetPosition(enemies[i]->transform.GetPositionX() - (getDirectionX(enemies[i], &Hero::getInstance()) * dt * enemies[i]->getmovespeed()), enemies[i]->transform.GetPositionY() - (getDirectionY(enemies[i], &Hero::getInstance()) * dt * enemies[i]->getmovespeed()));
                        enemies[i]->Update();
                    }
                }
            }
            if (enemies[i]->dead()) {
                enemy* scv = enemies[i];

                GameObjectManager::getInstance().remove(enemies[i]);
                remove(enemies[i]);
                delete scv;
            }
        }
    }
	
    ~enemiesmanager() {};
private:
	int count;
	int capacity;
    float timecount=0.f;
	float cooldown = 3.f;
	enemy** enemies;
	enemiesmanager() {
		capacity = 100;
		count = 0;
		enemies = new enemy * [capacity];
	};
	void expand() {
		capacity *= 2;
		enemy** newArray = new enemy * [capacity]();
		for (int i = 0; i < count; i++)
			newArray[i] = enemies[i];
		delete[] enemies;
        enemies = newArray;
	}
    float getDirectionX(GameObject* A, GameObject* B) {
		float x = B->transform.GetPositionX() - A->transform.GetPositionX();
        float y = B->transform.GetPositionY() - A->transform.GetPositionY();
		float length = sqrt(x * x + y * y);
		return x / length;


    }
    float getDirectionY(GameObject* A, GameObject* B) {
        float x = B->transform.GetPositionX() - A->transform.GetPositionX();
        float y = B->transform.GetPositionY() - A->transform.GetPositionY();
        float length = sqrt(x * x + y * y);
        return y / length;


    }


};

