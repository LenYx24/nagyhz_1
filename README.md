# This is the game I developed for my Basics of Programming 1 class.

It's written in C, I used SDL2 for the graphics and SDL2 helper libraries (SDL_image,gfx,ttf).

I got the idea for this game, from a popular website: [loldodgegame](www.loldodgegame.com), and I basically copied the game and simplified it a bit.

## How to run

As I wasn't familiar with makefiles at the time, I used one gcc command found at the official site for this class: [infoc](https://infoc.eet.bme.hu/sdl_telepito/)

You can find out how to install SDL2 and compile this game from the site above. For linux it's as simple as downloading the sdl2 packages from your package manager.

(In the future I might update this repo, and create a makefile)

``
cd owldodgegame &&  

gcc owldodgegame/src/*.c owldodgegame/include/*.h -o ${PROGRAM_NAME} `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_mixer
``

Replace PROGRAM_NAME with the name you want your binary to be, then run the file.
