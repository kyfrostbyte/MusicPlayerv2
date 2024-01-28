# Overview

This is a terminal music player built in C++. It uses the SDL and SDL_Mixer libraries to process .WAV files allowing you to play songs directly from the terminal.
The SDL and SDL_Mixer libraries do all the leg work in terms of audio processes. By initializing the mixer and opening up an audio channel, you can then load a .WAV file into it.
This program essentially provides a link between the music files and the mixer. The Songs class handles all the information for the songs, such as title, arist, and filepath. The program prompts the user to select 
a song, and the file path of that song is then fed to the mixer, which begins to play it. The music_player class handles the loop of menu navigation, and is really where the whole program comes to life.

This is the first project I have done in C++. I started it to begin to familiarize myself with C++ because of how commonly used it is in industry. I figured that building something like
a terminal music player would result in me being exposed so some of the most fundamental concepts of C++ like pointers, header files, and build instructions. Just the act of getting the libraries 
set up was difficult for me, but I have a much better understanding of how C++ works as a whole.


[Software Demo Video](https://youtu.be/zZsmYdru5FA)

# Development Environment

I originally decided to use Visual Studio because of its GUI capabilities, but soon realized I had bit off more than I could chew for a first project in a new language. 
After of few hours of trying to install the proper libraries in Visual Studio, I decided to take a step back and start fresh.
I ended up switching over to CLion, because it has good support for C++ programs, and the GUI was no longer as important. I used two external libraries, SDL and SDL_Mixer both of which provide
a ton of options for working with audio files. They are both commonly used to control the sound in games and animations. 

* [SDL2](https://wiki.libsdl.org/SDL2/FrontPage)  
* [SDL_Mixer 2.0](https://wiki.libsdl.org/SDL2_mixer/FrontPage)

# Useful Websites

- [SDL2 Installation](https://wiki.libsdl.org/SDL2/Installation)
- [SDL2 Tutorials](https://wiki.libsdl.org/SDL2/Tutorials)
- [W3 Schools](https://www.w3schools.com/cpp/)

# Future Work
- Add next and previous song functionality
- Run mixer on separate thread so song plays in background
- Next song to play when current song ends (implement duration)
- Map to GUI
- Implement slipstream audio
