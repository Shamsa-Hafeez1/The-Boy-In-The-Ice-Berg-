#include "waterbending.hpp"

Waterbending::Waterbending() {}

Waterbending::~Waterbending() {}

Waterbending::Waterbending(SDL_Texture* asset, SDL_Rect move)
{
    mover = move; 
    mover.x -= 30; 
    mover.h = 30; 
    mover.w = 30;  
    assets = asset; 
    src = {0, 0, 300, 300}; 
}

void Waterbending::show(SDL_Renderer* Renderer)
{     
    Unit::draw(Renderer); 
    mover.x -= 10;  
}


