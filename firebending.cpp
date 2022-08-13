#include "firebending.hpp"

Firebending::Firebending() { }

Firebending::~Firebending() { }

Firebending::Firebending(SDL_Texture* asset, SDL_Rect move) {
    mover = move; 
    mover.y += 50; 
    mover.h = 30; 
    mover.w = 30;  
    assets = asset; 
    src = {0, 0, 300, 300}; 
}

void Firebending::show(SDL_Renderer* Renderer) {      
    Unit::draw(Renderer); 
    mover.y += 10;  
}
