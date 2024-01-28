#include "Songs.h"
#include <iostream>

Songs::Songs(const std::string& artist, const std::string& title, const char* songPath, const int& songNum)
        : artist(artist), title(title), songPath(songPath), songNum(songNum) {
}

// Other member function implementations...

void Songs::displaySongs() const {
    std::cout << this->title << " - " << this->artist << std::endl;
}
