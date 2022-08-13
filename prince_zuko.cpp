#include "prince_zuko.hpp"

PrinceZuko::~PrinceZuko() { }

PrinceZuko::PrinceZuko(SDL_Texture* asset): Unit(asset) 
{  
	mover = {500, 0, 180, 180}; 
    src = {0, 0, 1800, 1800};  
}

void PrinceZuko::draw(SDL_Renderer* Renderer)
{
    enum {down, up, left, right}; 
    int temp = 0; 
    do
    {
        temp = rand () % 4; 
    }
    while (((temp == down) and (mover.y + mover.h + 15 > 600)) or ((temp == up) and (mover.y - 15 < 0)) or ((temp == right) and (mover.w + mover.x + 15 > 780)) or ((temp == left) and (mover.x - 15 < 0))); 

    if (temp == down)
        mover.y += 15;
    if (temp == up)
        mover.y -= 15; 
    if (temp ==left)
        mover.x -= 15; 
    if (temp == right)
        mover.x += 15; 
    Unit::draw(Renderer); 
}

void PrinceZuko::draw_health(SDL_Texture* assets, SDL_Renderer* Renderer)
{ 
    health.draw(assets, Renderer); 
}


bool PrinceZuko::attack()
{
    int temp = rand() % 100;   
	if (temp < 30)	  
        return true; 
	return false; 
}

void PrinceZuko::decreaseLife()
{ 
    --health; 
}

bool PrinceZuko::isAlive()
{
    if (health.isFinished()) 
        return false; 
    return true; 
}

ofstream& operator<<(ofstream& out, PrinceZuko& princeZuko)
{ 
    out << (princeZuko.getMover()).x << "\n"; 
    out << (princeZuko.getMover()).y << "\n"; 
    out << (princeZuko.health) << "\n"; 
    return out; 
}