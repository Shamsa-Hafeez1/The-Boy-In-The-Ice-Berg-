# The-Boy-In-The-Ice-Berg-

Group Members: Shamsa Hafeez, Abdullah Fareed, Ramis Raza 

A game made on C++ incorporating Object Oriented Programming Concepts. 

## How to Play? 
Player Movement: 
- Press Arrow keys to move Aang 

Pause: 
- Press Space bar to Pause Game 

Powers (applicable from Level 2): 
- Press A for airbending (moves forward) 
- Press W for waterbending (moves backwards) 
- Press E for earthbending (moves upwards) 
- Press F for firebending (moves downwards) 

Level 1: Aang must avoid collision with fireballs without having any powers 
Level 2: Defend Aang from fireballs using powers 
Level 3: Defear Zuko to win the game using powers 

## How to Compile: 
- Open this folder in VSCode
- Open VSCode terminal and put this command to compile everything:

	g++ *.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

- Run the game by this command:

	.\a.exe
