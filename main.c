#include <SDL.h>
#include <stdio.h>
#include "constants.h"

int is_game_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int initialize_window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return FALSE;
	}

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_BORDERLESS);	
	if (!window)
	{
		fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
		return FALSE;
	}	

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
		return FALSE;
	}

	return TRUE;
}

int setup()
{
	// TODO: Add your setup logic here
	return TRUE;
}

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			is_game_running = FALSE;
			break;

		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
			is_game_running = FALSE;
			break;
    
	}
}

void update()
{
	// TODO: Add your update logic here
}

void render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void destroy_window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main()
{
	const int is_win_init_successful = initialize_window();
	if (is_win_init_successful == FALSE) return FALSE;

	const int is_setup_successful = setup();
	if (is_setup_successful == FALSE) return FALSE;

	is_game_running = TRUE;

	while (is_game_running == TRUE)
	{
		process_input();
		update();
		render();
	}

	destroy_window();

	return TRUE;
}
