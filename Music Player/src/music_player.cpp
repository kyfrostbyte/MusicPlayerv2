#include "thread"
#include "Windows.h"
#include "music_player.h"
#include <iostream>
#include "SDL_mixer.h"
#include "SDL.h"
#include "atomic"
#include "Songs.h"
#include <vector>
#include <algorithm>
#include <future>

MusicPlayer::MusicPlayer() : songs(), currentSong(nullptr), songFinished(false) {
    songs.push_back(Songs("Down", "Jay Sean", R"(C:\Users\aaron\Desktop\College Stuff\Applied Programming\CLion\Music Player\assets\Music\down.wav)", 1));
    songs.push_back(Songs("Dynamite", "Teo Cruz", R"(C:\Users\aaron\Desktop\College Stuff\Applied Programming\CLion\Music Player\assets\Music\Dynamite.wav)", 2));
    songs.push_back(Songs("Stick Season", "Noah Kahn", R"(C:\Users\aaron\Desktop\College Stuff\Applied Programming\CLion\Music Player\assets\Music\Stick Season.wav)", 3));


    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
        std::cerr << "SDL_mixer initialization failed! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

MusicPlayer::~MusicPlayer() {
    Mix_CloseAudio();
}


void MusicPlayer::run() {
    int choice;
    while (true) {
        // Display menu
        displayMenu();

        // Get user input
        std::cin >> choice;

        // Perform action based on user choice
        switch (choice) {
            case 1:
                displayAvailableSongs();
                break;
            case 2:
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




void MusicPlayer::displayAvailableSongs() {
    std::cout << "Available Songs\n";
    for (size_t i = 0; i < songs.size(); ++i) {
        std::cout << "  " << i + 1 << ": " << songs[i].getTitle() << " - " << songs[i].getArtist() << "\n";
    }

    int songChoice;
    std::cout << "Select a song by its number (0 to return to the menu): ";
    std::cin >> songChoice;

    if (songChoice >= 1 && static_cast<size_t>(songChoice) <= songs.size()) {
        // Get the selected song
        const Songs& selectedSong = songs[songChoice - 1];


        const std::string filePath = selectedSong.getSongPath();

        {
            std::unique_lock<std::mutex> lock(sdlMutex);
            Mix_Music* music = Mix_LoadMUS(filePath.c_str());
            if (music == nullptr) {
                std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
                return;
            }

            Mix_HookMusicFinished(&MusicPlayer::musicFinishedCallback);

            // Play the music
            Mix_PlayMusic(music, 0);

            std::cout << "Now playing: " << selectedSong.getTitle() << " - " << selectedSong.getArtist() << "\n";

            bool spacePressed = false;
            std::cout << "Press Space to end the song and return to the menu \n" << std::endl;
            do {
                // Check if the space key is pressed
                if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                    std::cout << "Space key pressed! Ending the song..." << std::endl;
                    isPlaying = false;
                    spacePressed = true;
                }

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
    std::cout << "1: Display Available Songs\n";
    std::cout << "2: Exit\n";
    std::cout << "Your choice: ";
}







//// Helper function to get the file path for a selected song

const std::string MusicPlayer::getSongNum(int songChoice) const {
    switch (songChoice) {
        case 1:
            return "Down";
        case 2:
            return "Dynamite";
        case 3:
            return "Stick Season";
        default:
            return "";
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