#ifndef MUSIC_HPP_INCLUDED
#define MUSIC_HPP_INCLUDED

#include<SDL.h>
#include<SDL_mixer.h>

#include<bits/stdc++.h>

using namespace std;

namespace Music{
    Mix_Music* loadMusic(const string path);

    void play(Mix_Music* gMusic);
}

#endif // !MUSIC_HPP_INCLUDED
