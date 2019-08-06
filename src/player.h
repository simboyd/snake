#pragma once
#include <vector>
#include "Square.h"

class Player
{
private:
	std::vector<Square*> tiles; // the snake itself
	std::vector<Square>& boxes; // the grid

public:
	int size;
	int direction; // 1=up, 2=right, 3=down, 4=left
	bool alive;
	Player(std::vector<Square>&);
	bool (Player::*func)();
	bool moveUp();
	bool moveDown();
	bool moveRight();
	bool moveLeft();
	void reset();
};
