#include "FireNationGuards.hpp"

FireNationGuards::~FireNationGuards() {}

FireNationGuards::FireNationGuards(SDL_Texture* asset): Unit(asset)
{ 
    src = {0, 0, 600, 600}; 
    mover = {750, rand() % 620, 50, 60}; 
}

void FireNationGuards::draw(SDL_Renderer* Renderer)
{
    SDL_RenderCopy(Renderer, assets, &src, &mover);
    Unit::draw(Renderer);
}

void FireNationGuards::move(SDL_Renderer* Renderer)
{	
	if (mover.y < 620)
	{
		mover.y ++;
	}
	else
	{
		mover.y;
	} 
}

bool FireNationGuards::attack()
{
    int temp = rand() % 100;   // generates a random number between 0 and 99 
	if (temp < 50)	  		   // Attacks with a probabllty of 20 % 
	{
		NoOfAttacks ++;
		return true; 
	} 
	return false; 
}

bool FireNationGuards::isAlive()
{
    if (NoOfAttacks == 3)   // Enemy can attack only 10 times  
		return false; 
	return true; 
}
