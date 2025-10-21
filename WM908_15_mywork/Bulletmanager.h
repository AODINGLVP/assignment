#pragma once
#include "Bullet.h"
class Bulletmanager
{
public:
	static Bulletmanager& getInstance() {
		static Bulletmanager instance;
		return instance;
	}
	void add(Bullet* bullet) {
		if (count >= capacity) {
			expand();
			
		}
		bullets[count++] = bullet;
	}
	void remove(Bullet* bullet) {
		for (int i = 0; i < count; i++) {
			if (bullets[i] == bullet) {
				for(int j=i; j < count - 1; j++) {
					bullets[j] = bullets[j + 1];
				}
				//cout << "Removing bullet at index " << i << endl;
				bullets[count - 1] = nullptr;
				count--;
				
				return;
			}
		}
	}
	void expand() {
		capacity *= 2;
		Bullet** newBullets = new Bullet * [capacity]();
		for (int i = 0; i < count; i++) {
			newBullets[i] = bullets[i];
		}
		delete[] bullets;
		bullets = newBullets;
	}
		//~Bulletmanager();

		void updateAll(float dt) {
			for (int i = 0; i < count; i++) {
				bullets[i]->updatelifetime(dt);
				bullets[i]->move(dt);
			}
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

