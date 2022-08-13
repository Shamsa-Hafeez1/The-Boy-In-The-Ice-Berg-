#include "aanghealth.hpp"

using namespace std; 

/** draw function will draw the health points (making a health bar) at the top right corner (red in colour) 
 * Each time it is being called, it loops over health_points 
 * and calculates the its x and y coordinates which then displays 
 * on screen via draw function of Health (its parent class)
 */ 

void aangHealth::draw(SDL_Texture* assets, SDL_Renderer* Renderer)
{ 
    for (int i = 0; i < health_points; i++) {
        mover = {650 + i * 12, 10, 10, 10};	
        src = {175, 461, 102, 90};	
        Health::draw(assets, Renderer); 		
    }
}

/** operator << is overloaded as it is being used to store the health_points 
 * of our player in Gamesate.txt file 
 */ 
ofstream& operator<<(ofstream& out, aangHealth& aangHealth)
{ 
    out << (aangHealth.health_points); 
    return out; 
}