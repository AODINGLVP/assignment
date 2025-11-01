class Hero;
#pragma once
#include "enemy.h"
#include "Hero.h"
#include<iostream>
#include "GameObjectManager.h"
#include <cmath>
#include <random>
#include "enemy_fastspeed.h"
#include "enemy_morehealth.h"
#include "enemy_moredamage.h"
#include "Archr.h" 
using namespace std;

class enemiesmanager
{
public:
    int credit = 0;
    static enemiesmanager& getInstance() {
        static enemiesmanager instance;
        return instance;
    }
    void changecodwon(float cd) {//随着时间减少敌人刷新cd
        timecounttotal += cd;
        if (timecounttotal >= 25.f) {
            timecounttotal -= 25.f;
				cooldown -= 0.3f;
        }

    }
    void add(enemy* obj) {
        if (count >= capacity)
            expand();
        enemies[count++] = obj;
    }

    void remove(enemy* obj) {
        credit += 5;
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
	void createnemyfastmovespeed(float x, float y, float speed, int health, int damage);
	void createnemymorehealth(float x, float y, float speed, int health, int damage);
	void createnemymoredamage(float x, float y, float speed, int health, int damage);
    void createnemyarchr(float x, float y, float speed, int health, int damage);
    void killsomeenemies(int n) {
        int maxhelath = -1;
        int beenkilled=-1;
        for (int i = 0; i < n; i++) {
            maxhelath = -1;
            for (int j = 0; j < count; j++) {
                if(enemies[j]->gethealth() > maxhelath) {
                    maxhelath = enemies[j]->gethealth();
                    beenkilled = j;
				}

            }
            if (beenkilled != -1) {
                enemy* scv = enemies[beenkilled];

                GameObjectManager::getInstance().remove(enemies[beenkilled]);
                remove(enemies[beenkilled]);
                delete scv;
            }
      }

    }
    enemy** getenemies() {
        return enemies;
	}
    int getcount() {
        return count;
	}
    void delatemyself() {
        
            count = 0;

        
    }
    void updateall(float dt) {
		changecodwon(dt);
		timecount += dt;
        if (timecount >= cooldown) {
            creatcount++;
			timecount -= cooldown;
            if (creatcount % 4 == 0) {
                createnemyfastmovespeed(Hero::getInstance().transform.GetPositionX() + 100, Hero::getInstance().transform.GetPositionY() + 100, 1, 1, 1);
            }
            else if (creatcount % 4 == 1) {
                createnemymorehealth(Hero::getInstance().transform.GetPositionX() + 100, Hero::getInstance().transform.GetPositionY() + 100, 1, 1, 1);
            }
            else if(creatcount%4==2) {
                createnemymoredamage(Hero::getInstance().transform.GetPositionX() + 100, Hero::getInstance().transform.GetPositionY() + 100, 1, 1, 1);
            }
            else {
                createnemyarchr(Hero::getInstance().transform.GetPositionX() + 100, Hero::getInstance().transform.GetPositionY() + 100, 1, 1, 1);
            }


           
           // createenemy(Hero::getInstance().transform.GetPositionX() + 100, Hero::getInstance().transform.GetPositionY() + 100, 50.f, 100, 5);
        }
        for (int i = 0; i < count; i++) {

			if (enemies[i]->Tag != "Archr")
            enemies[i]->transform.SetPosition(enemies[i]->transform.GetPositionX() +( getDirectionX(enemies[i], &Hero::getInstance())*dt*enemies[i]->getmovespeed()), enemies[i]->transform.GetPositionY() + (getDirectionY(enemies[i], &Hero::getInstance()) * dt * enemies[i]->getmovespeed()));
            else if(enemies[i]->Tag == "Archr") {
                if (getDistance(enemies[i], &Hero::getInstance()) >= 800) {
                    enemies[i]->transform.SetPosition(enemies[i]->transform.GetPositionX() + (getDirectionX(enemies[i], &Hero::getInstance()) * dt * enemies[i]->getmovespeed()), enemies[i]->transform.GetPositionY() + (getDirectionY(enemies[i], &Hero::getInstance()) * dt * enemies[i]->getmovespeed()));
                }
                else {
                    enemies[i]->updatetime(dt);
                }
            }
            enemies[i]->Update();
           /*for (int j = 0; j < count; j++) {
                if (j != i) {
                    enemies[i]->Update();
                    if (enemies[i]->collision.isColliding(enemies[i]->collision, enemies[j]->collision)) {
                        enemies[i]->transform.SetPosition(enemies[i]->transform.GetPositionX() - (getDirectionX(enemies[i], &Hero::getInstance()) * dt * enemies[i]->getmovespeed()), enemies[i]->transform.GetPositionY() - (getDirectionY(enemies[i], &Hero::getInstance()) * dt * enemies[i]->getmovespeed()));
                        enemies[i]->Update();
                    }
                }
            }*/
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
    int creatcount = 0;
	int count;
	int capacity;
    float timecount=0.f;
	float cooldown = 3.f;
    float timecounttotal = 0.f;
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
    float getDistance(GameObject* A, GameObject* B) {
        float x = B->transform.GetPositionX() - A->transform.GetPositionX();
        float y = B->transform.GetPositionY() - A->transform.GetPositionY();
        float length = sqrt(x * x + y * y);
        return length;


    }


};

