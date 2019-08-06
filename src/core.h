#pragma once


#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <time.h>
#include <string>
#include <iostream>
#include "Square.h"
#include "Player.h"

#define TITLE "Gaym"
#define WINDOW_WIDTH 1009
#define WINDOW_HEIGHT 660

class Setup {
private:
	
	SDL_Window* gWindow = nullptr;
	SDL_Surface* windowSurface = nullptr;
	SDL_Renderer* gRenderer = nullptr;
	Player* player = nullptr;
	TTF_Font* geo = nullptr;
	SDL_Texture* mainTexture = nullptr;
	bool isRunning;
	long int starttime;
	void ask(); // ask if player wants to continue after losing
	void reset(); // reset a game after losing
	unsigned char r, g, b;

public:
	
	Setup();
	~Setup();
	
	bool thereIsFood;
	std::vector<Square> vec;

	// listens for events and handles them
	void listen();

	// checks for loss, creates food, moves snake
	void update();

	// renders updated graphics to the screen
	void render();

	// tests if the application needs to shut down or not
	bool running() const;

};