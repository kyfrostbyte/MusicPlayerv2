// Songs.h

#ifndef MUSIC_PLAYER_SONGS_H
#define MUSIC_PLAYER_SONGS_H

#include <iostream>
#include <string>

class Songs {
private:
    std::string songPath;
    std::string title;
    std::string artist;
    int songNum;
    int duration;

public:
    // Default constructor with default values
    Songs(const std::string& artist = "", const std::string& title = "", const char* songPath = "", const int& songNum =0);

    // Getters
    std::string getSongPath() const { return songPath; }
    std::string getTitle() const { return title; }
    std::string getArtist() const { return artist; }
    int getSongNum() const { return songNum; }
    int getDuration() const { return duration; }

    // Setters (if needed)
    void setSongPath(const std::string& path) { songPath = path; }
    void setTitle(const std::string& newTitle) { title = newTitle; }
    void setArtist(const std::string& newArtist) { artist = newArtist; }
    void setDuration(int newDuration) { duration = newDuration; }
    void displaySongs() const;

    // Other member functions...
};

#endif // MUSIC_PLAYER_SONGS_H
