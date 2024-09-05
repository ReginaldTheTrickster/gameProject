#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include<SDL.h>
#include<SDL_image.h>

#include "board.hpp"

const int WINDOW_WIDTH=800;
const int WINDOW_HEIGHT=640;

const int TILE_SIZE=80;

namespace Graphics{
    void initSDL();
    void cleanupSDL(SDL_Renderer* renderer, SDL_Window* window);

    SDL_Window* createSDLWindow();
    SDL_Renderer* createSDLRenderer(SDL_Window* window);

    void drawChessboard(SDL_Renderer* renderer,Board* board);
    int SDL_RenderFillCircle(SDL_Renderer* renderer,int x,int y,int radius);

    void handleMouseClicked(SDL_MouseButtonEvent event,Board* board);
    void handleKeyPressed(SDL_KeyboardEvent event,Board* board);

    pair<int,int> getBoardIndices(int x,int y);
}

#endif  // !GRAPHICS_H_INCLUDED
