#pragma once
#include <SDL.h>

class Square
{
	SDL_Surface* wind = nullptr;
	bool isPlayer;
	bool isFood;
	int which;
	SDL_Rect box;
	static int color;


public:
	Square(SDL_Surface*, bool, int, int, int);
	void snakify();
	void desnakify();
	void foodify();
	bool check_if_free() const;
	bool check_if_food() const;
	bool check_if_player() const;
	int get_which() const;

};

