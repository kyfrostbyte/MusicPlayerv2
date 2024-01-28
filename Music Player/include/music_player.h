// music_player.h

#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <vector>
#include <string>
#include <thread>
#include "SDL_mixer.h"
#include "atomic"
#include "Songs.h"
#include <condition_variable>



class MusicPlayer {
public:
    MusicPlayer();
    ~MusicPlayer();
    static void musicFinishedCallback();
    void run();
    std::vector<Songs*> allSongs;
    bool isPlaying;

private:
    void playPause();
    void nextSong();
    void previousSong();
    void displayAvailableSongs();
    std::vector<Songs> songs;
    Mix_Music* currentSong;
    static MusicPlayer* getInstance();
    void playSongReal(const char *filePath);
    void displayMenu();

    std::mutex sdlMutex;
    std::condition_variable sdlCondition;
    bool sdlEventReceived = false;
    std::atomic<bool> songFinished;
    const char *getSongPath(int songChoice) const;

    const std::string getSongNum(int songChoice) const;
};

#endif
