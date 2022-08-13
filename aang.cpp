#include "aang.hpp"

Aang::Aang() {}

Aang::~Aang() {}

Aang::Aang(SDL_Texture* asset): Unit(asset)
{  
	mover = {0, 0, 120, 110}; 
    src = {0, 0, 1200, 1200}; 
}

/** When user gives input via Up, Down, Left, Right keys on keyboard.
 * draw function first increases or decreases the x or y coordinate as per this input. 
 * It then proceeds towads drawing the Aang on its updated position.  
 */

void Aang::draw(bool up, bool down, bool right, bool left, SDL_Renderer* Renderer)
{

    if (down && mover.y <= 515)
        mover.y += 15;
    if (up && mover.y >= 15)
        mover.y -= 15; 
    if (left && mover.x >= 15)
        mover.x -= 15; 
    if (right && mover.x <= 715)
        mover.x += 15; 
    Unit::draw(Renderer); 

}

void Aang::draw_health(SDL_Texture* assets, SDL_Renderer* Renderer)
{ 
    health.draw(assets, Renderer); 
}

/** The function decreaseLife decreases health by 1.
 * Note that since health belongs to class aangHealth, the operator -- is overloaded in the class aangHealth. 
 */ 

void Aang::decreaseLife()
{ 
    --health; 
}

bool Aang::isAlive()
{
    if (health.isFinished()) 
        return false; 
    return true; 
}

/** operator << has been overloaded such that the data regarding Aang's state is stored in the Gamestate.txt file 
 * The first line writes the x coordinate of Aang's position in Gamestate.txt file. 
 * The second line writes the y coordinate of Aang's position in Gamestate.txt file.
 * The third line writes Aang's health points in Gamestate.txt file. Since aangHealth is also a class, the << operator has been overlaoded for that class too. 
 */

ofstream& operator<<(ofstream& out, Aang& aang)
{ 
    out << (aang.getMover()).x << "\n";          
    out << (aang.getMover()).y << "\n";           
    out << (aang.health) << "\n"; 
    return out; 
}