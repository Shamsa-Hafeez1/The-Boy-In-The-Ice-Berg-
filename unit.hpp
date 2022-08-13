
#pragma once
#include <fstream> 
#include "SDL.h"

/** \brief This class is used to treat each of its child classes as a Unit so that it can be drawn on screen and return Mover
 * 
 */
class Unit
{  
    public: 
        Unit(); 
        ~Unit();

        /** This constructor takes Renderer as a parameter 
         * 
         */
        Unit(SDL_Texture*);
 

        /** Draws the particular Unit on screen 
         * 
         */
        void draw(SDL_Renderer*);

        /** This function returns the Mover
         * 
         */
        SDL_Rect getMover();
        
    protected:
        SDL_Texture* assets;
        SDL_Rect src;
        SDL_Rect mover;
};