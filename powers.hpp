#pragma once 
#include "Unit.hpp"
#include <iostream> 
using namespace std; 

/** \brief This class provides the four elemental powers to Aang 
 * 
 * Power is the parent class which takes account of Airbending, Waterbending, Firebending and Earthbending which is to be used by Aang.
 */ 

class Power: public Unit 
{
    public:
        Power(); 
        ~Power(); 
        virtual void show(SDL_Renderer*) = 0; // Pure Virtual Function 
};