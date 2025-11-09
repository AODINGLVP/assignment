#include "enemiesmanager.h"
#include <random>
#include <cmath>
float getrandom(float &a,float &b);

void enemiesmanager::createenemy(float x, float y, float speed, int health, int damage) {
    getrandom(x, y);
    // it not been used
    enemy* newEnemy = new enemy(x,y, speed, health, damage);
    
    cout << "Enemy created at (" << x << "," << y << ") with speed " << speed << ", health " << health << ", damage " << damage << endl;
  
}
void enemiesmanager::createnemyfastmovespeed(float x, float y, float speed, int health, int damage) {
    getrandom(x, y);
    enemy* scv1 = new enemy_fastspeed(x, y);
    //create enemy type 1 
   
    
 
    
    
}
void enemiesmanager::createnemymorehealth(float x, float y, float speed, int health, int damage) {
    getrandom(x, y);
    enemy* scv2 = new enemy_morehealth(x, y);
    //create enemy type 2
}
void enemiesmanager::createnemymoredamage(float x, float y, float speed, int health, int damage) {
    getrandom(x, y);
    enemy* scv3 = new enemy_moredamage(x, y);
    //create enemy type 3
    
}
void enemiesmanager::createnemyarchr(float x, float y,float speed, int health, int damage) {
    getrandom(x, y);
    enemy* scv4 = new Archr(x, y);
    //create enemy type 4
  
}



float getrandom(float &a,float &b) {
    //Directly modify the given x and y coordinates
    random_device rd;
    mt19937 gen(rd()); 

    
    uniform_int_distribution<> distInt(0, 99);
    

    
    uniform_real_distribution<float> 
        distFloat(a+1500.f, a+2000.f);
    uniform_real_distribution<float>
        distFloat1(-1.f, 1.f);
    uniform_real_distribution<float>
        distint(0,1);
    float x = distFloat1(gen);
    float y = sqrt(1 - (x * x));
    if (distint(gen) == 1) {
        y = -y;
    }
    //Calculate the unit vector of y based on x
    a = x * distFloat(gen);
    b = y * distFloat(gen);
	return 0;
  
  

}