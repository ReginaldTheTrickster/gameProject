#include "musics.hpp"

using namespace std;

Mix_Music* Music::loadMusic(const string path){
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"SDL_mixer could not initialize! SDL_mixer Error: %s\n",Mix_GetError());
        SDL_Quit();
    }

    Mix_Music* gMusic=Mix_LoadMUS(path.c_str());
    if(gMusic==nullptr)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"Could not load music! SDL_mixer Error: %s\n", Mix_GetError());
    return gMusic;
}

void Music::play(Mix_Music* gMusic){
    if(gMusic==nullptr) return;

    if(Mix_PlayingMusic()==0) Mix_PlayMusic(gMusic,-1);
    else if(Mix_PausedMusic()==1) Mix_ResumeMusic();
}
