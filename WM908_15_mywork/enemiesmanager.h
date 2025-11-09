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
using json = nlohmann::json;

class enemiesmanager
{
public:
    
    int credit = 0;
    static enemiesmanager& getInstance() {
        static enemiesmanager instance;
        return instance;
    }//singleton pattern
    void save(json& obj)  {
        obj.push_back({
            {"Tag","enemiesmanager"},
            {"timecounttotal",timecounttotal},
            {"cooldown",cooldown},
            {"timecount",timecount }
            });
    }
    float& gettimecounttotalreference() {
        return timecounttotal;
    }
    float& getcooldownreference() {
        return cooldown;
    }
    float& gettimecountreference() {
        return timecount;
    }
    //reduce enemy spawn interval with time flow
    void changecodwon(float cd) {
        timecounttotal += cd;
        if (timecounttotal >= 18.f) {
            timecounttotal -= 18.f;
				cooldown -= 0.3f;
        }

    }
    void add(enemy* obj) {
        if (count >= capacity)
            expand();
        //auto expand
        enemies[count++] = obj;
    }
    void setcooldown(float scv) {
        cooldown = scv;
        timecounttotal = 0;
    }
    float getcooldown() {
        return cooldown;
    }
    void remove(enemy* obj) {
        credit += 5;
        for (int i = 0; i < count; i++) {
            if (enemies[i] == obj) {
                for (int j = i; j < count - 1; j++)
                    enemies[j] = enemies[j + 1];
                enemies[count - 1] = nullptr;
                count--;
                break;
            }
        }
    }//remove dead enemies
    void createenemy(float x, float y, float speed, int health, int damage);
	void createnemyfastmovespeed(float x, float y, float speed, int health, int damage);
	void createnemymorehealth(float x, float y, float speed, int health, int damage);
	void createnemymoredamage(float x, float y, float speed, int health, int damage);
    void createnemyarchr(float x, float y, float speed, int health, int damage);
    void killsomeenemies(int n) {
        //Hero's AOE
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
            //find the highest-NPCS
            if (beenkilled != -1) {
                enemy* scv = enemies[beenkilled];

                GameObjectManager::getInstance().remove(enemies[beenkilled]);
                remove(enemies[beenkilled]);
                delete scv;
            }
            //if have NPC in the game,kill the highest-NPCs
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
                createnemyarchr(Hero::getInstance().transform.GetPositionX() , Hero::getInstance().transform.GetPositionY(), 1, 1, 1);
            }
           //create different types enemy 
        }
        for (int i = 0; i < count; i++) {
            //calculate the new position
			if (enemies[i]->Tag != "Archr")
            enemies[i]->transform.SetPosition(enemies[i]->transform.GetPositionX() +( getDirectionX(enemies[i], &Hero::getInstance()) *dt*enemies[i]->getmovespeed()),  enemies[i]->transform.GetPositionY() + (getDirectionY(enemies[i], &Hero::getInstance()) * dt  * enemies[i]->getmovespeed()));
            //the special rule for archer,it will move when hero beyond its range.
            else if(enemies[i]->Tag == "Archr") {
                if (getDistance(enemies[i], &Hero::getInstance()) >= 800) {
                    enemies[i]->transform.SetPosition(enemies[i]->transform.GetPositionX() + (getDirectionX(enemies[i], &Hero::getInstance()) * dt * enemies[i]->getmovespeed()), enemies[i]->transform.GetPositionY() +(getDirectionY(enemies[i], &Hero::getInstance())* dt * enemies[i]->getmovespeed()));
                }
                else {
                    enemies[i]->updatetime(dt);
                    //update archer shot interval
                }
            }
            enemies[i]->Update();
            //update collision box
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
    int creatcount = 0;
	int count;
	int capacity;
    float timecount=0.f;
	float cooldown = 2.f;
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

