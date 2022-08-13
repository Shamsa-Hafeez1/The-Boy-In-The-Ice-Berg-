#include "health.hpp"
#include <iostream> 
using namespace std; 

/** 
 * Operator overlaoding has been used in order to decrease the health points 
 */

void Health::operator -- ()
{ 
    health_points --; 
    if (health_points < 0)
        health_points = 0; 
}

void Health::draw (SDL_Texture* assets, SDL_Renderer* Renderer)
{ 
	SDL_RenderCopy( Renderer, assets, &src, &mover);		
}

bool Health::isFinished()
{
    if (health_points <= 0) 
        return true; 
    return false; 
}

