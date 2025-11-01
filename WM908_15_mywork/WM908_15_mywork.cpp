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
using json = nlohmann::json;

bool press = false;
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
	float presscount = 0.f;
	int stage = 1;
	json data;
	
	HRESULT hr = CoInitialize(NULL); //  初始化 COM

	
	GameObjectManager& gameobjectmanager = GameObjectManager::getInstance();
	Bulletmanager& bulletmanager = Bulletmanager::getInstance();
	
	Hero& hero = Hero::getInstance();

	enemiesmanager& enemymanager = enemiesmanager::getInstance();
	Camera& camera = Camera::GetCamera();
	camera.SetPosition(hero.transform.GetPositionX(), hero.transform.GetPositionY());
	GamesEngineeringBase::Image tiles[24];
	for (int i = 0; i < 24; i++) {
		tiles[i].load("../Resources/" + to_string(i) + ".png");

	}
	

	GamesEngineeringBase::Image image;
	GamesEngineeringBase::Image welcome_page;
	GamesEngineeringBase::Image lose_page;
	GamesEngineeringBase::Image load_page;
	GamesEngineeringBase::Image save_page;
	GamesEngineeringBase::Image chose_page;
	GamesEngineeringBase::Window canvas;

	image.load("../Resources/A.png");
	// Create a canvas window with dimensions 1024x768 and title “Tiles"



	unsigned int planeX = 300;  // Initial x-coordinate for the plane image.
	unsigned int planeY = 300;

	canvas.create(1280, 1280, "Tiles");
	
	bool running = true; // Variable to control the main loop's running state.
	cout << canvas.getWidth() << "   " << canvas.getHeight();
	welcome_page.load("../Resources/welcome_page.png");
	lose_page.load("../Resources/lose_page.png");
	load_page.load("../Resources/load_page.png");
	save_page.load("../Resources/save_page.png");
	chose_page.load("../Resources/welcome_page.png");

	


	while (1) {
		
		if (stage == 1) {//welcome page
			canvas.clear();
			if (canvas.keyPressed('Q')) {
				stage = 7;
				
			}
			if (canvas.keyPressed('W')) {
				stage = 4;
				
			}
			if (canvas.keyPressed('E')) {
				ExitProcess(0);
			}

			draw_title(0, 0, canvas, welcome_page);



			canvas.present();

		}
		else if (stage == 2) {//game over page
			canvas.clear();
			draw_title(0, 0,canvas, lose_page);
			if (canvas.keyPressed('Q')) {
				stage = 7;
				
			}
			if (canvas.keyPressed('W')) {
				stage = 4;
				
			}
			if (canvas.keyPressed('E')) {
				ExitProcess(0);
			}
			canvas.present();

		}
		else if (stage == 3) {//load page
			canvas.clear();
			draw_title(0, 0, canvas, load_page);
			if (canvas.keyPressed('Q')) {
				
				
			}
			if (canvas.keyPressed('W')) {
				
			}
			if (canvas.keyPressed('E')) {
				
			}
			if (canvas.keyPressed('R')) {
				ExitProcess(0);
			}
			canvas.present();

		}
		else if (stage == 4) {//save page
			canvas.clear();
			draw_title(0, 0,canvas, save_page);
			if (canvas.keyPressed('Q')) {

			}
			if (canvas.keyPressed('W')) {

			}
			if (canvas.keyPressed('E')) {

			}
			if (canvas.keyPressed('R')) {
				ExitProcess(0);
			}
			canvas.present();
		}
		else if (stage == 5) {//infinity map 

			gameobjectmanager.delatemyself();
			bulletmanager.delatemyself();
			enemymanager.delatemyself();
			float presscount = 0.f;
		
			hero.setHealth(100);
			Water*** watermap = new Water * *[42];
			for (int i = 0; i < 42; i++) {
				watermap[i] = new Water * [42];
				for (int j = 0; j < 42; j++) {
					watermap[i][j] = new Water; // 初始化为空指针
					watermap[i][j]->positionmap_x = i;
					watermap[i][j]->positionmap_y = j;
				}
			}
			int** mapoffestx = new int* [100]();
			for (int i = 0; i < 100; i++)
				mapoffestx[i] = new int[100]();
			int** mapoffesty = new int* [100]();
			for (int i = 0; i < 100; i++)
				mapoffesty[i] = new int[100]();
			

			GamesEngineeringBase::Timer timer;
			
			ifstream file("../Resources/tiles.txt");
			Hero& hero = Hero::getInstance();
			hero.transform.SetPosition(canvas.getWidth() / 2, canvas.getHeight() / 2);
			
			camera.SetPosition(hero.transform.GetPositionX(), hero.transform.GetPositionY());

			float dt = timer.dt();
			int move = hero.getMoveSpeed() * dt;
			int fps = 0;
			float fpsdtcount = 0;
			int** mapsave1 = new int* [42];
			for (int i = 0; i < 42; i++)
				mapsave1[i] = new int[42];
			

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

					if (mapsave1[i][j] >= 14 && mapsave1[i][j] <= 22) {
						watermap[i][j]->collision.SetCollision(0, 0, 32, 32);
					}
					else {
						watermap[i][j]->collision.SetCollision(0, 0, 0, 0);
						watermap[i][j]->Active = false;
					}
				}
			}

		
			
			// Create a canvas window with dimensions 1024x768 and title “Tiles"



			unsigned int planeX = 300;  // Initial x-coordinate for the plane image.
			unsigned int planeY = 300;

			

			while (running)//infinity map stage 5
			{

				if (canvas.keyPressed('O') && !press) {
					ofstream loadfile("../load/sava.json", std::ios::out | std::ios::trunc);
					press = true;
					presscount = 0.5f;
					GameObjectManager::getInstance().saveall(data);
					loadfile << data.dump(4);
					loadfile.close();
					data = json();

				}
				if (canvas.keyPressed('I')) {
					for (int i = 0; i < 42; i++) {
						for (int j = 0; j < 42; j++) {

						}
					}
				}
				if (canvas.keyPressed('P') && !press) {
					std::ifstream in("../load/sava.json");
					if (!in) {
						std::cerr << "无法打开读取文件 ../load/sava.json\n";
					}
					else {
						try {
							in >> data; // 从文件反序列化到内存 json 对象
						}
						catch (nlohmann::json::parse_error& e) {
							std::cerr << "JSON 解析错误: " << e.what() << '\n';
							data = nlohmann::json(); // 可选：重置为空 json
						}
						in.close();
						enemiesmanager::getInstance().delatemyself();
						Bulletmanager::getInstance().delatemyself();
						press = true;
						presscount = 0.5f;
						GameObjectManager::getInstance().loadall(data);
						for (int i = 0; i < gameobjectmanager.GetCount(); i++) {
							if (gameobjectmanager.getobjects()[i]->Tag == "water") {
								watermap[gameobjectmanager.getobjects()[i]->getmapx()][gameobjectmanager.getobjects()[i]->getmapy()] = dynamic_cast<Water*>(gameobjectmanager.getobjects()[i]);

							}
						}
						for (int i = 0; i < 42; i++) {
							for (int j = 0; j < 42; j++) {

								if (mapsave1[i][j] >= 14 && mapsave1[i][j] <= 22) {
									watermap[i][j]->collision.SetCollision(0, 0, 32, 32);
								}
								else {
									watermap[i][j]->Active = false;
								}
							}
						}
						continue;
					}
				}

				dt = timer.dt();
				presscount -= dt;
				if (presscount <= 0.f) {
					press = false;
				}
				hero.updataability(dt);
				fpsdtcount += dt;
				fps++;
				if (fpsdtcount >= 1.0f) {
					cout << "FPS: " << fps << endl;
					cout << "FPS: " << fps << endl;
					cout << "hero.max" << hero.getabilitymax() << endl;
					cout << "hero.cooldown" << hero.getabilitycooldown() << endl;
					cout << "hero.bulletspeed" << hero.getbulletmovespeed() << endl;
					cout << "cooldown" << hero.getcooldown() << endl;
					fps = 0;
					fpsdtcount = 0;
				}
				
				hero.shot(dt, hero);
				enemymanager.updateall(dt);
				move = hero.getMoveSpeed() * dt;
				controlHero(hero, canvas, move);
				changemao(hero, mapoffestx, mapoffesty);
				camera.SetPosition(hero.transform.GetPositionX() - (canvas.getWidth() / 2), hero.transform.GetPositionY() - (canvas.getHeight() / 2));
				bulletmanager.updateAll(dt);
				gameobjectmanager.UpdateAll(dt);
				if (hero.getHealth() < 0) {
					stage = 2;
					break;
				}
				if (canvas.keyPressed('M'))
				{
					stage = 2;
					break;
				}
				// Check for input (key presses or window events)
				// Clear the window for the next frame rendering
				canvas.clear();

				draw_entire_background(mapsave1, canvas, tiles, mapoffestx, mapoffesty, watermap);
				//draw_title((int)floorf(hero.transform.GetPositionX()), (int)floorf(hero.transform.GetPositionY()), canvas, hero.image);
				draw_object(canvas, gameobjectmanager.getobjects(), gameobjectmanager.GetCount());

				//draw_collision(hero, canvas);


				// Update game logic
				// Draw();
				// Display the frame on the screen. This must be called once the frameis finished in order to display the frame.
				canvas.present();
			}
		}
		else if (stage == 6) {//fixed map


			gameobjectmanager.delatemyself();
			bulletmanager.delatemyself();
			enemymanager.delatemyself();

			float presscount = 0.f;


			Water*** watermap = new Water * *[42];
			for (int i = 0; i < 42; i++) {
				watermap[i] = new Water * [42];
				for (int j = 0; j < 42; j++) {
					watermap[i][j] = new Water; // 初始化为空指针
					watermap[i][j]->positionmap_x = i;
					watermap[i][j]->positionmap_y = j;
				}
			}
			int** mapoffestx = new int* [100]();
			for (int i = 0; i < 100; i++)
				mapoffestx[i] = new int[100]();
			int** mapoffesty = new int* [100]();
			for (int i = 0; i < 100; i++)
				mapoffesty[i] = new int[100]();


			GamesEngineeringBase::Timer timer;

			ifstream file("../Resources/tiles.txt");
			Hero& hero = Hero::getInstance();
			hero.transform.SetPosition(canvas.getWidth() / 2, canvas.getHeight() / 2);

			camera.SetPosition(hero.transform.GetPositionX(), hero.transform.GetPositionY());

			float dt = timer.dt();
			int move = hero.getMoveSpeed() * dt;
			int fps = 0;
			float fpsdtcount = 0;
			int** mapsave1 = new int* [42];
			for (int i = 0; i < 42; i++)
				mapsave1[i] = new int[42];


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

					if (mapsave1[i][j] >= 14 && mapsave1[i][j] <= 22) {
						watermap[i][j]->collision.SetCollision(0, 0, 32, 32);
					}
					else {
						watermap[i][j]->Active=false;
					}

				}
			}



			// Create a canvas window with dimensions 1024x768 and title “Tiles"



			unsigned int planeX = 300;  // Initial x-coordinate for the plane image.
			unsigned int planeY = 300;






























			while (running)//fixed map stage 6
			{



				if (canvas.keyPressed('O') && !press) {
					ofstream loadfile("../load/sava.json", std::ios::out | std::ios::trunc);
					press = true;
					presscount = 0.5f;
					GameObjectManager::getInstance().saveall(data);
					loadfile << data.dump(4);
					loadfile.close();
					data = json();

				}
				if (canvas.keyPressed('I')) {
					for (int i = 0; i < 42; i++) {
						for (int j = 0; j < 42; j++) {

						}
					}
				}
				if (canvas.keyPressed('P') && !press) {
					std::ifstream in("../load/sava.json");
					if (!in) {
						std::cerr << "无法打开读取文件 ../load/sava.json\n";
					}
					else {
						try {
							in >> data; // 从文件反序列化到内存 json 对象
						}
						catch (nlohmann::json::parse_error& e) {
							std::cerr << "JSON 解析错误: " << e.what() << '\n';
							data = nlohmann::json(); // 可选：重置为空 json
						}
						in.close();
						enemiesmanager::getInstance().delatemyself();
						Bulletmanager::getInstance().delatemyself();
						press = true;
						presscount = 0.5f;
						GameObjectManager::getInstance().loadall(data);
						for (int i = 0; i < gameobjectmanager.GetCount(); i++) {
							if (gameobjectmanager.getobjects()[i]->Tag == "water") {
								watermap[gameobjectmanager.getobjects()[i]->getmapx()][gameobjectmanager.getobjects()[i]->getmapy()] = dynamic_cast<Water*>(gameobjectmanager.getobjects()[i]);

							}
						}
						for (int i = 0; i < 42; i++) {
							for (int j = 0; j < 42; j++) {

								if (mapsave1[i][j] >= 14 && mapsave1[i][j] <= 22) {
									watermap[i][j]->collision.SetCollision(0, 0, 32, 32);
								}
								else {
									watermap[i][j]->Active = false;
								}
							}
						}
						continue;
					}
				}

				dt = timer.dt();
				presscount -= dt;
				if (presscount <= 0.f) {
					press = false;
				}
				hero.updataability(dt);
				fpsdtcount += dt;
				fps++;
				if (fpsdtcount >= 1.0f) {
					cout << "FPS: " << fps << endl;
					cout << "hero.max" << hero.getabilitymax() << endl;
					cout << "hero.cooldown" << hero.getabilitycooldown() << endl;
					cout << "hero.bulletspeed" << hero.getbulletmovespeed() << endl;
					cout << "cooldown" << hero.getcooldown() << endl;
					fps = 0;
					fpsdtcount = 0;
				}
				if (canvas.keyPressed(VK_ESCAPE)) break;
				hero.shot(dt, hero);
				enemymanager.updateall(dt);
				move = hero.getMoveSpeed() * dt;
				controlHero(hero, canvas, move);
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


				bulletmanager.updateAll(dt);
				gameobjectmanager.UpdateAll(dt);
				if (hero.getHealth() < 0) {
					stage = 2;
					break;
				}
				if (canvas.keyPressed('M'))
				{
					stage = 2;
					break;
				}
				// Check for input (key presses or window events)
				// Clear the window for the next frame rendering
				canvas.clear();

				draw_entire_background(mapsave1, canvas, tiles, mapoffestx, mapoffesty, watermap);
				//draw_title((int)floorf(hero.transform.GetPositionX()), (int)floorf(hero.transform.GetPositionY()), canvas, hero.image);
				draw_object(canvas, gameobjectmanager.getobjects(), gameobjectmanager.GetCount());

				//draw_collision(hero, canvas);


				// Update game logic
				// Draw();
				// Display the frame on the screen. This must be called once the frameis finished in order to display the frame.
				canvas.present();
			}

		}
		else if (stage == 7) {//chose map page
			stage = 5;
		}
	}



	/*while (running)//fixed map stage 5
	{

		if (canvas.keyPressed('O')&&!press) {
			ofstream loadfile("../load/sava.json", std::ios::out | std::ios::trunc);
			press = true;
			presscount = 0.5f;
			GameObjectManager::getInstance().saveall(data);
			loadfile << data.dump(4);
			loadfile.close();
			data = json();

		}
		if (canvas.keyPressed('I')) {
			for (int i = 0; i < 42; i++) {
				for (int j = 0; j < 42; j++) {

				}
			}
		}
		if (canvas.keyPressed('P') && !press) {
			std::ifstream in("../load/sava.json");
			if (!in) {
				std::cerr << "无法打开读取文件 ../load/sava.json\n";
			}
			else {
				try {
					in >> data; // 从文件反序列化到内存 json 对象
				}
				catch (nlohmann::json::parse_error& e) {
					std::cerr << "JSON 解析错误: " << e.what() << '\n';
					data = nlohmann::json(); // 可选：重置为空 json
				}
				in.close();
				enemiesmanager::getInstance().delatemyself();
				Bulletmanager::getInstance().delatemyself();
				press = true;
				presscount = 0.5f;
				GameObjectManager::getInstance().loadall(data);
				for (int i = 0; i <gameobjectmanager.GetCount(); i++) {
					if (gameobjectmanager.getobjects()[i]->Tag == "water") {
						watermap[gameobjectmanager.getobjects()[i]->getmapx()][gameobjectmanager.getobjects()[i]->getmapy()] = dynamic_cast<Water*>(gameobjectmanager.getobjects()[i]);

					}
				}
				for (int i = 0; i < 42; i++) {
					for (int j = 0; j < 42; j++) {

						if (mapsave1[i][j] >= 14 && mapsave1[i][j] <= 22) {
							watermap[i][j]->collision.SetCollision(0, 0, 32, 32);
						}
					}
				}
				continue;
			}
		}

		dt = timer.dt();
		presscount -= dt;
		if (presscount <= 0.f) {
			press = false;
		}
		hero.updataability(dt);
		fpsdtcount += dt;
		fps++;
		if (fpsdtcount >= 1.0f) {
			cout << "FPS: " << fps << endl;
			cout << "FPS: " << fps << endl;
		cout << "hero.max" << hero.getabilitymax() << endl;
		cout << "hero.cooldown" << hero.getabilitycooldown() << endl;
		cout << "hero.bulletspeed" << hero.getbulletmovespeed() << endl;
		cout << "cooldown" << hero.getcooldown() << endl;
			fps = 0;
			fpsdtcount = 0;
		}
		if (canvas.keyPressed(VK_ESCAPE)) break;
		hero.shot(dt, hero);
		enemymanager.updateall(dt);
		move = hero.getMoveSpeed() * dt;
		controlHero(hero, canvas, move);
		changemao(hero, mapoffestx, mapoffesty);
		camera.SetPosition(hero.transform.GetPositionX() - (canvas.getWidth() / 2), hero.transform.GetPositionY() - (canvas.getHeight() / 2));
		bulletmanager.updateAll(dt);
		gameobjectmanager.UpdateAll(dt);
		// Check for input (key presses or window events)
		// Clear the window for the next frame rendering
		canvas.clear();

		draw_entire_background(mapsave1, canvas, tiles, mapoffestx, mapoffesty, watermap);
		//draw_title((int)floorf(hero.transform.GetPositionX()), (int)floorf(hero.transform.GetPositionY()), canvas, hero.image);
		draw_object(canvas, gameobjectmanager.getobjects(), gameobjectmanager.GetCount());

		//draw_collision(hero, canvas);


		// Update game logic
		// Draw();
		// Display the frame on the screen. This must be called once the frameis finished in order to display the frame.
		canvas.present();
	}*/


	/*while (running)//fixed map stage 6
	{

		if (canvas.keyPressed('O') && !press) {
			ofstream loadfile("../load/sava.json", std::ios::out | std::ios::trunc);
			press = true;
			presscount = 0.5f;
			GameObjectManager::getInstance().saveall(data);
			loadfile << data.dump(4);
			loadfile.close();
			data = json();

		}
		if (canvas.keyPressed('I')) {
			for (int i = 0; i < 42; i++) {
				for (int j = 0; j < 42; j++) {

				}
			}
		}
		if (canvas.keyPressed('P') && !press) {
			std::ifstream in("../load/sava.json");
			if (!in) {
				std::cerr << "无法打开读取文件 ../load/sava.json\n";
			}
			else {
				try {
					in >> data; // 从文件反序列化到内存 json 对象
				}
				catch (nlohmann::json::parse_error& e) {
					std::cerr << "JSON 解析错误: " << e.what() << '\n';
					data = nlohmann::json(); // 可选：重置为空 json
				}
				in.close();
				enemiesmanager::getInstance().delatemyself();
				Bulletmanager::getInstance().delatemyself();
				press = true;
				presscount = 0.5f;
				GameObjectManager::getInstance().loadall(data);
				for (int i = 0; i < gameobjectmanager.GetCount(); i++) {
					if (gameobjectmanager.getobjects()[i]->Tag == "water") {
						watermap[gameobjectmanager.getobjects()[i]->getmapx()][gameobjectmanager.getobjects()[i]->getmapy()] = dynamic_cast<Water*>(gameobjectmanager.getobjects()[i]);

					}
				}
				for (int i = 0; i < 42; i++) {
					for (int j = 0; j < 42; j++) {

						if (mapsave1[i][j] >= 14 && mapsave1[i][j] <= 22) {
							watermap[i][j]->collision.SetCollision(0, 0, 32, 32);
						}
					}
				}
				continue;
			}
		}

		dt = timer.dt();
		presscount -= dt;
		if (presscount <= 0.f) {
			press = false;
		}
		hero.updataability(dt);
		fpsdtcount += dt;
		fps++;
		if (fpsdtcount >= 1.0f) {
			cout << "FPS: " << fps << endl;
			cout << "hero.max" << hero.getabilitymax() << endl;
			cout << "hero.cooldown" << hero.getabilitycooldown() << endl;
			cout << "hero.bulletspeed" << hero.getbulletmovespeed() << endl;
			cout << "cooldown" << hero.getcooldown() << endl;
			fps = 0;
			fpsdtcount = 0;
		}
		if (canvas.keyPressed(VK_ESCAPE)) break;
		hero.shot(dt, hero);
		enemymanager.updateall(dt);
		move = hero.getMoveSpeed() * dt;
		controlHero(hero, canvas, move);
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


		bulletmanager.updateAll(dt);
		gameobjectmanager.UpdateAll(dt);
		// Check for input (key presses or window events)
		// Clear the window for the next frame rendering
		canvas.clear();

		draw_entire_background(mapsave1, canvas, tiles, mapoffestx, mapoffesty, watermap);
		//draw_title((int)floorf(hero.transform.GetPositionX()), (int)floorf(hero.transform.GetPositionY()), canvas, hero.image);
		draw_object(canvas, gameobjectmanager.getobjects(), gameobjectmanager.GetCount());

		//draw_collision(hero, canvas);


		// Update game logic
		// Draw();
		// Display the frame on the screen. This must be called once the frameis finished in order to display the frame.
		canvas.present();
	}*/


	return 0;
}
void changemao(Hero& hero, int** mapmapoffestx, int** mapmapoffesty) {//change map offest
	int countx = ((int)hero.transform.GetPositionX() - 672) / (42 * 32);
	int county = ((int)hero.transform.GetPositionY() - 672) / (42 * 32);
	int offestx = ((int)hero.transform.GetPositionX() - 672) % (42 * 32) / 32;
	int offesty = ((int)hero.transform.GetPositionY() - 672) % (42 * 32) / 32;

	for (int i = 0; i < 42; i++) {
		for (int j = 0; j < 42; j++) {
			mapmapoffestx[i][j] = 0;
			mapmapoffesty[i][j] = 0;
		}
	}
	if (offestx < 0 || countx < 0) {

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
void draw_title(int x, int y, GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image& image) {//draw a pixil image at (x,y) position on the canvas

	for (int i = 0; i < image.height; i++) {
		for (int j = 0; j < image.width; j++) {
			if (x + j >= 0 && i + y >= 0 && x + j < canvas.getWidth() && i + y < canvas.getHeight()) {
				if (image.alphaAt(j, i)) {
					canvas.draw(x + j, y + i, image.at(j, i));
				}


			}

		}
	}

}
void draw_object(GamesEngineeringBase::Window& canvas, GameObject** obj, int count) {//draw a pixil image at (x,y) position on the canvas

	for (int o = 0; o < count; o++) {
		if (obj[o]) {

			draw_collision(*obj[o], canvas);//draw collision box for testing
			for (int i = 0; i < obj[o]->image.height; i++) {
				for (int j = 0; j < obj[o]->image.width; j++) {
					if (true) {
						if (obj[o]->image.alphaAt(j, i)) {
							camera_draw(j, i, obj[o]->image, canvas, obj[o]);
							//canvas.draw(obj[o]->transform.GetPositionX() + j-Camera::GetCamera().GetX(), obj[o]->transform.GetPositionY() + i - Camera::GetCamera().GetY(), obj[o]->image.at(j, i));
						}


					}

				}
			}

		}
	}


}
void camera_draw(float x, float y, GamesEngineeringBase::Image& image, GamesEngineeringBase::Window& canvas, GameObject* obj) {
	if (obj->transform.GetPositionX() + x - Camera::GetCamera().GetX() >= 0 && obj->transform.GetPositionX() + x - Camera::GetCamera().GetX() < canvas.getWidth() && obj->transform.GetPositionY() + y - Camera::GetCamera().GetY() >= 0 && obj->transform.GetPositionY() + y - Camera::GetCamera().GetY() < canvas.getHeight())
		canvas.draw(obj->transform.GetPositionX() + x - Camera::GetCamera().GetX(), obj->transform.GetPositionY() + y - Camera::GetCamera().GetY(), obj->image.at(x, y));
}

void draw_collision(GameObject& gameobject, GamesEngineeringBase::Window& canvas) {
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

	scvtest = false;

}
void draw_entire_background(int** mapsave1, GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image* tiles, int** offestmapx, int** offestmapy, Water*** watermap) {
	for (int i = 0; i < canvas.getHeight(); i++) {
		for (int j = 0; j < canvas.getWidth(); j++) {
			canvas.draw(j, i, 0, 0, 0);
		}
	}
	//scvcount++;
	for (int i = 0; i < 42; i++) {
		for (int j = 0; j < 42; j++) {
			if (mapsave1[i][j] > -1 && mapsave1[i][j] < 24) {
				if (mapsave1[i][j] >= 14 && mapsave1[i][j] <= 22) {
					watermap[i][j]->transform.SetPosition((j * 32) + offestmapx[j][i], (i * 32) + offestmapy[j][i]);
					watermap[i][j]->Update(0, Camera::GetCamera());

				}

				draw_title((j * 32) - Camera::GetCamera().GetX() + offestmapx[j][i], (i * 32) - Camera::GetCamera().GetY() + offestmapy[j][i], canvas, tiles[mapsave1[i][j]]);

			}
		}


	}
}
void controlHero(Hero& hero, GamesEngineeringBase::Window& canvas, float move) {


	if (canvas.keyPressed('W')) {


		hero.transform.SetPosition(hero.transform.GetPositionX(), hero.transform.GetPositionY() - move);
		hero.Update();
		if (GameObjectManager::getInstance().checkwater()) {
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
	if (canvas.keyPressed('N')) {
		if (Hero::getInstance().getabilitytimecount() >= 10.f) {
			enemiesmanager::getInstance().killsomeenemies(Hero::getInstance().getabilitymax());
			Hero::getInstance().setabilitytimecount(0.f);
		}

	}

}
