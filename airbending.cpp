#include "airbending.hpp"

Airbending::Airbending() {}

Airbending::~Airbending() {}

Airbending::Airbending(SDL_Texture* asset, SDL_Rect move)
{
    mover = move; 
    mover.x += 50; 
    mover.h = 30; 
    mover.w = 30;  
    assets = asset; 
    src = {0, 0, 300, 300}; 
}

void Airbending::show(SDL_Renderer* Renderer)
{      
    Unit::draw(Renderer); 
    mover.x += 10;  
}


