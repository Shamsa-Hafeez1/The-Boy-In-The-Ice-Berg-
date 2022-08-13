#pragma once 
#include "unit.hpp"

using namespace std; 
/**
 * \brief This class is of Enimies i.e. FireNationGuards from which Aang needs to save himself 
 * 
 */

class FireNationGuards: public Unit
{
    public:
        ~FireNationGuards(); 
        FireNationGuards(SDL_Texture*);

        /** Draws FireNationGuards on screen 
         * 
         */
        void draw(SDL_Renderer*);

        /** Decides whether an attack needs to be generated or not. 
         * The attack probability is 50% 
         */

        bool attack(); 

        /** Moves the FireNation Guard downwards 
         */
        void move(SDL_Renderer*);

        /** A FireNationGuard is dead after making 3 attacks. 
         * This function determines whether the FireNationGuard is still alive or not 
         * i.e. This function explains whether the FireNationGuard has completed its 3 attacks or not 
         */
        bool isAlive();

    private:
        int NoOfAttacks = 0;  
};