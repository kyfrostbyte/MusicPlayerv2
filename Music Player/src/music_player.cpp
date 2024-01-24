#include "music_player.h"
#include <iostream>

MusicPlayer::MusicPlayer() : songs{"Song1", "Song2", "Song3"}, currentSong(nullptr) {
    // Initialize SDL_mixer or any other necessary setup
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void MusicPlayer::run() {
    int choice;

    while (true) {
        // Display menu
        std::cout << "Choose an option:\n";
        std::cout << "1: Play / Pause Song\n";
        std::cout << "2: Next Song\n";
        std::cout << "3: Previous Song\n";
        std::cout << "0: Exit\n";
        std::cout << "Your choice: ";

        // Get user input
        std::cin >> choice;

        // Perform action based on user choice
        switch (choice) {
            case 1:
                playPause();
                break;
            case 2:
                nextSong();
                break;
            case 3:
                previousSong();
                break;
            case 0:
                std::cout << "Exiting program\n";
                // Clean up resources (e.g., close SDL_mixer)
                Mix_CloseAudio();
                return;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    }
}

void MusicPlayer::playPause() {
    // Implement play/pause logic
    std::cout << "Play/Pause Song\n";
}

void MusicPlayer::nextSong() {
    // Implement next song logic
    std::cout << "Next Song\n";
}

void MusicPlayer::previousSong() {
    // Implement previous song logic
    std::cout << "Previous Song\n";
}
