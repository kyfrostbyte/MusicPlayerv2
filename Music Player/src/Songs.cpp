#include "Songs.h"
#include <iostream>
// Holds information of all songs
Songs::Songs(const std::string& artist, const std::string& title, const char* songPath, const int& songNum)
        : artist(artist), title(title), songPath(songPath), songNum(songNum) {
}



void Songs::displaySongs() const {
    std::cout << this->title << " - " << this->artist << std::endl;
}
