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
    void displayAvailableSongs(); // New function to display available songs

    std::vector<std::string> songs;
    Mix_Music* currentSong; // Updated to Mix_Music pointer for background music
    bool isPlaying; // New flag to track whether music is playing
};

#endif // MUSIC_PLAYER_H

