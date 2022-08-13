#pragma once 
#include <iostream> 
#include <string>
#include "powers.hpp"

using namespace std; 

/** \brief Firebending is a child class of Power class and is used to make Aang capable of using 
 */ 

class Firebending: public Power
{
    public: 
        Firebending(); 
        ~Firebending(); 

        /** The copy constructor of Firebending assigns mover and src coordinates to Airbending as well as assigned asset
        */
        Firebending(SDL_Texture*, SDL_Rect);

        /** show function displays the air ball moving downwards 
        */     
        void show(SDL_Renderer*);
};
