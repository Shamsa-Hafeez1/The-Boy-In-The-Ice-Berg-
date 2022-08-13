#include "earthbending.hpp"

Earthbending::Earthbending() {}

Earthbending::~Earthbending() {}

Earthbending::Earthbending(SDL_Texture* asset, SDL_Rect move) {
    mover = move; 
    mover.y -= 50; 
    mover.h = 30; 
    mover.w = 30;  
    assets = asset; 
    src = {0, 0, 300, 300}; 
}

void Earthbending::show(SDL_Renderer* Renderer) {      // Draws object on screen 
    Unit::draw(Renderer); 
    mover.y -= 10;  
}
