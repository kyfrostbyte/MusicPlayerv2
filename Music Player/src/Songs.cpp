#include "Songs.h"
// Songs.cpp

#include "Songs.h"

Songs::Songs(const std::string& artist, const std::string& title)
        : artist(artist), title(title) {
}

// other member function implementations...

void Songs::displaySongs() {
    cout << this->title << this->artist;

}



