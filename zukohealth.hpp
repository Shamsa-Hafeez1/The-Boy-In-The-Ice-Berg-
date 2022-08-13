#pragma once 
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include "health.hpp"
 
using namespace std; 

/** \brief This class is inherited from Health class and is used to monitor health bar of PrinceZuko
 * 
 */
class zukoHealth: public Health 
{
    public:

        /** draws the health bar of PrinceZuko on the right top corner of screen ( with blue circles )
         * Health points are drawn as per the current Health Points of Prince Zuko 
         */
        void draw(SDL_Texture* assets, SDL_Renderer* Renderer); 

        /** Overload the operation << in order to be able to write the current health_points of PrinceZuko in gameState.txt file 
         * 
         */
        friend ofstream& operator<<(ofstream&, zukoHealth&); 
}; 