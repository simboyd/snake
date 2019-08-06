#include "Square.h"

int Square::color = 100;

Square::Square(SDL_Surface* wnd, bool wh, int which, int x, int y) : wind(wnd), isPlayer(wh), which(which) {
	box.h = 32; box.w = 32; box.x = x; box.y = y;
	isFood = false;
}

void Square::snakify()	{ if (Square::color == 100) Square::color = 120; else Square::color = 100; isPlayer = true; 
						isFood = false; SDL_FillRect(wind, &box, SDL_MapRGB(wind->format, 0, Square::color, 0)); }
void Square::desnakify(){ isPlayer = false; isFood = false; 
						SDL_FillRect(wind, &box, SDL_MapRGB(wind->format, 255, 255, 255)); }
void Square::foodify()	{ isPlayer = false; isFood = true;  SDL_FillRect(wind, &box, SDL_MapRGB(wind->format, 255, 0, 0));}
bool Square::check_if_free() const { if (isPlayer == false && isFood == false) return true; else return false; }
bool Square::check_if_food() const { if (isFood) return true; else return false; }
bool Square::check_if_player() const { if (isPlayer) return true; else return false; }
int Square::get_which() const { return which; }