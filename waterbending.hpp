#pragma once 
#include "powers.hpp"
#include <iostream> 

using namespace std; 

/** \brief Waterbending is a child class of Power class and is used to make Aang capable of using water elemental power 
 */

class Waterbending: public Power
{
    public: 
        Waterbending(); 
        ~Waterbending(); 

        /** The copy constructor of Waterbending assigns mover and src coordinates to Waterbending as well as assigned asset
        */
        Waterbending(SDL_Texture* , SDL_Rect);

        /** show function displays the water ball moving leftwards
        */  
        void show(SDL_Renderer*);

};
