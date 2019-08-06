
#include "Player.h"

Player::Player(std::vector <Square>& o_boxes) : boxes(o_boxes)
{
	tiles.push_back(&boxes.front());
	tiles.front()->snakify();
	func = &Player::moveRight;
	direction = 2;
	alive = true;
	size = 1;
	//btw, now i realize that I'll have to use the dreaded direction
	//variable even though I tried to avoid it by using a function pointer
	//but i'm not gonna get rid of the function pointers now cause i spent
	//a bunch of time on them 
}
bool Player::moveUp()
{
	bool ateFood = false;
	direction = 1;

	if (tiles.back()->get_which() >= 20) // if we're not about to hit the edge
	{
		ateFood = (tiles.back() - 20)->check_if_food();
		alive = !(tiles.back() - 20)->check_if_player();
		tiles.push_back(tiles.back() - 20); // assign next tile to the snake
	}
	else // if we are
	{
		ateFood = (tiles.back() + 380)->check_if_food();
		alive = !(tiles.back() + 380)->check_if_player();
		tiles.push_back(tiles.back() + 380); // assign the first tile of current row to the snake
	}
	if (!ateFood)
	{
		tiles.front()->desnakify(); // turn off first tile
		tiles.erase(tiles.begin()); // delete the old tile from snake 
	}
	else
		size++;
	tiles.back()->snakify(); // turn on the new tile
	return ateFood;
}
bool Player::moveDown()
{
	bool ateFood = false;
	direction = 3;
	
	if (tiles.back()->get_which() <= 379)
	{
		ateFood = (tiles.back() + 20)->check_if_food();
		alive = !(tiles.back() + 20)->check_if_player();
		tiles.push_back(tiles.back() + 20);
	}
	else
	{
		ateFood = (tiles.back() - 380)->check_if_food();
		alive = !(tiles.back() - 380)->check_if_player();
		tiles.push_back(tiles.back() - 380);
	}

	if (!ateFood)
	{
		tiles.front()->desnakify();
		tiles.erase(tiles.begin());
	}
	else
		size++;
	tiles.back()->snakify();
	return ateFood;
}
bool Player::moveRight()
{
	bool ateFood = false;
	direction = 2;

	if ((tiles.back()->get_which() + 1) % 20 != 0)
	{
		ateFood = (tiles.back() + 1)->check_if_food();
		alive = !(tiles.back() + 1)->check_if_player();
		tiles.push_back(tiles.back() + 1); 
	}
	else
	{
		ateFood = (tiles.back() - 19)->check_if_food();
		alive = !(tiles.back() - 19)->check_if_player();
		tiles.push_back(tiles.back() - 19);
	}

	if (!ateFood)
	{
		tiles.front()->desnakify();
		tiles.erase(tiles.begin());
	}
	else
		size++;
	tiles.back()->snakify();
	return ateFood;
}
bool Player::moveLeft()
{
	bool ateFood = false;
	direction = 4;

	if (tiles.back()->get_which() % 20 != 0)
	{
		ateFood = (tiles.back() - 1)->check_if_food();
		alive = !(tiles.back() - 1)->check_if_player();
		tiles.push_back(tiles.back() - 1);
	}
	else
	{
		ateFood = (tiles.back() + 19)->check_if_food();
		alive = !(tiles.back() + 19)->check_if_player();
		tiles.push_back(tiles.back() + 19);
	}
	
	if (!ateFood)
	{
		tiles.front()->desnakify();
		tiles.erase(tiles.begin());
	}
	else
		size++;
	tiles.back()->snakify();
	return ateFood;
}

void Player::reset()
{
	tiles.clear();
	for (int i = 0; i < 400; i++)
		(boxes.begin() + i)->desnakify();
	tiles.push_back(&boxes.front());
	alive = true;
	direction = 2;
	size = 1;
	tiles.front()->snakify();
	func = &Player::moveRight;
}