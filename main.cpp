#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

#include<bits/stdc++.h>

#include "board.hpp"
#include "game.hpp"
#include "graphics.hpp"
#include "musics.hpp"

using namespace std;

int main(int argc,char** argv){
    Graphics::initSDL();

    SDL_Window* window=Graphics::createSDLWindow();
    SDL_Renderer* renderer=Graphics::createSDLRenderer(window);
    Board board;
    SDL_Event event;

    board.readFen(STARTING_FEN);
    board.printBoard();

    Mix_Music* BGM=Music::loadMusic("bgm\\bgm.mp3");
    Music::play(BGM);

    bool running=1;
    bool gameOver=0;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                running=0;
            } else if(event.type==SDL_MOUSEBUTTONUP){
                Graphics::handleMouseClicked(event.button,&board);
            } else if(event.type==SDL_KEYUP){
                Graphics::handleKeyPressed(event.key,&board);
            }
        }

        if(gameOver) continue;

        if(Game::isInCheckmate(&board,WHITE)){
            cout<<"CHECKMATE! BLACK WINS!"<<'\n';
            gameOver=1;
        }
        if(Game::isInCheckmate(&board,BLACK)){
            cout<<"CHECKMATE! WHITE WINS!"<<'\n';
            gameOver=1;
        }

        SDL_RenderClear(renderer);
        Graphics::drawChessboard(renderer,&board);

        SDL_RenderPresent(renderer);
    }
    if(BGM!=nullptr) Mix_FreeMusic(BGM);

    Graphics::cleanupSDL(renderer,window);

    return 0;
}
