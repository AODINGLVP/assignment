class Hero;
#pragma once
#include "Bullet.h"
#include "json.hpp"
class Bulletmanager
{
public:
	static Bulletmanager& getInstance() {
		static Bulletmanager instance;
		return instance;
	}//singleton pattern
	void add(Bullet* bullet) {
		if (count >= capacity) {
			expand();
			//check capacity and auto expand
			
		}
		bullets[count++] = bullet;
	}
	void remove(Bullet* bullet) {
		for (int i = 0; i < count; i++) {
			if (bullets[i] == bullet) {
				for(int j=i; j < count - 1; j++) {
					bullets[j] = bullets[j + 1];
				}
				
				bullets[count - 1] = nullptr;
				count--;
				
				return;
			}
		}
	}//remove bullet 
	void expand() {
		capacity *= 2;
		Bullet** newBullets = new Bullet * [capacity]();
		for (int i = 0; i < count; i++) {
			newBullets[i] = bullets[i];
		}
		delete[] bullets;
		bullets = newBullets;
	}//expand capacity
		

		void updateAll(float dt) {
			for (int i = 0; i < count; i++) {
				bullets[i]->move(dt);
				bullets[i]->updatelifetime(dt);
				//update position and remaing time for every bullet
			}
			
		}
		void delatemyself() {
			
				count = 0;

			
		}
		

	
private:
	Bulletmanager() {
		bullets = new Bullet * [capacity]();
		
		
	}
		;
	Bullet** bullets;
	int count = 0;
	int capacity = 100;
	



};

