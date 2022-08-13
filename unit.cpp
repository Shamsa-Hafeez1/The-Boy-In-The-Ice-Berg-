#include "unit.hpp"
#include <iostream> 
using namespace std; 

Unit::Unit() { }

Unit::Unit(SDL_Texture* asset): assets(asset){ } 

Unit::~Unit() { } 

void Unit::draw(SDL_Renderer* Renderer) 
{      
    SDL_RenderCopy(Renderer, assets, &src, &mover); 
}

SDL_Rect Unit::getMover() 
{     
    return mover; 
}


