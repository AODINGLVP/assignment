#include "Hero.h"
#include "Bullet.h"
#include "enemiesmanager.h"
void Hero::shot(float dt,Hero &hero) {
	cooldown += dt;

	if (cooldown >= 0.5f) {
		length = 10000;
		cloest = -1;
		cooldown -= 0.5f;
		Bullet* bullet = new Bullet();
		bullet->transform.SetPosition(this->transform.GetPositionX() + 40, this->transform.GetPositionY() + 60);

		for (int i = 0; i < enemiesmanager::getInstance().getcount(); i++) {
			if (length >= sqrt(getDistance(this, enemiesmanager::getInstance().getenemies()[i]))) {

				cloest = i;
				length = sqrt(getDistance(this, enemiesmanager::getInstance().getenemies()[i]));
			}
		}
		if (cloest != -1)
		bullet->setdirection(getDirectionX(this, enemiesmanager::getInstance().getenemies()[cloest]),getDirectionY(this, enemiesmanager::getInstance().getenemies()[cloest]));
		

	}

}