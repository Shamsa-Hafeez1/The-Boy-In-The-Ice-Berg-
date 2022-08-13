#pragma once 
#include <iostream> 
#include <fstream> 
#include "health.hpp"

using namespace std;  

/** \brief This aangHealth class is inherited from Health class and is used to monitor health bar of Aang. 
 * 
 * It draws the health bar on the top right corner of the screen as well as per the health points 
 */

class aangHealth: public Health
{
    public:
    /** draw function draws the health points of aang on the yop right corner of the screen. 
     */
        void draw(SDL_Texture*, SDL_Renderer*); 

    /** ofstream operator << has been overloaded in order to store the health points of Aang in the Gamestate.txt file 
     */ 
        friend ofstream& operator<<(ofstream&, aangHealth&); 
}; 