#include "GameObject.h"
#include"GameObjectManager.h"
void GameObject::registerobj(GameObject* obj) {

	GameObjectManager::getInstance().add(obj);
}
void GameObject::removeobj(GameObject* obj) {
	GameObjectManager::getInstance().remove(obj);
}