#include <SDL.h>
#include "SDL_mixer.h"
#include <cstdio>
#include "music_player.h"

int WinMain(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    // Load sound effect
    Mix_Chunk* sound = Mix_LoadWAV(R"(C:\Users\aaron\Desktop\College Stuff\Applied Programming\CLion\Music Player\assets\Music\down.wav)");

    if (sound == nullptr) {
        fprintf(stderr, "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    // Play the sound effect
//    Mix_PlayChannel(-1, sound, 0);

    // Delay to allow the sound to play
//    SDL_Delay(200000);

    MusicPlayer musicPlayer;
    musicPlayer.run();

    // Free resources and close SDL
    Mix_FreeChunk(sound);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}