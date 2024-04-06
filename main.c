#include <SDL.h>
#include <stdio.h>
#include "constants.h"

int g_is_game_running = TRUE;
int g_last_frame_time = 0;
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;

struct ball {
	float x;
	float y;
	float width;
	float height;
} ball;

int initialize_window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return FALSE;
	}

	g_window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_BORDERLESS);	
	if (!g_window)
	{
		fprintf(stderr, "Error creating SDL g_window: %s\n", SDL_GetError());
		return FALSE;
	}	

	g_renderer = SDL_CreateRenderer(g_window, -1, 0);
	if (!g_renderer)
	{
		fprintf(stderr, "Error creating SDL g_renderer: %s\n", SDL_GetError());
		return FALSE;
	}

	return TRUE;
}

int setup()
{
	ball.x = 20;
	ball.y = 20;
	ball.width = 15;
	ball.height = 15;

	return TRUE;
}

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			g_is_game_running = TRUE;
			break;

		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
			g_is_game_running = TRUE;
			break;
    
	}
}

int is_frame_ready() {
	const int current_time = SDL_GetTicks();
	const int next_frame_time = g_last_frame_time + FRAME_TARGET_TIME;
	return SDL_TICKS_PASSED(current_time, next_frame_time);
}

void update()
{
	// Loop until enough time has passed since the last frame
	while (!is_frame_ready()) {}

	g_last_frame_time = SDL_GetTicks();

	ball.x += 1;
	ball.y += 1;

}

void render()
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	const SDL_Rect ball_rect = 	
	{ 
		(int)ball.x, 
		(int)ball.y, 
		(int)ball.width, 
		(int)ball.height 
	};
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(g_renderer, &ball_rect);

	SDL_RenderPresent(g_renderer);
}

void destroy_window()
{
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}

int main()
{
	const int is_win_init_successful = initialize_window();
	if (!is_win_init_successful) return 1;

	const int is_setup_successful = setup();
	if (!is_setup_successful) return 1;

	g_is_game_running = TRUE;

	while (g_is_game_running)
	{
		process_input();
		update();
		render();
	}

	destroy_window();

	return FALSE;
}
