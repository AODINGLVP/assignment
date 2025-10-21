#include "Bullet.h"
#include "Bulletmanager.h"

void Bullet::regisetbulletmanager(Bullet* bullet) {
	Bulletmanager::getInstance().add(bullet);

}
void Bullet::removed(Bullet* bullet) {
	Bulletmanager::getInstance().remove(bullet);
	


}
