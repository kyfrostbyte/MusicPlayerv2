// music_player.cpp

#include "thread"

#include "Windows.h"
#include "music_player.h"
#include <iostream>
#include "SDL_mixer.h"
#include "SDL.h"
#include "atomic"
#include "Songs.h"
#include <vector>






MusicPlayer::MusicPlayer() : songs{"Song1", "Song2", "Song3"}, currentSong(nullptr), songFinished(false) {
    // Initialize SDL_mixer or any other necessary setup
    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
        std::cerr << "SDL_mixer initialization failed! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }



}

// Modify the destructor to join the SDL event thread
MusicPlayer::~MusicPlayer() {



    // Clean up resources (e.g., close SDL_mixer)
    Mix_CloseAudio();
}


void MusicPlayer::run() {
    Songs *song1 = new Songs(static_cast<std::string>("Stick Season"), static_cast<std::string>("Noa Kahn"));
    Songs *song2 = new Songs(static_cast<std::string>("2tick Season"), static_cast<std::string>("Noah ahn"));
    Songs *song3 = new Songs(static_cast<std::string>("3tick Season"), static_cast<std::string>("Noah Kahn"));

    std::vector<Songs*> allSongs = {song1, song2, song3};



    int choice;
    while (true) {
        // Display menu
        displayMenu();

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
                Mix_CloseAudio();
                return;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}



void MusicPlayer::playPause() {
    if (currentSong == nullptr) {
        // Load background music (down.wav in this case)
        currentSong = Mix_LoadMUS(R"(C:\Users\aaron\Desktop\College Stuff\Applied Programming\CLion\Music Player\assets\Music\down.wav)");
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

#include <future> // Include for std::async

void MusicPlayer::displayAvailableSongs() {
    std::cout << "Available Songs\n";
    std::cout << "  1: Down - Jay Sean\n";
    std::cout << "  2: Dynamite - Teo Cruz\n";
    std::cout << "  3: Stick Season - Noah Kahn\n";

    int songChoice;
    std::cout << "Select a song by its number (0 to return to the menu): ";
    std::cin >> songChoice;

    if (songChoice >= 1 && static_cast<size_t>(songChoice) <= songs.size()) {
        const char* filePath = getSongPath(songChoice);

        {
            std::unique_lock<std::mutex> lock(sdlMutex);
            Mix_Music* music = Mix_LoadMUS(filePath);
            if (music == nullptr) {
                std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
                return;
            }

            Mix_HookMusicFinished(&MusicPlayer::musicFinishedCallback);

            // Play the music
            Mix_PlayMusic(music, 0);

            std::cout << "Now playing: " << this->currentSong << "\n";

            bool spacePressed = false;
            std::cout << "Press Space to end song and return to menu \n" << std::endl;
            do {


                // Check if the space key is pressed
                if (GetAsyncKeyState(SDLK_SPACE) & 0x8000) {
                    // Perform your action here
                    std::cout << "Space key pressed! Performing an action..." << std::endl;
                    isPlaying = false;
                    spacePressed = true;
                }

                // Optional: Insert a small delay to reduce CPU usage


            } while (!spacePressed);

            // Free the music after the song has finished playing
            Mix_FreeMusic(music);
        }
    } else if (songChoice == 0) {
        std::cout << "Returning to the menu\n";
    } else {
        std::cout << "Invalid choice. Returning to the menu\n";
    }
}



void MusicPlayer::displayMenu(){
    // Display menu
    std::cout << "Choose an option:\n";
    std::cout << "1: Play / Pause Song\n";
    std::cout << "2: Next Song\n";
    std::cout << "3: Previous Song\n";
    std::cout << "4: Display Available Songs\n"; // New option
    std::cout << "0: Exit\n";
    std::cout << "Your choice: ";
}







// Helper function to get the file path for a selected song
const char *MusicPlayer::getSongPath(int songChoice) const {
    switch (songChoice) {
        case 1:
            return R"(C:\Users\aaron\Desktop\College Stuff\Applied Programming\CLion\Music Player\assets\Music\down.wav)";
        case 2:
            return R"(C:\Users\aaron\Desktop\College Stuff\Applied Programming\CLion\Music Player\assets\Music\Dynamite.wav)";
        case 3:
            return R"(C:\Users\aaron\Desktop\College Stuff\Applied Programming\CLion\Music Player\assets\Music\Stick Season.wav)";
        default:
            return"";
    }
}

// Modify the musicFinishedCallback function
void MusicPlayer::musicFinishedCallback() {
    // Access non-static members using an instance of the class
    MusicPlayer* player = MusicPlayer::getInstance();

    // Set the flag to true when the music finishes
    if (player != nullptr) {
        player->songFinished = true;
    }
}


MusicPlayer* MusicPlayer::getInstance() {
    static MusicPlayer instance;  // Create a single instance on first call
    return &instance;
}