#include "enemiesmanager.h"
#include <random>
#include <cmath>
float getrandom(float &a,float &b);

void enemiesmanager::createenemy(float x, float y, float speed, int health, int damage) {
    getrandom(x, y);

    enemy* newEnemy = new enemy(x,y, speed, health, damage);
    
    cout << "Enemy created at (" << x << "," << y << ") with speed " << speed << ", health " << health << ", damage " << damage << endl;
  
}
void enemiesmanager::createnemyfastmovespeed(float x, float y, float speed, int health, int damage) {
    getrandom(x, y);
    enemy* scv1 = new enemy_fastspeed(x, y);
    
   
    
 
    
    
}
void enemiesmanager::createnemymorehealth(float x, float y, float speed, int health, int damage) {
    getrandom(x, y);
    enemy* scv2 = new enemy_morehealth(x, y);
   
}
void enemiesmanager::createnemymoredamage(float x, float y, float speed, int health, int damage) {
    getrandom(x, y);
    enemy* scv3 = new enemy_moredamage(x, y);

    
}
void enemiesmanager::createnemyarchr(float x, float y, float speed, int health, int damage) {
    getrandom(x, y);
    enemy* scv3 = new Archr(x, y);

  
}



float getrandom(float &a,float &b) {
    random_device rd;
    mt19937 gen(rd()); // 梅森旋转算法（高质量随机数引擎）

    // 整数分布 [0, 99]
    uniform_int_distribution<> distInt(0, 99);
    

    // 浮点数分布 [0.0, 1.0]
    uniform_real_distribution<float> distFloat(a+1500.f, a+2000.f);
    uniform_real_distribution<float> distFloat1(-1.f, 1.f);
    float x = distFloat1(gen);
    float y = sqrt(1 - (x * x));
    a = x * distFloat(gen);
    b = y * distFloat(gen);
	return 0;
  
  

}