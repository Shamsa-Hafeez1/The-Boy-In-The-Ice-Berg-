#pragma once 
#include <SDL.h>
#include <SDL_image.h>
#include <fstream> // input from text file 
#include <cstring> // strcpy 

using namespace std; 
/** 
 * \brief This class takes account of Health points through out the game 
 * 
 * This class is the parent class of aangHealth and zukoHealth class,
 * Both Aang and Prince Zuko have 10 health points by default which keep and 
 * are assigned a particular src and mover as per their source asset 
 * and screen position. 
 * 
 */


class Health {
   public:
        /** Operator -- is used to decrease the 
        * health points which has been by default set up to 10
        */ 
        void operator --(); 

        /** draw is used to draw the health bar on top right corner of screen 
        */ 
        virtual void draw(SDL_Texture*, SDL_Renderer*);

        /** isFinished is a function that determines if the the health points are finished or not
        */         
        bool isFinished(); 


    protected:
        int health_points = 10; 
        SDL_Rect src; 
        SDL_Rect mover; 

}; 
