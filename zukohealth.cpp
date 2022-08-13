#include  "zukohealth.hpp"
 
/** draw function will draw the health points (making a health bar) at the top right corner ( blue in colour )
 * Each time it is being called, it loops over health_points 
 * and calculates the its x and y coordinates which then displays 
 * on screen via draw function of Health (its parent class)
 */ 

void zukoHealth::draw(SDL_Texture* assets, SDL_Renderer* Renderer)
{ 
    for(int i = 0 ; i < health_points; i++) {
		mover = {650+i*12, 30, 10, 10};	
		src = {0, 0, 200, 200}; 
        Health::draw(assets, Renderer); 		
    }
}

/** operator << is overloaded as it is being used to store the health_points 
 * of our player in gameSate.txt file 
 */ 
ofstream& operator<<(ofstream& out, zukoHealth& zukoHealth)
{
    out << (zukoHealth.health_points) << "\n"; 
    return out; 
}