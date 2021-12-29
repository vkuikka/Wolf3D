# Wolf3D
Wolfenstein 3D rendering technique recreated.

## Installation
- Clone and open this repository.
- Run `make`. this should first compile libft library and then compile the project itself.
- If your operating system is not osx you have to get the correct frameworks for SDL2 and SDL2_image and replace the current ones with those.

## Usage
- Before running the program you should make a map in another file.
	- Eaxmple of valid a map:
		```
		1 1 1 1
		1 0 0 1
		1 0 0 1
		1 1 1 1
		```
	- All lines have to be the same length and there should not be empty lines.
	- Zeros in the map represent area where the player can move.
	- The map has to be surrounded by walls.
	- Any other number is a wall.
- Run the program by giving the name of the map file as argument.
	- eg. `./wolf3d map.txt`

## Controls
- Moving:
	- w, a, s and d
	- up and down arrows
- Turning:
	- q and e
	- left and right arrows
- FOV (field of view) can be changed with numbers 1 and 2

**A bunch of parameters including window resolution and move speed can be changed from macros in wolf.h**
