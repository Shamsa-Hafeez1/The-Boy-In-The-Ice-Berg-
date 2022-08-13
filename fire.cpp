#include "fire.hpp"

Fire::~Fire(){ }

Fire::Fire(SDL_Texture* fire_asset, SDL_Rect mover_fire): Unit(fire_asset)
{ 
    mover = mover_fire; 
    src = {0, 0, 500, 500}; 
}

void Fire::draw(SDL_Renderer* Renderer)
{
    mover.x -= 10; 
    mover.h = 30; 
    mover.w = 30; 
    Unit::draw(Renderer); 
}

