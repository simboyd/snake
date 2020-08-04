#include "core.h"

Setup::Setup()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(-1);
	if (TTF_Init() == -1)
		exit(-2);
	srand((unsigned int)time(NULL));
	gWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
		WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!gWindow)
		exit(-3);

	Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	gRenderer = SDL_CreateRenderer(gWindow, -1, renderer_flags);
	if (!gRenderer)
		exit(-4);

	geo = TTF_OpenFont("geofont.ttf", 32);

	isRunning = true;

	// magic number galore from here
	windowSurface = SDL_GetWindowSurface(gWindow);
	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;
	SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, r, g, b));
	int x = 10, y = 10;
	for (int i = 0; i < 400; i++)
	{
		vec.push_back(Square(windowSurface, false, i, x, y));
		vec[i].desnakify();
		x += 32;
		if (x > 640)
		{
			x = 10;
			y += 32;
		}
	}
	player = new Player(vec);
	thereIsFood = false;
	starttime = (unsigned int)time(NULL);
}



void Setup::listen() 
{
	/* // listens for events and handles the living fuck out of them */
	SDL_Event game_event;
	SDL_PollEvent(&game_event);
	if (game_event.type == SDL_QUIT)
		isRunning = false;
	else if (game_event.type == SDL_KEYDOWN)
	{
		switch (game_event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			isRunning = false;
			break;
		case SDLK_DOWN:
			if(player->direction != 1) player->func = &Player::moveDown;
			break;
		case SDLK_UP:
			if (player->direction != 3) player->func = &Player::moveUp;
			break;
		case SDLK_LEFT:
			if (player->direction != 2) player->func = &Player::moveLeft;
			break;
		case SDLK_RIGHT:
			if (player->direction != 4) player->func = &Player::moveRight;
			break;

		default:
			break;
		}
	}
}

void Setup::update()
{
	if (!thereIsFood)
	{
		int random;
		do {
			random = rand() % 400;
		} while (!vec[random].check_if_free());

		vec[random].foodify();
	}
	if (!player->alive)
	{
		ask(); 
		(player->*(player->func))();
	}
	else
		thereIsFood = !((player->*(player->func))()); // atrocious; but also kind of cool. needs a macro
}

void Setup::render()
{
	// text stuff 

	SDL_Rect outline;
	SDL_Color tc = { 255, 255, 255 };
	SDL_Color bc = { r, g, b };
	std::string message = "qula: ";
	std::string time_text = "gasuli dro: ";
	message.append(std::to_string(player->size) + "  ");
	time_text.append(std::to_string((unsigned int)time(NULL) - starttime) + "  ");
	SDL_Surface* text = TTF_RenderText_Shaded(geo, message.c_str(), tc, bc);
	outline.h = 50;
	outline.w = 240;
	outline.x = 670;
	outline.y = 25;
	text = TTF_RenderText_Shaded(geo, message.c_str(), tc, bc);
	SDL_BlitSurface(text, NULL, windowSurface, &outline);
	SDL_FreeSurface(text);
	text = TTF_RenderText_Shaded(geo, time_text.c_str(), tc, bc);
	outline.y = 65;
	SDL_BlitSurface(text, NULL, windowSurface, &outline);

	// final render and cleanup 
	SDL_UpdateWindowSurface(gWindow);
	SDL_FreeSurface(text);
}

bool Setup::running() const
{
	return isRunning;
}

Setup::~Setup()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyTexture(mainTexture);
	SDL_Quit();
	TTF_CloseFont(geo);
	TTF_Quit();
	gWindow = nullptr;
	gRenderer = nullptr;
	delete player;
}

void Setup::ask()
{

	bool hovering_yes = false, hovering_no = false;
	while (true)
	{
		SDL_RenderClear(gRenderer);

		SDL_Rect box = { 170, 190, 680, 280 };
		SDL_Color fg = { 255, 255, 255 };
		SDL_Color bg = { 0, 0, 255 };
		SDL_Color bg_yes = { 0, 0, 255 };
		SDL_Color bg_no = { 0, 0, 255 };

		SDL_FillRect(windowSurface, &box, SDL_MapRGB(windowSurface->format, 0, 0, 255));
		
		std::string message = "TamaSi dasrulda. Tqven daagroveT "; 
		message.append(std::to_string(player->size) + " qula.");
		SDL_Surface* text = TTF_RenderText_Shaded(geo, message.c_str(), fg, bg);
		box = { 190, 210 };
		SDL_BlitSurface(text, NULL, windowSurface, &box);
		SDL_FreeSurface(text);

		message = "gsurT Tavidan TamaSi?";
		text = TTF_RenderText_Shaded(geo, message.c_str(), fg, bg);
		box = { 340, 290 };
		SDL_BlitSurface(text, NULL, windowSurface, &box);
		SDL_FreeSurface(text);

		SDL_Rect box_yes = { 300, 400, 150, 40 };
		SDL_Rect box_no = { 550, 400, 150, 40 };

		if (hovering_yes)
		{
			SDL_FillRect(windowSurface, &box_yes, SDL_MapRGB(windowSurface->format, 0, 0, 100));
			bg_yes.b = 100;
		}
		if (hovering_no)
		{
			SDL_FillRect(windowSurface, &box_no, SDL_MapRGB(windowSurface->format, 0, 0, 100));
			bg_no.b = 100;
		}

		message = "ki";
		text = TTF_RenderText_Shaded(geo, message.c_str(), fg, bg_yes);
		box = { 365, 399 };
		SDL_BlitSurface(text, NULL, windowSurface, &box);
		SDL_FreeSurface(text);

		message = "ara";
		text = TTF_RenderText_Shaded(geo, message.c_str(), fg, bg_no);
		box = { 605, 401 };
		SDL_BlitSurface(text, NULL, windowSurface, &box);
		SDL_FreeSurface(text);

		SDL_Texture* mainTexture = SDL_CreateTextureFromSurface(gRenderer, windowSurface);
		SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);

		SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
	
		SDL_RenderDrawRect(gRenderer, &box_yes);
		SDL_RenderDrawRect(gRenderer, &box_no);

		SDL_RenderPresent(gRenderer);
		SDL_DestroyTexture(mainTexture);
	
		SDL_Event mouse;
		SDL_PollEvent(&mouse);
		if (mouse.type == SDL_MOUSEMOTION || mouse.type == SDL_MOUSEBUTTONDOWN)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x >= 300 && x <= 450 && y >= 400 && y <= 440)
			{
				hovering_yes = true;
				if (mouse.type == SDL_MOUSEBUTTONDOWN)
				{
					reset(); break;
				}
			}
			else
				hovering_yes = false;
			if (x >= 550 && x <= 700 && y >= 400 && y <= 440)
			{
				hovering_no = true;
				if (mouse.type == SDL_MOUSEBUTTONDOWN)
				{
					isRunning = false; break;
				}
			}
			else
				hovering_no = false;

		}
	}
}

void Setup::reset()
{
	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;
	SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, r, g, b));
	player->reset();
	thereIsFood = false;
}
