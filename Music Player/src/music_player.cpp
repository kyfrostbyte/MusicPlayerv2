// music_player.cpp

#include "music_player.h"
#include <iostream>
#include "SDL_mixer.h"
#include "SDL.h"

MusicPlayer::MusicPlayer() : songs{"Song1", "Song2", "Song3"}, currentSong(nullptr) {
    // Initialize SDL_mixer or any other necessary setup
    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
        std::cerr << "SDL_mixer initialization failed! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

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
        std::cout << "4: Display Available Songs\n"; // New option
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
            case 4:
                displayAvailableSongs();
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
    if (currentSong == nullptr) {
        // Load background music (down.wav in this case)
        currentSong = Mix_LoadMUS("down.wav");
        if (currentSong == nullptr) {
            std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return;
        }
    }

    if (isPlaying) {
        // Pause music
        Mix_PauseMusic();
        std::cout << "Paused the music\n";
    } else {
        // Resume or start playing music
        Mix_ResumeMusic();
        std::cout << "Playing the music\n";
    }

    isPlaying = !isPlaying; // Toggle the play/pause state
}

void MusicPlayer::nextSong() {
    // Implement next song logic
    std::cout << "Next Song\n";
}

void MusicPlayer::previousSong() {
    // Implement previous song logic
    std::cout << "Previous Song\n";
}

void MusicPlayer::displayAvailableSongs() {
    std::cout << "Available Songs:\n";
    for (size_t i = 0; i < songs.size(); ++i) {
        std::cout << i + 1 << ": " << "Song " << i + 1 << "\n";
    }

    int songChoice;
    std::cout << "Select a song by its number (0 to return to the menu): ";
    std::cin >> songChoice;

    if (songChoice >= 1 && static_cast<size_t>(songChoice) <= songs.size()) {
        // Play the selected song
        if (songChoice == 1) {
            // Play the down.wav file using SDL_mixer
            Mix_Chunk* sound = Mix_LoadWAV("../down.wav");
            if (sound == nullptr) {
                std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
            } else {
                Mix_PlayChannel(-1, sound, 0);
                std::cout << "Now playing: " << "Song " << songChoice << "\n";
                SDL_Delay(200000);  // Delay to allow the sound to play (adjust as needed)
                Mix_FreeChunk(sound);
            }


        } else {
            // Implement logic for other songs
            std::cout << "Now playing: " << "Song " << songChoice << "\n";
        }
    } else if (songChoice == 0) {
        std::cout << "Returning to the menu\n";
    } else {
        std::cout << "Invalid choice. Returning to the menu\n";
    }
}