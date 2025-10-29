#include "enemy.h"
#include "enemiesmanager.h"
void enemy::enemyregister(enemy* obj) {
	enemiesmanager::getInstance().add(obj);
}


