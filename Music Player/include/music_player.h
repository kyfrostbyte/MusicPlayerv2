#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <vector>
#include <string>
#include "SDL_mixer.h" // Include SDL_mixer header

class MusicPlayer {
public:
    MusicPlayer();

    void run();

private:
    void playPause();
    void nextSong();
    void previousSong();

    std::vector<std::string> songs;
    Mix_Chunk* currentSong; // Declare currentSong member
};

#endif // MUSIC_PLAYER_H
