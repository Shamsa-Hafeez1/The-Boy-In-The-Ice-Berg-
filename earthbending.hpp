#pragma once 
#include <iostream> 
#include "powers.hpp"


using namespace std; 

/** \brief Earthbending is a child class of Power class and is used to make Aang capable of using earth / rocks 
 */ 

class Earthbending: public Power
{
    public: 
        Earthbending();  
        ~Earthbending(); 

        /** The copy constructor of Airbending assigns mover and src coordinates to Airbending as well as assigned asset
        */
        Earthbending(SDL_Texture* , SDL_Rect);

        /** show function displays the air ball moving rightwards. 
        */ 
        void show(SDL_Renderer*);
};
