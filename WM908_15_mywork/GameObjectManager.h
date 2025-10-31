#pragma once
#include "GameObject.h"
#include<iostream>
#include "Camera.h"
#include <json.hpp>
#include "Archr.h"
#include "Bullet.h"
#include "enemy.h"
#include "Enemybullet.h"
#include "enemy_fastspeed.h"
#include "enemy_moredamage.h"
#include "enemy_morehealth.h"
#include "Water.h"
#include "Hero.h"
#include "powerup_lineattack.h"
#include "powerup_maxnumber.h"

using json = nlohmann::json;
using namespace std;


class GameObjectManager {
public:
	int scvcount1 = 0;
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
	bool checkwater() {
		for (int i = 0; i < count; i++) {
			if (objects[i]->Tag == "hero") {
				for (int j = 0; j < count; j++) {
					if (objects[j]->Tag == "water") {
						if (objects[i]->collision.isColliding(objects[i]->collision, objects[j]->collision)) {
							return true;
						}
					}

				}
			}

		}
		return false;
	}

	void UpdateAll(float dt) {
		scvcount1++;

		for (int i = 0; i < count; i++) {
			if (objects[i]) {
				objects[i]->Update(dt, camera);
			}
			if (objects[i]->Tag == "water") {
				continue;
			}
			if (objects[i]->Tag == "Enemybullet") {
				continue;
			}
			if (objects[i]->Tag == "enemy") {
				continue;
			}
			for (int j = 0; j < count; j++) {
				if (objects[j]->Tag == "water") {
					continue;
					continue;
				}
				if (objects[i]->Tag == "hero") {
					if (objects[j]->Tag == "powerup_maxnumber" && objects[i]->collision.isColliding(objects[i]->collision, objects[j]->collision)) {
						Hero::getInstance().changemax(1);
						remove(objects[j]);
						if (objects[j] == nullptr) {//在object被删除后判断他是不是最后一个obj，如过不是跳过这个循环并从原来的位置继续
							break;
						}
						else {
							j--;
						}
					}
					if (objects[j]->Tag == "powerup_lineattack" && objects[i]->collision.isColliding(objects[i]->collision, objects[j]->collision)) {
						Hero::getInstance().changecooldown(0.1);
						Hero::getInstance().addbulletmovespeed(50);
						remove(objects[j]);
						if (objects[j] == nullptr) {//在object被删除后判断他是不是最后一个obj，如过不是跳过这个循环并从原来的位置继续
							break;
						}
						else {
							j--;
						}
					}
					if (objects[j]->Tag == "Enemybullet") {
						if (objects[i]->collision.isColliding(objects[i]->collision, objects[j]->collision)) {
							objects[i]->makedamage(5);
							objects[j]->suicide();
							if (objects[j] == nullptr) {//在子弹被删除后判断他是不是最后一个obj，如过不是跳过这个循环并从原来的位置继续
								break;
							}
							else {
								j--;
							}
						}

					}
					if (objects[j]->Tag == "enemy") {
						if (objects[i]->collision.isColliding(objects[i]->collision, objects[j]->collision)) {
							objects[i]->makedamage(5);

						}

						//something happed
					}
				}
				if (objects[i]->Tag == "bullet") {
					if (objects[j]->Tag == "enemy" || objects[j]->Tag == "Archr") {
						if (objects[i]->collision.isColliding(objects[i]->collision, objects[j]->collision)) {
							objects[j]->makedamage(Hero::getInstance().getdamage());
							objects[i]->suicide();
							if (objects[i] == nullptr) {//在子弹被删除后判断他是不是最后一个obj，如过不是跳过这个循环并从原来的位置继续
								break;

							}
							else {
								i--;
							}

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
	void saveall(json& obj) {
		for (int i = 0; i < count; i++) {
			objects[i]->save(obj);
		}
		Camera::GetCamera().save(obj);
	}
	void loadall(json& obj) {
		
		for (int i = 0; i < count; i++) {

			if (objects[i]->Tag == "hero") {
				objects[0] = objects[i];
				if (i != 0)
					objects[i] = nullptr;
		
			}
			else {
				objects[i] = nullptr;
			}
			 
			
			

		}
		count = 1;
		for (json e : obj) {
			if (e["Tag"] == "Archr") {
				GameObject* scv = new Archr(e["position_x"],e["position_y"]);
				scv->load(e);
			}
			else if (e["Tag"] == "bullet") {
				GameObject* scv = new Bullet();
				scv->load(e);
			}
			else if (e["Tag"] == "Enemybullet") {
				GameObject* scv = new Enemybullet();
				scv->load(e);
			}
			else if (e["Tag"] == "enemy_morehealth") {
				GameObject* scv = new enemy_morehealth(e["position_x"],e["position_y"]);
				scv->load(e);
			}
			else if (e["Tag" ] == "enemy_moredamage") {
				GameObject* scv = new enemy_moredamage(e["position_x"], e["position_y"]);
				scv->load(e);
			}
			else if (e["Tag"] == "enemy_fastspeed") {
				GameObject* scv = new enemy_fastspeed(e["position_x"], e["position_y"]);
				scv->load(e);
			}
			else if (e["Tag" == "powerup_maxnumber"]) {
				GameObject* scv = new powerup_maxnumber(e["position_x"], e["position_y"]);

			}
			else if (e["Tag" == "powerup_lineattack"]) {
				GameObject* scv = new powerup_lineattack(e["position_x"], e["position_y"]);

			}
			else if (e["Tag"] == "water") {
				GameObject* scv = new Water();
				scv->load(e);
			}
			else if (e["Tag"] == "hero") {
				
				Hero::getInstance().load(e);
			}
			else if (e["Tag"] == "camera") {
				
				Camera::GetCamera().load(e);
			}
			
			

		}
		
		
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
	Camera& camera = Camera::GetCamera();
	GameObject** objects;
	int count = 0;
	int capacity = 100;
};
