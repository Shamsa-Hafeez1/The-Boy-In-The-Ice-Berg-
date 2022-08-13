#pragma once 
#include <iostream> 
#include <fstream>
#include "unit.hpp"
#include "zukohealth.hpp"


using namespace std;

/** \brief PrinceZuko class takes account of functions and attributes of Prince Zuko (enemy)
 * 
 * 
 */ 

class PrinceZuko: public Unit
{
    public:

        ~PrinceZuko(); 
        
        /** This function sets the src coordinates , mover coordinates and assets 
         */
        PrinceZuko(SDL_Texture*);

        /** draw function draws prince zuko on screen and makes it move randomly. 
         */
        void draw(SDL_Renderer*); 

        /** Draws the health points of prince zuko on the top right corner of screen (blue in color)
         */
        void draw_health(SDL_Texture*, SDL_Renderer*); 

        /** decreaseLife function is called when PrinceZuko is collides with Aang's attack
         * It decreases the health of Prince Zuko by 1 which was orignally set to 10. 
         */
        void decreaseLife();
         
        /** isAlive function determines whether the number of lives for PrinceZuko has finished or not. When the lives are over, Zuko is dead and game is over. 
         */
        bool isAlive(); 

        /** Decides whether an attack needs to be generated or not. 
         * The attack probability is 50% 
         */
        bool attack(); 

        /** Operator overloading << ofstream is used to write game state in txt file. 
         */
        friend ofstream& operator<<(ofstream&, PrinceZuko&); 

    private:
        /** health is the health points of PrinceZuko
         */
        zukoHealth health; 
        
}; 