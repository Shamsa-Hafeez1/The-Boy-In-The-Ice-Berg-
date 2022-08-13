#pragma once 
#include "unit.hpp"
#include "prince_zuko.hpp"

/** \brief This class is used for implemeting functions regarding fire balls which are produced by FireNationGuards 
 * 
 */

class Fire: public Unit
{
    public:
        ~Fire(); 

        /** The copy constructor of Fire assigns mover and src coordinates to Fire being used by Fire nation guards 
        */ 
        Fire(SDL_Texture*, SDL_Rect);
        
        /** Draws the fire ball being thrown by FireNationGurads and moves it leftwards 
         */
        void draw(SDL_Renderer*); 
}; 