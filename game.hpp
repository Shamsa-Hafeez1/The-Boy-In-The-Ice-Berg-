#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <SDL_mixer.h>
#include <fstream> // input from text file 
#include <cstring> // strcpy 

#include "unit.hpp"
#include "aang.hpp"
#include "FireNationGuards.hpp"
#include "fire.hpp"
#include "powers.hpp"
#include "airbending.hpp"
#include "waterbending.hpp"
#include "earthbending.hpp"
#include "firebending.hpp"
#include "prince_zuko.hpp"
using namespace std;


enum {menu, instructions, credits, exitGame};  
enum {resumeGame, NewGame};

/** \brief This is the game class through which the entire game is handled 
 * 
 */

class Game {
    public:
        Game(); 
        ~Game();
        /** Initializes the game 
         */
        bool init();

        /**Loads all pictures , assets , music 
         */
        bool loadMedia();

        /**Closes the game 
         */
        void close();

        /** Loads all the images 
         */
        SDL_Texture* loadTexture( std::string path );
        
        /**
         * Level 1 of the game in which aang has to save himself 
         * 
         */
        void run1();

        /**
         * Level 2 of the game in which aang can defend himself using elemental powers 
         * 
         */
        void run2();
        /**
         * Level 3 of the game in which aang can defend himself using elemental powers and needs to make Prince Zuko Die 
         * 
         */
        void run3();  

        /**
         * Draws Objects of FireNationGuards and Fire on screen 
         */
        void drawAllObjects();

        /** makeEnemy generates enemies at a probability of 10%
         * 
         */
        void makeEnemy();

        /** Erases FireNationGuards if they are dead 
         * or else adds a Fire in the list of Fire 
         */
        void updateEnemy();  

        /**Ends the game 
         */
        void end(); 

        /** Updates the score of player if he collides with Fire 
         * i.e. Decrease score of player by 1 upon collision with fire 
         * 
         */
        void updateScoring(Aang &player); 

        /** Updates score in level 3 
         * Aangs health decrease upon collision with fire 
         * Zuko life decreases upon collision with Aang's attack 
         * 
         */
        void updateScoring(Aang &player, PrinceZuko &zuko); 

        /** If Fire collides with player then play the music 
         * and returns true 
         * 
         */
        bool FireCollidesPlayer(SDL_Rect, SDL_Rect); 

        /** returns true is the game is won 
         */
        bool getWin(); 
        bool gamewin();
        bool Over(); 
        void reset(); 
        void playerAttacks(Aang &player, bool& earth, bool& fire, bool& water, bool& air) ;
        void attackPersists() ;  

        /** Finds if Aang's attack has collided with prince Zuko's attack 
         * 
         */
        void attackCollidesAttack();

        /** Displays main menu page 
         * 
         */
        bool show_menu(); 
 
        bool pause_menu();
        void playMusic(); 
        /**Saves necessary information to preserve current state 
         */
        void writeState(Aang&, PrinceZuko&); 
        /** reads all the contents of readState.txt file 
         * 
         */
        void readState();

private:
    //Screen dimension constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture* assets = NULL;
    SDL_Texture* guard_asset = NULL; 
    SDL_Texture* fire_asset = NULL; 
    SDL_Texture* health_asset = NULL; 
    SDL_Texture* level2_aang = NULL; 
    SDL_Texture* level3_aang = NULL; 
    SDL_Texture* airbend_asset = NULL; 
    SDL_Texture* earthbend_asset = NULL; 
    SDL_Texture* waterbend_asset = NULL; 
    SDL_Texture* firebend_asset = NULL; 
    SDL_Texture* zuko = NULL; 
    SDL_Texture* zuko_health = NULL; 

    Mix_Music *bgMusic = NULL;
    Mix_Music *collisionSound = NULL;

    list <FireNationGuards*> guards;
    list <Fire*> fire_list; 
    list <Power*> powers; 
    
    bool level_over = false; 
    bool win = false; 
    bool pause = false;
    int level = 1; 
};

