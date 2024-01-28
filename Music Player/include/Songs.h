#ifndef MUSIC_PLAYER_SONGS_H
#define MUSIC_PLAYER_SONGS_H
#include <iostream>
#include <string>
using namespace std;

class Songs {


private:
    string songPath = "";
    string title = "";
    string artist = "";
    int duration = 0;

public:
    Songs(const std::string& artist = "", const std::string& title = "");
    // Getters
    string getSongPath()    { return this->songPath; }
    string getTitle()    { return this->title; }
    string getArtist()      { return this->artist;   }
    int getDuration()       { return this->duration; }

    // Setters
    void setSongPath(string songPath) { this->songPath = songPath; }
    void setTitle(string title) { this->title= title; }
    void setArtist(string artist)     { this->artist = artist; }
    void setDuration(int duration) { this->duration = duration; }

    void displaySongs();




};



#endif //MUSIC_PLAYER_SONGS_H
