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
#include"GameObject.h"
#include"Hero.h"
#include<iostream>
#include<fstream>
#include<string>
#include "GamesEngineeringBase.h" // Include the GamesEngineeringBase header
bool scvtest=true;

void draw_title(int x, int y, GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image& image);
void draw_entire_background(int **mapsave1, GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image* tiles);
void controlHero(Hero& hero, GamesEngineeringBase::Window& canvas, float move);
void draw_collision(GameObject& gameobject, GamesEngineeringBase::Window& canvas);

using namespace std;

int main() {
	
	HRESULT hr = CoInitialize(NULL); //  初始化 COM

	GamesEngineeringBase::Timer timer;
	
	ifstream file("../Resources/tiles.txt");
	Hero hero;
	float dt = timer.dt();
	int move = hero.getMoveSpeed() * dt;

	int** mapsave1 = new int* [42];
	for (int i = 0; i < 42; i++)
		mapsave1[i] = new int[42];
	/*int mapsave1[42][42];
	for (int i = 0; i < 42; i++) {
		for (int j = 0; j < 42; j++) {
			mapsave1[i][j] = -1;
		}
	}*/

	
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
	for (int i = 0; i < 42; i++) {
		for (int j = 0; j < 42; j++) {
			cout<<mapsave1[i][j]<<"  ";
		}
		cout << endl;
	}
	GamesEngineeringBase::Image tiles[24];
	for (int i = 0; i < 24; i++) {
		 cout<<tiles[i].load("../Resources/"+to_string(i)+".png")<<endl;

	}
	

	GamesEngineeringBase::Image image;
	GamesEngineeringBase::Window canvas;

	image.load("../Resources/A.png");
	// Create a canvas window with dimensions 1024x768 and title “Tiles"
	

	
	unsigned int planeX = 300;  // Initial x-coordinate for the plane image.
	unsigned int planeY = 300;

	canvas.create(1920, 1920, "Tiles");
	bool running = true; // Variable to control the main loop's running state.
	while (running)
	{
		if (canvas.keyPressed(VK_ESCAPE)) break;
		controlHero(hero, canvas, move);
		// Check for input (key presses or window events)
		// Clear the window for the next frame rendering
		canvas.clear();
	
		draw_entire_background(mapsave1, canvas, tiles);
		draw_title((int)floorf(hero.transform.GetPositionX()), (int)floorf(hero.transform.GetPositionY()), canvas, hero.heroimage);
		
		draw_collision(hero, canvas);
		float dt = timer.dt();
		 move = hero.getMoveSpeed() * dt;
		
		// Update game logic
		// Draw();
		// Display the frame on the screen. This must be called once the frameis finished in order to display the frame.
			canvas.present();
	}
	return 0;
}

void draw_title(int x, int y, GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image& image) {//draw a pixil image at (x,y) position on the canvas

	for ( int i = 0; i < image.height; i++) {
		for ( int j = 0; j < image.width; j++) {
			if(x + j >=0&&i+y>=0){
				if (image.alphaAt(j, i)) {
					canvas.draw(x + j, y + i, image.at(j, i));
				}
				//cout << i + x <<"   "<< j + y<<endl;//only a little test can be used
				
			}
			
		}
	}
	
}
void draw_collision(GameObject& gameobject, GamesEngineeringBase::Window& canvas) {
	for (int i = gameobject.collision.getcollisionX(); i < gameobject.collision.getcollisionX()+ gameobject.collision.getcollisionW(); i++) {
		canvas.draw(i, gameobject.collision.getcollisionY(), 0, 0, 225);
		if (scvtest)
		cout << i << "   " << gameobject.collision.getcollisionY() << endl;
		
		
		
		
	}
	for (int i = gameobject.collision.getcollisionY(); i < gameobject.collision.getcollisionY() + gameobject.collision.getcollisionH(); i++) {
		canvas.draw(gameobject.collision.getcollisionX(),i , 0, 0, 225);
		
	}
	scvtest = false;

}
void draw_entire_background(int **mapsave1, GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image* tiles) {
	for (int i = 0; i < 42; i++) {
		for (int j = 0; j < 42; j++) {
			if (mapsave1[i][j] > -1 && mapsave1[i][j] < 24) {

				draw_title(j * 32, i * 32, canvas, tiles[mapsave1[i][j]]);
			}
		}


	}
}
void controlHero(Hero& hero, GamesEngineeringBase::Window& canvas,float move) {
	

	if (canvas.keyPressed('W')) {
		hero.transform.SetPosition(hero.transform.GetPositionX(),hero.transform.GetPositionY() - move);
		cout << hero.transform.GetPositionY() << endl;
		

	}
	if (canvas.keyPressed('S')) {
		hero.transform.SetPosition(hero.transform.GetPositionX(), hero.transform.GetPositionY() + move);
		cout << hero.transform.GetPositionY() << endl;

	}
	if (canvas.keyPressed('A')) {
		hero.transform.SetPosition(hero.transform.GetPositionX()-move, hero.transform.GetPositionY() );

	}
	if (canvas.keyPressed('D')) {
		hero.transform.SetPosition(hero.transform.GetPositionX() + move, hero.transform.GetPositionY());

	}
}
