# This is the game I made for my Basics of Programming 1 class.

It's written in C, I used SDL2 for the graphics and some more SDL2 helper libraries.

I got the idea for this game, from a popular website: [loldodgegame](www.loldodgegame.com), and I basically copied the idea with a couple of twists.


## How to run

As I wasn't familiar with makefiles at the time, I used one gcc command found at the official site for this class: [infoc](https://infoc.eet.bme.hu/sdl_telepito/)

You can find out how to install SDL2 and compile this game from the site above.

(In the future I might update this repo, and create a makefile)

`
gcc owldodgegame/src/main.c -o ${PROGRAM_NAME} `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_mixer
`
Replace PROGRAM_NAME with the name you want your binary to be.
