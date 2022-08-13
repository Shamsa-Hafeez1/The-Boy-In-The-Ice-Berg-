#pragma once
#include <fstream> 
#include "unit.hpp"
#include "health.hpp"
#include "aanghealth.hpp"

using namespace std; 

/** \brief this class is storing the Functions and attributes of player - Aang 
 * 
 * 
 * Aang has 10 health points by default and upon every collision with the attacks made by Fire Nation Guards or Prince Zuko, one health point reduces 
*/

class Aang: public Unit 
{
    public:
        Aang(); 
        ~Aang(); 

        /** This function sets the src coordinates , mover coordinates and assets 
         */
        Aang(SDL_Texture*);

        /** draw function make the updated Aang on screen as per user's input.
         * User can give an input of up, down, left or right and Aang is drawn accordingly on screen. 
         */

        void draw(bool, bool, bool, bool, SDL_Renderer*); 

        /** draw_health function, draws the health points of Aang on top right corner of the screen. 
         */
        void draw_health(SDL_Texture*, SDL_Renderer*); 

        /** decreaseLife function is called when Aang collides with attacks made by Fire Nation Guards or Prince Zuko. 
         * It deceases the health of Aang by 1 which was orignally set to 10. 
         */
        void decreaseLife(); 

        /** isAlive function determines whether the number of lives for aang has finished or not. When the lives are over, Aang is dead and game is over. 
         */
        bool isAlive(); 

        /** Operator overloading << ofstream is used to write game state in txt file. 
         */
        friend ofstream& operator<<(ofstream&, Aang&); 

    private:
        /** health is the health points of Aang 
         */
        aangHealth health; 
}; 