cmake_minimum_required(VERSION 3.27)

project(Music_Player)
set(CMAKE_WIN32_EXECUTABLE "${PROJECT_NAME}.exe")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")

# Add your source files
add_executable(Music_Player main.cpp src/music_player.cpp
        src/Songs.cpp
        include/Songs.h)

# Set additional properties if needed
set_target_properties(Music_Player PROPERTIES WIN32_EXECUTABLE false)

# Add the path to the SDL2 installation
set(SDL2_DIR "C:/Users/aaron/Desktop/SDL2-2.28.5/x86_64-w64-mingw32")

# Add the necessary SDL2 headers
include_directories("${SDL2_DIR}/include/SDL2")

# Add the path to the SDL_mixer installation
set(SDL2_mixer_DIR "C:/Users/aaron/Desktop/SDL2_mixer-2.8.0/x86_64-w64-mingw32")

# Add the necessary SDL_mixer headers
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Link the SDL2 libraries
target_link_libraries(Music_Player "${SDL2_DIR}/lib/libSDL2.a" ${CMAKE_DL_LIBS})
target_link_libraries(Music_Player hid setupapi imm32 version winmm)

# Link the SDL_mixer library
target_link_libraries(Music_Player "${SDL2_mixer_DIR}/lib/libSDL2_mixer.a" ${CMAKE_DL_LIBS})

# Include the necessary directories
target_include_directories(Music_Player PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Manually set SDL2_mixer include directories and libraries
set(SDL2_MIXER_INCLUDE_DIRS "C:/Users/aaron/Desktop/College Stuff/Applied Programming/CLion/Music Player/include")
set(SDL2_MIXER_LIBRARIES "C:/Users/aaron/Desktop/SDL2_mixer-2.8.0/x86_64-w64-mingw32/lib/libSDL2_mixer.a")

# Include SDL2_mixer directories
include_directories(${SDL2_MIXER_INCLUDE_DIRS})

# Link SDL2_mixer library
target_link_libraries(Music_Player ${SDL2_MIXER_LIBRARIES} -lwinmm -lole32 -loleaut32 -luuid -lwinmm -lversion -limm32 -lsetupapi -lhid)