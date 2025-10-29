#include "enemiesmanager.h"
#include <random>
float getrandom(float a);

void enemiesmanager::createenemy(float x, float y, float speed, int health, int damage) {
    
    enemy* newEnemy = new enemy(getrandom(x), getrandom(y), speed, health, damage);
    
    cout << "Enemy created at (" << x << "," << y << ") with speed " << speed << ", health " << health << ", damage " << damage << endl;
  
}
void enemiesmanager::createnemyfastmovespeed(float x, float y, float speed, int health, int damage) {
    enemy* scv1 = new enemy_fastspeed(getrandom(x), getrandom(y));
    
   
    
 
    
    
}
void enemiesmanager::createnemymorehealth(float x, float y, float speed, int health, int damage) {
    enemy* scv2 = new enemy_morehealth(getrandom(x), getrandom(y));
   
}
void enemiesmanager::createnemymoredamage(float x, float y, float speed, int health, int damage) {
    enemy* scv3 = new enemy_moredamage(getrandom(x), getrandom(y));

    
}
void enemiesmanager::createnemyarchr(float x, float y, float speed, int health, int damage) {
    enemy* scv3 = new Archr(getrandom(x), getrandom(y));

  
}



float getrandom(float a) {
    random_device rd;
    mt19937 gen(rd()); // 梅森旋转算法（高质量随机数引擎）

    // 整数分布 [0, 99]
    uniform_int_distribution<> distInt(0, 99);
    

    // 浮点数分布 [0.0, 1.0]
    uniform_real_distribution<float> distFloat(a+1000.f, a+2000.f);
    uniform_real_distribution<float> distFloat1(-1.f, 1.f);
	return distFloat(gen) * distFloat1(gen);
  

}