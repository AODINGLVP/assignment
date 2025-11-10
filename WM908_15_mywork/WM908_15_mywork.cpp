/*
MIT License

Copyright (c) 2024 MSc Games Engineering Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
int scvcount = 0;
#include <thread>
#include"GameObject.h"
#include"Hero.h"
#include<iostream>
#include<fstream>
#include<string>
#include "Camera.h"
#include "GamesEngineeringBase.h" // Include the GamesEngineeringBase header
#include"GameObjectManager.h"
#include "Bulletmanager.h"
#include "Bullet.h"
#include "enemiesmanager.h"
#include "Water.h"
#include <memory>
#include <windows.h>
#include "json.hpp"
using json = nlohmann::json;


float presscount = 0.f;
bool press = false;
void timecountthread() {
	//is for avoid the Keyboard mis-click
	GamesEngineeringBase::Timer scv;
	while (1) {
		presscount -= scv.dt();
		if (presscount <= -0.3f && press) {
			press = false;
		}
		
	}



}

void draw_numbers(float x, float y, GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image& image, int number);
bool scvtest = true;
void draw_object(GamesEngineeringBase::Window& canvas, GameObject** obj, int count);
void draw_title(int x, int y, GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image& image);
void draw_entire_background(int** mapsave1, GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image* tiles, int** offestmapx, int** offextmapy, Water*** watermap);
void controlHero(Hero& hero, GamesEngineeringBase::Window& canvas, float move);
void draw_collision(GameObject& gameobject, GamesEngineeringBase::Window& canvas);
void camera_draw(float x, float y, GamesEngineeringBase::Image& image, GamesEngineeringBase::Window& canvas, GameObject* obj);
void changemao(Hero& hero, int** mapmapoffestx, int** mapoffesty);
using namespace std;

int main() {
	thread t(timecountthread);
	float gametimecount=120.f;
	bool winorlose=true;
	int loadpagechose = 3;
	bool goload = false;
	
	int stage = 1;
	json data;

	HRESULT hr = CoInitialize(NULL);
	//  initialize COM ,in fact ,pictures will disappera if I don't do that


	GameObjectManager& gameobjectmanager = GameObjectManager::getInstance();
	Bulletmanager& bulletmanager = Bulletmanager::getInstance();

	Hero& hero = Hero::getInstance();

	enemiesmanager& enemymanager = enemiesmanager::getInstance();
	Camera& camera = Camera::GetCamera();
	
	GamesEngineeringBase::Image tiles[24];
	for (int i = 0; i < 24; i++) {
		tiles[i].load("../Resources/" + to_string(i) + ".png");

	}
	//load tiles


	GamesEngineeringBase::Image image;
	GamesEngineeringBase::Image welcome_page;
	GamesEngineeringBase::Image lose_page;
	GamesEngineeringBase::Image win_page;
	GamesEngineeringBase::Image load_page;
	GamesEngineeringBase::Image save_page;
	GamesEngineeringBase::Image chose_page;
	GamesEngineeringBase::Image number;
	GamesEngineeringBase::Image Creditsshow;
	GamesEngineeringBase::Image FPSshow;
	GamesEngineeringBase::Image healthshow;
	GamesEngineeringBase::Image aoeshow;
	GamesEngineeringBase::Image Tshow;
	GamesEngineeringBase::Image Yshow;
	GamesEngineeringBase::Image TIMEshow;
	GamesEngineeringBase::Window canvas;

	image.load("../Resources/A.png");
	



	
	canvas.create(1280, 1280, "Tiles");

	bool running = true; 
	cout << canvas.getWidth() << "   " << canvas.getHeight();
	welcome_page.load("../Resources/welcome_page.png");
	lose_page.load("../Resources/lose_page.png");
	win_page.load("../Resources/win_page.png");
	load_page.load("../Resources/load_page.png");
	save_page.load("../Resources/save_page.png");
	chose_page.load("../Resources/chosepage.png");
	number.load("../Resources/number.png");
	Creditsshow.load("../Resources/Credits.png");
	FPSshow.load("../Resources/FPS.png");
	healthshow.load("../Resources/health.png");
	aoeshow.load("../Resources/aoeshow.png");
	Tshow.load("../Resources/Tshow.png");
	Yshow.load("../Resources/Yshow.png");
	TIMEshow.load("../Resources/TIME.png");





	while (1) {

		if (stage == 1) {//welcome page
			
			canvas.clear();
			
			if (canvas.keyPressed('Q') && !press) {
				gametimecount = 120.f;
				presscount = 0.2f;
				press = true;
				stage = 7;
				//go to chosen map page

			}
			if (canvas.keyPressed('W') && !press) {
				presscount = 0.2f;
				press = true;
				gametimecount = 120.f;
				stage = 5;
				goload = true;
				//go to load page

			}
			if (canvas.keyPressed('E')) {
				ExitProcess(0);
			}

			draw_title(0, 0, canvas, welcome_page);
			

			canvas.present();

		}
		else if (stage == 2) {//game over page
			canvas.clear();
			if (winorlose) {
				draw_title(0, 0, canvas, win_page);
			}
			else {
				draw_title(0, 0, canvas, lose_page);
			}
			//show different string to show win or lose
			
			if (canvas.keyPressed('Q') && !press) {
				gametimecount = 120.f;
				presscount = 0.2f;
				press = true;
				stage = 7;
				//to chosen map page

			}
			if (canvas.keyPressed('W') && !press) {
				presscount = 0.2f;
				press = true;
				stage = 5;
				goload = true;

			}
			//to load page
			if (canvas.keyPressed('E') && !press) {
				presscount = 0.2f;
				press = true;
				ExitProcess(0);
			}
			canvas.present();

		}
		
		else if (stage == 5) {// game page

			gameobjectmanager.delatemyself();
			bulletmanager.delatemyself();
			enemymanager.delatemyself();
			enemymanager.setcooldown(2.f);
			hero.cleartimecount();
			int showfps = 20;
			hero.setHealth(100);
			//initialize data
			Water*** watermap = new Water * *[42];
			for (int i = 0; i < 42; i++) {
				watermap[i] = new Water * [42];
				for (int j = 0; j < 42; j++) {
					watermap[i][j] = new Water; 
					watermap[i][j]->positionmap_x = i;
					watermap[i][j]->positionmap_y = j;
				}
			}
			//initialize water
			int** mapoffestx = new int* [100]();
			for (int i = 0; i < 100; i++)
				mapoffestx[i] = new int[100]();
			int** mapoffesty = new int* [100]();
			for (int i = 0; i < 100; i++)
				mapoffesty[i] = new int[100]();
			//initialize offset about map
			int** mapsave1 = new int* [42];
			for (int i = 0; i < 42; i++)
				mapsave1[i] = new int[42];
			//initialize the data about map
			GamesEngineeringBase::Timer timer;


			if (loadpagechose == 1 || loadpagechose == 3) {
				ifstream file("../Resources/tiles.txt");
				//load map1
				string line;
				for (int linenumber = 0; getline(file, line);) {
					if (linenumber >= 6) {
						//lins between 0-5 is other is the introduce of map
						int columnline = 0;
						int stack = -1;
						for (int i = 0; i < line.size(); i++) {
							if (line[i] == ',') {
								mapsave1[linenumber - 6][columnline] = stack;
								columnline++;
								stack = -1;
							}
							else {
								//calculate the number from string
								if (stack == -1) {
									stack = line[i] - '0';
								}
								else {
									stack = stack * 10 + (line[i] - '0');
								}
							}

						}
					}
					linenumber++;

				}
				file.close();
				for (int i = 0; i < 42; i++) {
					for (int j = 0; j < 42; j++) {

						if (mapsave1[i][j] >= 15 && mapsave1[i][j] <= 22) {
							watermap[i][j]->collision.SetCollision(0, 0, 32, 32);
							//active water
						}
						else {
							watermap[i][j]->collision.SetCollision(0, 0, 0, 0);
							watermap[i][j]->Active = false;
						}
					}
				}
			}
			else {
				ifstream file("../Resources/tiles1.txt");
				//load map2
				string line;
				for (int linenumber = 0; getline(file, line);) {
					if (linenumber >= 6) {
						int columnline = 0;
						int stack = -1;
						for (int i = 0; i < line.size(); i++) {
							if (line[i] == ',') {
								mapsave1[linenumber - 6][columnline] = stack;
								columnline++;
								stack = -1;
							}
							else {
								if (stack == -1) {
									stack = line[i] - '0';
								}
								else {
									stack = stack * 10 + (line[i] - '0');
								}
							}

						}
					}
					linenumber++;

				}
				file.close();
				for (int i = 0; i < 42; i++) {
					for (int j = 0; j < 42; j++) {

						if (mapsave1[i][j] >= 15 && mapsave1[i][j] <= 22) {
							watermap[i][j]->collision.SetCollision(0, 0, 32, 32);
						}
						else {
							watermap[i][j]->collision.SetCollision(0, 0, 0, 0);
							watermap[i][j]->Active = false;
						}
					}
				}
			}

			Hero& hero = Hero::getInstance();
			hero.transform.SetPosition(canvas.getWidth() / 2, canvas.getHeight() / 2);

			camera.SetPosition(hero.transform.GetPositionX()- (canvas.getWidth() / 2), hero.transform.GetPositionY()- (canvas.getHeight() / 2));
			//set position while subtracting the hero's initial position
			float dt = timer.dt();
			int move = hero.getMoveSpeed() * dt;
			int fps = 0;
			float fpsdtcount = 0;







			while (running)//game staet
			{
				if (canvas.keyPressed('T') && !press) {
					//to save page
					press = true;
					presscount = 0.2f;
					//is about avoid mistake press keyboard
					while (1) {

						dt = timer.dt();
						canvas.clear();
						draw_title(0, 0, canvas, save_page);
						if (canvas.keyPressed('Q') && !press) {
							press = true;
							presscount = 0.2f;
							//is about avoid mistake press keyboard
							ofstream loadfile("../load/sava1.json", std::ios::out | std::ios::trunc);
							//save to file 1
							GameObjectManager::getInstance().saveall(data);
							//save all gameobjects data
							data.push_back({
								{"Tag","mapchose"},
								{"loadpagechose",loadpagechose}
								});
							//save the screen that be chosed
							data.push_back({
								{"Tag","credit"},
								{"credit",enemymanager.credit}
								});
							//save sorces of the game
							data.push_back({
								{"Tag","gametimecount"},
								{"gametimecount",gametimecount}
								});
							//save remaing time
							enemymanager.save(data);
							//save data about enemymanage,such as the cooldown of creat enemy
							loadfile << data.dump(4);
							loadfile.close();
							data = json();
							//clear data
							break;
						}
						if (canvas.keyPressed('W') && !press) {
							press = true;
							presscount = 0.2f;
							//is about avoid mistake press keyboard
							ofstream loadfile("../load/sava2.json", std::ios::out | std::ios::trunc);
							//save to file 2
							GameObjectManager::getInstance().saveall(data);
							//save all gameobjects data
							data.push_back({
								{"Tag","mapchose"},
								{"loadpagechose",loadpagechose}
								});
							//save the screen that be chosed
							data.push_back({
								{"Tag","credit"},
								{"credit",enemymanager.credit}
								});
							//save sorces of the game
							data.push_back({
								{"Tag","gametimecount"},
								{"gametimecount",gametimecount}
								});
							//save remaing time
							enemymanager.save(data);
							//save data about enemymanage,such as the cooldown of creat enemy
							loadfile << data.dump(4);
							loadfile.close();
							data = json();
							//clear data
							break;
						}
						if (canvas.keyPressed('E') && !press) {
							press = true;
							presscount = 0.2f;
							//is about avoid mistake press keyboard
							ofstream loadfile("../load/sava3.json", std::ios::out | std::ios::trunc);
							//save to file 3
							GameObjectManager::getInstance().saveall(data);
							//save all gameobjects data
							data.push_back({
								{"Tag","mapchose"},
								{"loadpagechose",loadpagechose}
								});
							//save the screen that be chosed
							data.push_back({
								{"Tag","credit"},
								{"credit",enemymanager.credit}
								});
							//save sorces of the game
							data.push_back({
								{"Tag","gametimecount"},
								{"gametimecount",gametimecount}
								});
							//save remaing time
							enemymanager.save(data);
							//save data about enemymanage,such as the cooldown of creat enemy
							loadfile << data.dump(4);
							loadfile.close();
							data = json();
							//clear data
							break;
						}
						if (canvas.keyPressed('R')) {
							ExitProcess(0);
						}
						canvas.present();
					}

				}
				
				
				if (canvas.keyPressed('Y') || goload) {
					//go to load page
					press = true;
					presscount = 0.2f;
					goload = false;
					//it is about from welcome page or gamevoer page to here
					while (1) {
						canvas.clear();
						draw_title(0, 0, canvas, load_page);
						//draw the page
						if (canvas.keyPressed('Q') && !press) {
							presscount = 0.2f;
							press = true;


							std::ifstream in("../load/sava1.json");
							if (!in) {
								std::cerr << "error ../load/sava.json\n";
							}
							else {
								
									in >> data;
									//load data
								
								
								in.close();
								enemiesmanager::getInstance().delatemyself();
								Bulletmanager::getInstance().delatemyself();
								//make count to zero
								loadpagechose = GameObjectManager::getInstance().loadall(data,enemymanager.credit,gametimecount,enemymanager.gettimecounttotalreference(),enemymanager.getcooldownreference(),enemymanager.gettimecountreference());
								//clear gameobjects and load 
								if (loadpagechose == 1 || loadpagechose == 3) {
									//chose map from load and load to mapsave1
									ifstream file("../Resources/tiles.txt");
									
									string line;
									for (int linenumber = 0; getline(file, line);) {

										if (linenumber >= 6) {

											int columnline = 0;
											int stack = -1;
											for (int i = 0; i < line.size(); i++) {
												if (line[i] == ',') {
													mapsave1[linenumber - 6][columnline] = stack;
													columnline++;
													stack = -1;
												}
												else {
													if (stack == -1) {
														stack = line[i] - '0';
													}
													else {
														stack = stack * 10 + (line[i] - '0');
													}
												}

											}
										}
										linenumber++;

									}
									file.close();
								}
								else if (loadpagechose == 2 || loadpagechose == 4) {
									//chose map from load and load to mapsave1
									ifstream file("../Resources/tiles1.txt");
									
									string line;
									for (int linenumber = 0; getline(file, line);) {

										if (linenumber >= 6) {

											int columnline = 0;
											int stack = -1;
											for (int i = 0; i < line.size(); i++) {
												if (line[i] == ',') {
													mapsave1[linenumber - 6][columnline] = stack;
													columnline++;
													stack = -1;
												}
												else {
													if (stack == -1) {
														stack = line[i] - '0';
													}
													else {
														stack = stack * 10 + (line[i] - '0');
													}
												}

											}
										}
										linenumber++;

									}
									file.close();
								}
								for (int i = 0; i < gameobjectmanager.GetCount(); i++) {
									if (gameobjectmanager.getobjects()[i]->Tag == "water") {
										watermap[gameobjectmanager.getobjects()[i]->getmapx()][gameobjectmanager.getobjects()[i]->getmapy()] = dynamic_cast<Water*>(gameobjectmanager.getobjects()[i]);

									}
								}
								//load Water to watermap
								for (int i = 0; i < 42; i++) {
									for (int j = 0; j < 42; j++) {

										if (mapsave1[i][j] >= 15 && mapsave1[i][j] <= 22) {
											watermap[i][j]->collision.SetCollision(0, 0, 32, 32);
										}
										else {
											watermap[i][j]->Active = false;
										}
									}
								}//avtive Water which is real water tile

							}

							break;

						}
						if (canvas.keyPressed('W') && !press) {
							presscount = 0.2f;
							press = true;


							std::ifstream in("../load/sava2.json");
							if (!in) {
								std::cerr << "error ../load/sava.json\n";
							}
							else {

								in >> data;
								//load data


								in.close();
								enemiesmanager::getInstance().delatemyself();
								Bulletmanager::getInstance().delatemyself();
								//make count to zero
								loadpagechose = GameObjectManager::getInstance().loadall(data, enemymanager.credit, gametimecount, enemymanager.gettimecounttotalreference(), enemymanager.getcooldownreference(), enemymanager.gettimecountreference());
								//clear gameobjects and load 
								if (loadpagechose == 1 || loadpagechose == 3) {
									//chose map from load and load to mapsave1
									ifstream file("../Resources/tiles.txt");

									string line;
									for (int linenumber = 0; getline(file, line);) {

										if (linenumber >= 6) {

											int columnline = 0;
											int stack = -1;
											for (int i = 0; i < line.size(); i++) {
												if (line[i] == ',') {
													mapsave1[linenumber - 6][columnline] = stack;
													columnline++;
													stack = -1;
												}
												else {
													if (stack == -1) {
														stack = line[i] - '0';
													}
													else {
														stack = stack * 10 + (line[i] - '0');
													}
												}

											}
										}
										linenumber++;

									}
									file.close();
								}
								else if (loadpagechose == 2 || loadpagechose == 4) {
									//chose map from load and load to mapsave1
									ifstream file("../Resources/tiles1.txt");

									string line;
									for (int linenumber = 0; getline(file, line);) {

										if (linenumber >= 6) {

											int columnline = 0;
											int stack = -1;
											for (int i = 0; i < line.size(); i++) {
												if (line[i] == ',') {
													mapsave1[linenumber - 6][columnline] = stack;
													columnline++;
													stack = -1;
												}
												else {
													if (stack == -1) {
														stack = line[i] - '0';
													}
													else {
														stack = stack * 10 + (line[i] - '0');
													}
												}

											}
										}
										linenumber++;

									}
									file.close();
								}
								for (int i = 0; i < gameobjectmanager.GetCount(); i++) {
									if (gameobjectmanager.getobjects()[i]->Tag == "water") {
										watermap[gameobjectmanager.getobjects()[i]->getmapx()][gameobjectmanager.getobjects()[i]->getmapy()] = dynamic_cast<Water*>(gameobjectmanager.getobjects()[i]);

									}
								}
								//load Water to watermap
								for (int i = 0; i < 42; i++) {
									for (int j = 0; j < 42; j++) {

										if (mapsave1[i][j] >= 15 && mapsave1[i][j] <= 22) {
											watermap[i][j]->collision.SetCollision(0, 0, 32, 32);
										}
										else {
											watermap[i][j]->Active = false;
										}
									}
								}//avtive Water which is real water tile

							}

							break;

						}
						if (canvas.keyPressed('E') && !press) {
							presscount = 0.2f;
							press = true;


							std::ifstream in("../load/sava3.json");
							if (!in) {
								std::cerr << "error ../load/sava.json\n";
							}
							else {

								in >> data;
								//load data


								in.close();
								enemiesmanager::getInstance().delatemyself();
								Bulletmanager::getInstance().delatemyself();
								//make count to zero
								loadpagechose = GameObjectManager::getInstance().loadall(data, enemymanager.credit, gametimecount, enemymanager.gettimecounttotalreference(), enemymanager.getcooldownreference(), enemymanager.gettimecountreference());
								//clear gameobjects and load 
								if (loadpagechose == 1 || loadpagechose == 3) {
									//chose map from load and load to mapsave1
									ifstream file("../Resources/tiles.txt");

									string line;
									for (int linenumber = 0; getline(file, line);) {

										if (linenumber >= 6) {

											int columnline = 0;
											int stack = -1;
											for (int i = 0; i < line.size(); i++) {
												if (line[i] == ',') {
													mapsave1[linenumber - 6][columnline] = stack;
													columnline++;
													stack = -1;
												}
												else {
													if (stack == -1) {
														stack = line[i] - '0';
													}
													else {
														stack = stack * 10 + (line[i] - '0');
													}
												}

											}
										}
										linenumber++;

									}
									file.close();
								}
								else if (loadpagechose == 2 || loadpagechose == 4) {
									//chose map from load and load to mapsave1
									ifstream file("../Resources/tiles1.txt");

									string line;
									for (int linenumber = 0; getline(file, line);) {

										if (linenumber >= 6) {

											int columnline = 0;
											int stack = -1;
											for (int i = 0; i < line.size(); i++) {
												if (line[i] == ',') {
													mapsave1[linenumber - 6][columnline] = stack;
													columnline++;
													stack = -1;
												}
												else {
													if (stack == -1) {
														stack = line[i] - '0';
													}
													else {
														stack = stack * 10 + (line[i] - '0');
													}
												}

											}
										}
										linenumber++;

									}
									file.close();
								}
								for (int i = 0; i < gameobjectmanager.GetCount(); i++) {
									if (gameobjectmanager.getobjects()[i]->Tag == "water") {
										watermap[gameobjectmanager.getobjects()[i]->getmapx()][gameobjectmanager.getobjects()[i]->getmapy()] = dynamic_cast<Water*>(gameobjectmanager.getobjects()[i]);

									}
								}
								//load Water to watermap
								for (int i = 0; i < 42; i++) {
									for (int j = 0; j < 42; j++) {

										if (mapsave1[i][j] >= 15 && mapsave1[i][j] <= 22) {
											watermap[i][j]->collision.SetCollision(0, 0, 32, 32);
										}
										else {
											watermap[i][j]->Active = false;
										}
									}
								}//avtive Water which is real water tile

							}

							break;

						}
						if (canvas.keyPressed('R')) {
							ExitProcess(0);
						}
						canvas.present();
					}
				}
		

				dt = timer.dt();
				gametimecount -= dt;
				hero.updataability(dt);
				//update AOE cooldown
				hero.updateinvincible(dt);
				//update invincible tiem
				fpsdtcount += dt;
				fps++;
				if (fpsdtcount >= 1.0f) {
					
					cout << "FPS: " << fps << endl;
					cout << "hero.ability max number" << hero.getabilitymax() << endl;
					cout << "hero.bulletspeed" << hero.getbulletmovespeed() << endl;
					cout << "bullet cooldown" << hero.getcooldown() << endl;
					cout << "enemy creat cooldown" << enemymanager.getcooldown() << endl;
					showfps = fps;
					//showfps will show in game
					fps = 0;
					fpsdtcount = 0;
					//show some information in terminal
				}

				hero.shot(dt, hero);
				//update cooldown and shot bullet
				enemymanager.updateall(dt);
				//make enemies move
				move = hero.getMoveSpeed() * dt;
				controlHero(hero, canvas, move);
				//control hero move
				if (canvas.keyPressed('N')) {
					//use AOE
					if (Hero::getInstance().getabilitytimecount() >= 10.f) {
						enemiesmanager::getInstance().killsomeenemies(Hero::getInstance().getabilitymax());
						Hero::getInstance().setabilitytimecount(0.f);
					}

				}
				if (loadpagechose == 3 || loadpagechose == 4) {
					//fixed map need to restrict hero's position and camera's position
					if (hero.transform.GetPositionX() <= -10) {
						hero.transform.SetPositionX(-10);
					}
					if (hero.transform.GetPositionY() <= -10) {
						hero.transform.SetPositionY(-10);
					}
					if (hero.transform.GetPositionX() >= canvas.getWidth() - 32) {
						hero.transform.SetPositionX(canvas.getWidth() - 32);
					}
					if (hero.transform.GetPositionY() >= canvas.getHeight() - 32) {
						hero.transform.SetPositionY(canvas.getHeight() - 32);
					}
					//changemao(hero, mapoffestx, mapoffesty);

					//camera.SetPosition(hero.transform.GetPositionX() - (canvas.getWidth() / 2), hero.transform.GetPositionY() - (canvas.getHeight() / 2));
					if (hero.transform.GetPositionX() - (canvas.getWidth() / 2) >= 0) {
						camera.SetPositionX(min(hero.transform.GetPositionX() - (canvas.getWidth() / 2), 64));
					}
					else {
						camera.SetPositionX(max(hero.transform.GetPositionX() - (canvas.getWidth() / 2), 0));
					}


					if (hero.transform.GetPositionY() - (canvas.getHeight() / 2) >= 0) {
						camera.SetPositionY(min(hero.transform.GetPositionY() - (canvas.getHeight() / 2), 64));
					}
					else {
						camera.SetPositionY(max(hero.transform.GetPositionY() - (canvas.getHeight() / 2), 0));
					}

				}
				else if (loadpagechose == 1 || loadpagechose == 2) {
					//infinite map
					changemao(hero, mapoffestx, mapoffesty);
					camera.SetPosition(hero.transform.GetPositionX() - (canvas.getWidth() / 2), hero.transform.GetPositionY() - (canvas.getHeight() / 2));
				}

				bulletmanager.updateAll(dt);
				//move bullets
				gameobjectmanager.UpdateAll(dt);
				//update collision box position to the object's position and check for collision
				if (hero.getHealth() < 0) {
					stage = 2;
					gametimecount = 120.f;
					winorlose = false;
					break;
				}
				//check hero die
				if (gametimecount <= 0) {
					presscount = 0.2f;
					press = true;
					stage = 2;
					winorlose = true;
					gametimecount = 120.f;
					break;
				}
				//check time over
				
				canvas.clear();

				draw_entire_background(mapsave1, canvas, tiles, mapoffestx, mapoffesty, watermap);
				//draw_title((int)floorf(hero.transform.GetPositionX()), (int)floorf(hero.transform.GetPositionY()), canvas, hero.image);
				draw_object(canvas, gameobjectmanager.getobjects(), gameobjectmanager.GetCount());
				draw_title(0, 10, canvas, healthshow);
				draw_numbers(healthshow.width + 10, 10, canvas,number,hero.getHealth());
				//show health
				draw_title(0, 60, canvas, Creditsshow);
				draw_numbers(Creditsshow.width + 10, 60, canvas, number, enemymanager.credit);
				//show scores
				draw_title(0, 110, canvas, FPSshow);
				draw_numbers(FPSshow.width + 10, 110, canvas, number, showfps);
				//show FPS
				draw_title(0, 160, canvas, TIMEshow);
				draw_numbers(TIMEshow.width + 10, 160, canvas, number, gametimecount);
				//show remaing time
				if (Hero::getInstance().getabilitytimecount() >= 10.f) {
					draw_title(450, 10, canvas, aoeshow);
				}
				//show the situation of AOE
				draw_title(900, 10, canvas, Tshow);
				draw_title(900, 60, canvas, Yshow);
				//show information about save and load
				


				
				canvas.present();
			}
		}
		
		else if (stage == 7) {//chose map page
			
			canvas.clear();
			draw_title(0, 0, canvas, chose_page);
				if (canvas.keyPressed('Q') && !press) {
					presscount = 0.2f;
					press = true;
					loadpagechose = 1;
					stage = 5;
					//map1 infinite
				}
				if (canvas.keyPressed('W') && !press) {
					presscount = 0.2f;
					press = true;
					loadpagechose = 2;
					stage = 5;
					//map2 infinite
				}
				if (canvas.keyPressed('E') && !press) {
					presscount = 0.2f;
					press = true;
					loadpagechose = 3;
					stage = 5;
					//map1 fixed
				}
				if (canvas.keyPressed('R') && !press) {
					presscount = 0.2f;
					press = true;
					loadpagechose = 4;
					stage = 5;
					//map2 fixed
				}
				canvas.present();
			}
		
	}



	


	return 0;
}
void changemao(Hero& hero, int** mapmapoffestx, int** mapmapoffesty) {//change map offest
	int countx = ((int)hero.transform.GetPositionX() - 672) / (42 * 32);
	int county = ((int)hero.transform.GetPositionY() - 672) / (42 * 32);
	int offestx = ((int)hero.transform.GetPositionX() - 672) % (42 * 32) / 32;
	int offesty = ((int)hero.transform.GetPositionY() - 672) % (42 * 32) / 32;

	for (int i = 0; i < 42; i++) {
		for (int j = 0; j < 42; j++) {
			//clean its
			mapmapoffestx[i][j] = 0;
			mapmapoffesty[i][j] = 0;
		}
	}
	if (offestx < 0 || countx < 0) {
		//hero in the left
		for (int i = 41; i >= 0; i--) {
			for (int j = 41; j >= 0; j--) {
				if (j > 41 + offestx) {
					mapmapoffestx[j][i] = (-1 + countx * 1) * 42 * 32;
				}
				else {
					mapmapoffestx[j][i] = (countx * 1) * 42 * 32;
				}
			}
		}
	}
	if (offestx >= 0 || countx > 0) {
		//hero in the right
		for (int i = 0; i < 42; i++) {
			for (int j = 0; j < 42; j++) {

				if (j < offestx)
					mapmapoffestx[j][i] = (1 + countx * 1) * 42 * 32;
				else {
					mapmapoffestx[j][i] = (countx * 1) * 42 * 32;
				}
			}
		}
	}
	if (offesty >= 0 || county > 0) {
		//hero in the top
		for (int i = 0; i < 42; i++) {
			for (int j = 0; j < 42; j++) {
				if (j < offesty) {
					mapmapoffesty[i][j] = (1 + county * 1) * 42 * 32;
				}
				else {
					mapmapoffesty[i][j] = (county * 1) * 42 * 32;
				}
			}
		}
	}
	if (offesty < 0 || county < 0) {
		//hero in the down
		for (int i = 0; i < 42; i++) {
			for (int j = 41; j >= 0; j--) {
				if (j > 41 + offesty) {
					mapmapoffesty[i][j] = (-1 + county * 1) * 42 * 32;
				}
				else {
					mapmapoffesty[i][j] = (county * 1) * 42 * 32;
				}

			}
		}
	}

}
void draw_title(int x, int y, GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image& image) {
	//draw a image with the window coordinate

	for (int i = 0; i < image.height; i++) {
		for (int j = 0; j < image.width; j++) {
			if (x + j >= 0 && i + y >= 0 && x + j < canvas.getWidth() && i + y < canvas.getHeight()) {
				//check the pixil is in the camera
				if (image.alphaAt(j, i)) {
					canvas.draw(x + j, y + i, image.at(j, i));
				}


			}

		}
	}

}
void draw_object(GamesEngineeringBase::Window& canvas, GameObject** obj, int count) {
	//draw a GameObject 

	for (int o = 0; o < count; o++) {
		if (obj[o]) {

			draw_collision(*obj[o], canvas);//draw collision box for testing
			for (int i = 0; i < obj[o]->image.height; i++) {
				for (int j = 0; j < obj[o]->image.width; j++) {
					if (true) {
						if (obj[o]->image.alphaAt(j, i)) {
							camera_draw(j, i, obj[o]->image, canvas, obj[o]);
							//it will calculate the offset about camera
						}


					}

				}
			}

		}
	}


}
//correction position with camera offset
void camera_draw(float x, float y, GamesEngineeringBase::Image& image,GamesEngineeringBase::Window& canvas, GameObject* obj) {

	if (obj->transform.GetPositionX() + x - Camera::GetCamera().GetX() >= 0 && obj->transform.GetPositionX() + x - Camera::GetCamera().GetX() < canvas.getWidth()&& obj->transform.GetPositionY() + y - Camera::GetCamera().GetY() >= 0 &&obj->transform.GetPositionY() + y - Camera::GetCamera().GetY() < canvas.getHeight())
		//if the new position in the canvs
		canvas.draw(obj->transform.GetPositionX() + x - Camera::GetCamera().GetX(), obj->transform.GetPositionY() + y - Camera::GetCamera().GetY(), obj->image.at(x, y));
}

void draw_collision(GameObject& gameobject, GamesEngineeringBase::Window& canvas) {//draw the collision box
	for (int i = gameobject.collision.getcollisionX() - Camera::GetCamera().GetX(); i < gameobject.collision.getcollisionX() + gameobject.collision.getcollisionW() - Camera::GetCamera().GetX(); i++) {
		if (i >= 0 && gameobject.collision.getcollisionY() - Camera::GetCamera().GetY() >= 0 && i < canvas.getWidth() && gameobject.collision.getcollisionY() - Camera::GetCamera().GetY() < canvas.getHeight()) {
			canvas.draw(i, gameobject.collision.getcollisionY() - Camera::GetCamera().GetY(), 0, 0, 225);

		}

	}
	for (int i = gameobject.collision.getcollisionX() - Camera::GetCamera().GetX(); i < gameobject.collision.getcollisionX() + gameobject.collision.getcollisionW() - Camera::GetCamera().GetX(); i++) {
		if (i >= 0 && gameobject.collision.getcollisionY() + gameobject.collision.getcollisionH() - Camera::GetCamera().GetY() >= 0 && i < canvas.getWidth() && gameobject.collision.getcollisionY() + gameobject.collision.getcollisionH() - Camera::GetCamera().GetY() < canvas.getHeight()) {
			canvas.draw(i, gameobject.collision.getcollisionY() + gameobject.collision.getcollisionH() - Camera::GetCamera().GetY(), 0, 0, 225);
		}

	}

	for (int i = gameobject.collision.getcollisionY() - Camera::GetCamera().GetY(); i < gameobject.collision.getcollisionY() + gameobject.collision.getcollisionH() - Camera::GetCamera().GetY(); i++) {
		if (gameobject.collision.getcollisionX() - Camera::GetCamera().GetX() >= 0 && i >= 0 && gameobject.collision.getcollisionX() - Camera::GetCamera().GetX() < canvas.getWidth() && i < canvas.getHeight()) {
			canvas.draw(gameobject.collision.getcollisionX() - Camera::GetCamera().GetX(), i, 0, 0, 225);
		}

	}
	for (int i = gameobject.collision.getcollisionY() - Camera::GetCamera().GetY(); i < gameobject.collision.getcollisionY() + gameobject.collision.getcollisionH() - Camera::GetCamera().GetY(); i++) {
		if (gameobject.collision.getcollisionX() + gameobject.collision.getcollisionW() - Camera::GetCamera().GetX() >= 0 && i >= 0 && gameobject.collision.getcollisionX() + gameobject.collision.getcollisionW() - Camera::GetCamera().GetX() < canvas.getWidth() && i < canvas.getHeight()) {
			canvas.draw(gameobject.collision.getcollisionX() + gameobject.collision.getcollisionW() - Camera::GetCamera().GetX(), i, 0, 0, 225);
		}

	}
	//the 4 for is about 4 line of the box
	

}
void draw_entire_background(int** mapsave1,GamesEngineeringBase::Window& canvas,GamesEngineeringBase::Image* tiles, int** offestmapx, int** offestmapy, Water*** watermap) {
	
	//draw background and update water collision box
	for (int i = 0; i < 42; i++) {
		for (int j = 0; j < 42; j++) {
			if (mapsave1[i][j] > -1 && mapsave1[i][j] < 24) {
				if (mapsave1[i][j] >= 15 && mapsave1[i][j] <= 22) {
					//update water position and water collision box position
					watermap[i][j]->transform.SetPosition((j * 32) +offestmapx[j][i], (i * 32) + offestmapy[j][i]);watermap[i][j]->Update(0, Camera::GetCamera());

				}

				draw_title((j * 32) - Camera::GetCamera().GetX() + offestmapx[j][i], (i * 32) - Camera::GetCamera().GetY() + offestmapy[j][i], canvas, tiles[mapsave1[i][j]]);
				//draw every tile with right offset,the function camera_draw is suit for gameobject,so correction offset and then use draw_title draw it in window
			}
		}


	}
}
void draw_numbers(float x, float y, GamesEngineeringBase::Window& canvas,GamesEngineeringBase::Image& image, int number) {
	int numbernow;
	int count = 0;
	int numbers[10];
	if (number == 0) {
		//draw 0 when the number is 0
		for (int i = 0; i < 39; i++) {
			for (int j = 0; j < 50; j++) {
				if (image.alphaAt(i , j)) {
					canvas.draw(i + x, j + y, image.at(i , j));
				}
			}
		}
	}
	while (number >0) {
		
		numbers[count] = number % 10;
		//save the number in different digits
		count++;
		//count the The number of digits
		number = number / 10;
		
	}
	for (int u = count-1; u >= 0;u-- ) {
		for (int i = 0; i < 39; i++) {
			for (int j = 0; j < 50; j++) {
				if (image.alphaAt(i + (numbers[u] * 39), j)) {
					canvas.draw(i + (count - u) * 39 + x, 
						//draw the number based on digits 
					j + y, image.at(i + (numbers[u] * 39), j));
				}
			}
		}
	}
	
	
}



void controlHero(Hero& hero, GamesEngineeringBase::Window& canvas, float move) {


	if (canvas.keyPressed('W')) {


		hero.transform.SetPosition(hero.transform.GetPositionX(), hero.transform.GetPositionY() - move);
		hero.Update();
		if (GameObjectManager::getInstance().checkwater()) {
			//check hero is collision with water or not
			hero.transform.SetPosition(hero.transform.GetPositionX(), hero.transform.GetPositionY() + move);
			hero.Update();

		}


	}
	if (canvas.keyPressed('S')) {
		hero.transform.SetPosition(hero.transform.GetPositionX(), hero.transform.GetPositionY() + move);
		hero.Update();
		if (GameObjectManager::getInstance().checkwater()) {
			hero.transform.SetPosition(hero.transform.GetPositionX(), hero.transform.GetPositionY() - move);
			hero.Update();

		}


	}
	if (canvas.keyPressed('A')) {
		hero.transform.SetPosition(hero.transform.GetPositionX() - move, hero.transform.GetPositionY());
		hero.Update();
		if (GameObjectManager::getInstance().checkwater()) {
			hero.transform.SetPosition(hero.transform.GetPositionX() + move, hero.transform.GetPositionY());
			hero.Update();
		}

	}
	if (canvas.keyPressed('D')) {
		hero.transform.SetPosition(hero.transform.GetPositionX() + move, hero.transform.GetPositionY());
		hero.Update();
		if (GameObjectManager::getInstance().checkwater()) {
			hero.transform.SetPosition(hero.transform.GetPositionX() - move, hero.transform.GetPositionY());
			hero.Update();
		}

	}
	

}
