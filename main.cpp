#include "game.hpp"



int main(int argc, char *argv[])
{
    Game game;
    srand(time(NULL));
    if( !game.init() ){
		printf( "Failed to initialize!\n" );
        return 0;
	}
		//Load media
    if( !game.loadMedia())
    {
        printf( "Failed to load media!\n" );
        return 0;
    }

    if (game.show_menu()) {
  
        game.run1(); // run1 
        if (game.getWin())
        {
            cout << "You have won Level 1" << endl; // Level 1 
            game.reset(); 
            game.run2(); // run 2 
            if (game.getWin())
            {
                cout << "You have won level 2" << endl;  // Level 2 
                game.run3(); 
                    if (game.gamewin())
                    {
                        cout << "You have won the game " << endl; // Level 3
                        return 0; 
                        game.close();  
                    }
            }
            else
            {
                game.close(); 
                cout << "You have lost the game " << endl; // Level 2 
                return 0; 
            }
        } 
        else
        {
            game.close(); 
            cout << "You lost " << endl; // Level 1 
        }  
        game.close();
    }
    return 0;
}