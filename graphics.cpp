#include "graphics.hpp"

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

#include<bits/stdc++.h>

#include "board.hpp"
#include "defines.hpp"
#include "game.hpp"
#include "pieces.hpp"

using namespace std;

void Graphics::initSDL() {
    SDL_Init(SDL_INIT_EVERYTHING);
}

void Graphics::cleanupSDL(SDL_Renderer* renderer, SDL_Window* window){
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window* Graphics::createSDLWindow() {
    return SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
}

SDL_Renderer* Graphics::createSDLRenderer(SDL_Window* window){
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"2");
    return SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);
}

void Graphics::drawChessboard(SDL_Renderer* renderer, Board* board){
    Piece p;
    Location selected_piece=board->getSelectedPiece();

    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++){
            SDL_Rect tile;

            tile.x=j*TILE_SIZE;
            tile.y=i*TILE_SIZE;
            tile.w=TILE_SIZE;
            tile.h=TILE_SIZE;

            if((i+j)%2==((board->isReversed())? 1:0)){
                SDL_SetRenderDrawColor(renderer,0xEE,0xEE,0xEE,0xFF);
            } else{
                SDL_SetRenderDrawColor(renderer,0x99,0x99,0x99,0xFF);
            }

            if(selected_piece.first==i && selected_piece.second==j){
                SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,0xFF);

                SDL_Rect highlight;
                highlight.x=tile.x+5;
                highlight.y=tile.y+3;
                highlight.w=tile.w-10;
                highlight.h=tile.h-10;

                SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,0xFF);
                SDL_RenderFillRect(renderer,&tile);

                if ((i+j)%2==((board->isReversed())? 1:0)) SDL_SetRenderDrawColor(renderer,0xEE,0xEE,0xEE,0xFF);
                else SDL_SetRenderDrawColor(renderer,0x99,0x99,0x99,0xFF);

                SDL_RenderFillRect(renderer,&highlight);
            } else SDL_RenderFillRect(renderer,&tile);

            p=board->board[i][j];

            if(p){
                string filepath="pieces\\"+Pieces::getPieceFilename(p);

                SDL_Surface* image=IMG_Load(filepath.c_str());
                if (image==NULL) cerr<<"image="<<image<<" Reason: "<<SDL_GetError()<<" "<< SDL_GetBasePath()<<'\n';
                SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,image);

                SDL_RenderCopy(renderer,texture,NULL,&tile);

                SDL_FreeSurface(image);
                SDL_DestroyTexture(texture);
            }

            if(board->hasSelectedPiece() && Game::isValidMove(board,board->getSelectedPiece(),makeLocation(i,j),1)){
                SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,0xFF);

                int centerX = tile.x+tile.w/2;
                int centerY = tile.y+tile.h/2;
                int radius=15;
                SDL_RenderFillCircle(renderer,centerX,centerY,radius);
            }
        }
    }
}

int Graphics::SDL_RenderFillCircle(SDL_Renderer* renderer,int x,int y,int radius){
    int offsetx,offsety,d;
    int status;

    offsetx=0;
    offsety=radius;
    d=radius-1;
    status=0;

    while(offsety>=offsetx){
        status+=SDL_RenderDrawLine(renderer,x-offsety,y+offsetx,x+offsety,y+offsetx);
        status+=SDL_RenderDrawLine(renderer,x-offsetx,y+offsety,x+offsetx,y+offsety);
        status+=SDL_RenderDrawLine(renderer,x-offsetx,y-offsety,x+offsetx,y-offsety);
        status+=SDL_RenderDrawLine(renderer,x-offsety,y-offsetx,x+offsety,y-offsetx);

        if(status<0){
            status=-1;
            break;
        }

        if(d>=2*offsetx){
            d-=2*offsetx+1;
            offsetx+=1;
        } else if(d<2*(radius-offsety)){
            d +=2*offsety-1;
            offsety--;
        } else{
            d+=2*(offsety-offsetx-1);
            offsety--;
            offsetx++;
        }
    }

    return status;
}

void Graphics::handleMouseClicked(SDL_MouseButtonEvent event,Board* board) {
    if (event.button==SDL_BUTTON_RIGHT) return;

    Location board_indices=getBoardIndices(event.x,event.y);

    if (board->getSelectedPiece()==board_indices) board->clearSelectedPiece();
    else if(!board->hasSelectedPiece()){
        if(board->getPieceAt(board_indices)!=0 && Pieces::getPieceColor(board->getPieceAt(board_indices))==board->getActiveColor()){
            board->setSelectedPiece(board_indices.first, board_indices.second);
        }
    } else if(board->hasSelectedPiece()){
        if(Pieces::getPieceColor(board->getPieceAt(board_indices))==Pieces::getPieceColor(board->getPieceAt(board->getSelectedPiece()))){
            board->setSelectedPiece(board_indices.first,board_indices.second);
        } else board->tryMove(board->getSelectedPiece(),board_indices);
    }


}

void Graphics::handleKeyPressed(SDL_KeyboardEvent event, Board* board) {
    if(event.keysym.sym==SDL_GetKeyFromName("r") || event.keysym.sym==SDL_GetKeyFromName("f")){
        cout<<"r/f pressed, reversing board"<<'\n';
        board->reverse();
    }
}

Location Graphics::getBoardIndices(int x,int y){
    Location out;

    out.second=x/TILE_SIZE;
    out.first=y/TILE_SIZE;

    return out;
}
