#include "Hero.h"
#include "Bullet.h"
#include "enemiesmanager.h"
void Hero::shot(float dt,Hero &hero) {
	shottimecount += dt;

	if (shottimecount >= cooldown) {
		length = 10000;
		cloest = -1;
		shottimecount = 0;
		Bullet* bullet = new Bullet();
		bullet->transform.SetPosition
		(this->transform.GetPositionX() + 40, 
		this->transform.GetPositionY() + 60);
		//make sure the new bullet be made in the middle of hero
		for (int i = 0; i < enemiesmanager::getInstance().getcount(); i++) {
			if (length >= sqrt(getDistance
			(this, enemiesmanager::getInstance().getenemies()[i]))) {

				cloest = i;
				length = sqrt(getDistance
				(this, enemiesmanager::getInstance().getenemies()[i]));
			}
		}
		//find the closet enemy
		if (cloest != -1)
		bullet->setdirection(getDirectionX(this, enemiesmanager::getInstance().getenemies()[cloest]),
			getDirectionY(this, enemiesmanager::getInstance().getenemies()[cloest]));
		bullet->setmovespeed(hero.getbulletmovespeed());
		

	}

}