#include <SDL.h>
#include <stdio.h>
#include "constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int initialize_window() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return FAIL;
    }
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT,
        SDL_WINDOW_BORDERLESS);
    {
        fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
        if (!window) return FAIL;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) { 
        fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
        return FAIL; 
    }

    return SUCCESS;
}

int main() {
    // Create a 2d array to represent the tiles
    int tiles[TILES_X][TILES_Y];

    // Initialize the tiles to 0
    for (int x = 0; x < TILES_X; x++) {
        for (int y = 0; y < TILES_Y; y++) {
            tiles[x][y] = 0;
        }
    }

    if (initialize_window() == FAIL) return 1; // Exit if window initialization fails

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Tiles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    return 0;
}
