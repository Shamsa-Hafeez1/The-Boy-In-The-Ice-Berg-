#pragma once 
#include "powers.hpp"
#include <iostream>

using namespace std; 

/** \brief Airbending is a child class of Power class and is used to make Aang capable of using air
 */ 

class Airbending: public Power
{
    public: 
        Airbending();
        ~Airbending(); 

        /** The copy constructor of Airbending assigns mover and src coordinates to Airbending as well as assigned asset
        */ 
        Airbending(SDL_Texture* , SDL_Rect);

        /** show function displays the air ball moving rightwards. 
         */ 
        void show(SDL_Renderer*);
};