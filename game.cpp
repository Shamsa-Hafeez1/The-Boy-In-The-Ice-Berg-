#include "game.hpp"

Game::Game() { }     

Game::~Game() {          
    for (auto f: guards) {
	   delete f;
	   f = NULL; 
    }
	guards.clear(); 
    for (auto f: fire_list) {
	   delete f; 
	   f = NULL; 
    }
    fire_list.clear(); 
    for (auto p:powers) {
	   delete p; 
	   p = NULL; 
    }
    powers.clear(); 
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "The Boy in the Iceberg", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()

{
	//Loading success flag
	bool success = true;
	zuko_health = loadTexture("blue_circle.png"); 
	zuko = loadTexture("zuko.png"); 
	earthbend_asset = loadTexture("earthbend_asset.png");
	waterbend_asset = loadTexture("waterbend_asset.png");
	firebend_asset = loadTexture("firebend_asset.png");
	airbend_asset = loadTexture("air.png");
	level2_aang = loadTexture("level2_aang.png"); 
	level3_aang = loadTexture("level3_aang.png"); 
	fire_asset = loadTexture("fire.png"); 
	guard_asset = loadTexture("firenationguards.png"); // Refernce : https://www.reddit.com/r/TheLastAirbender/comments/21zr2d/hey_guys_i_really_want_to_dress_as_a_fire_nation/
	assets = loadTexture("aang.png");
    gTexture = loadTexture("background.png");
	health_asset = loadTexture("health.png"); // from HW 2 
	if(assets==NULL || gTexture==NULL || guard_asset ==  NULL  || health_asset == NULL || airbend_asset == NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }

	bgMusic = Mix_LoadMUS( "avatar.mp3" );
	collisionSound = Mix_LoadMUS("collision.mp3"); 
	if(bgMusic == NULL || collisionSound == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets=NULL;
	SDL_DestroyTexture(gTexture);
	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	Mix_FreeMusic(bgMusic);
	Mix_FreeMusic(collisionSound);
	collisionSound = NULL; 
	bgMusic = NULL;
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

/** makeEnemy generates enemies at a probability of 10%
 * 
 */

void Game::makeEnemy() {
	int temp = rand() % 100; 
	if (temp < 2 ) {
		guards.push_back(new FireNationGuards(guard_asset));
	}
}

/** Erases FireNationGuards if they are dead 
 * or else adds a Fire in the list of Fire 
 */
void Game::updateEnemy() {
	auto iterator = guards.begin(); 
	while (iterator != guards.end()) 
	{
		if (!((*iterator) -> isAlive())) 
		{ 
			delete (*iterator); 
			(*iterator) = NULL; 
			iterator = guards.erase(iterator); 
		}
		else 
		{
			(*iterator) -> move(gRenderer); 
			if ((*iterator) -> attack()) 
			{
				fire_list.push_back(new Fire(fire_asset, ((*iterator) -> getMover()))) ; 
				iterator ++ ; 
			}
		}
	}
	
}

/** Updates the score of player if he collides with Fire 
 * i.e. Decrease score of player by 1 upon collision with fire 
 * 
 */
void Game::updateScoring(Aang &player) { // For level 2 
	for (auto f: fire_list) 
	{
		if (FireCollidesPlayer( (f -> getMover()), (player.getMover()))) {
			player.decreaseLife(); 
		} 	
	}
	return; 
}

/** Updates score in level 3 
 * Aangs health decrease upon collision with fire 
 * Zuko life decreases upon collision with Aang's attack 
 * 
 */
void Game::updateScoring(Aang &player, PrinceZuko &zuko) 
{ 
	for (auto f: fire_list) 
	{
		if (FireCollidesPlayer( (f -> getMover()), (player.getMover())))
		{
			player.decreaseLife(); 
		} 	
	}
		for (auto p: powers)
		{
		
		if (FireCollidesPlayer( (p -> getMover()), (zuko.getMover())))
			{
				cout << "Zuko life decrease " << endl; 
				zuko.decreaseLife(); 
			} 	
		}
	return; 
}

/** Finds if Aang's attack has collided with prince Zuko's attack 
 * 
 */
void Game::attackCollidesAttack() {
	auto iterator = powers.begin(); 
	while (iterator != powers.end()) { 

		auto it = fire_list.begin(); 

		bool flag = false; 
		while (it != fire_list.end()) {
			if (FireCollidesPlayer((*it) -> getMover() , ((*iterator) -> getMover()))) 
			{
				flag = true; 
				delete (*iterator); 
				(*iterator) = NULL; 
				iterator = powers.erase(iterator); 

				delete (*it); 
				(*it) = NULL; 
				it = fire_list.erase(it); 		
				break; 
			}
			else {
				it ++; 
			}	
		}
		if (!flag )
		iterator++; 
	}

}


/**Draws the objects Guards and Fire 
 */

void Game::drawAllObjects()
{  			
	for (auto guard: guards) {
		guard -> draw(gRenderer); 
	}
	for (auto f: fire_list) 
		f -> draw(gRenderer); 
}

/** If Fire collides with player then play the music 
 * and returns true 
 * 
 */
bool Game::FireCollidesPlayer(SDL_Rect fire, SDL_Rect player)
{
	if (SDL_HasIntersection(&fire,&player))
	{
		if( Mix_PlayingMusic() == NULL )
		{
			Mix_PlayMusic( collisionSound, 2 ); // Play the music 
			Mix_VolumeMusic(10); 
		}
		return true;
	}
}

/** Run function for level 1 of the game
 * 
 */ 


void Game::run1( )
{
    SDL_RenderClear( gRenderer );
	//Main loop flag
	bool quit = false;

	Aang player(assets); 
	//Event handler
	SDL_Event e;

	//While application is running
	while( !quit )
	{
		bool down = false; 
		bool up = false; 
		bool left = false; 
		bool right = false;

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) // First find out whcih key is pressed / Mouse used 
		{
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			else if( e.type == SDL_KEYDOWN ) 
			{
				SDL_Keycode key = e.key.keysym.sym;
						if (key == SDLK_DOWN) {

							down = true; 
						}
						if (key == SDLK_UP) {
							up = true; 
						}
						if (key == SDLK_LEFT) {
							right = true; 
						}
						if (key == SDLK_RIGHT) {
							left = true; 
						}
						if (key == SDLK_SPACE) {   
							pause = true; 
						}
			}
			else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) 
			{
				int xMouse, yMouse; 
				SDL_GetMouseState(&xMouse,&yMouse);
				if (xMouse >= 30 and xMouse <= 370 and yMouse >=40 and yMouse <= 520) {
					pause=false;
				}
				else if (xMouse >= 400 and xMouse <= 770 and yMouse >= 38 and yMouse <= 520) 
					quit=true; 
			}
		}
		if (!pause)
		{
			SDL_RenderClear(gRenderer); //removes everything from renderer
			SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
			updateEnemy();  // Update all the previous enemies and make new enemies 
			makeEnemy(); 
			updateScoring(player); 
			drawAllObjects();//draws all objects
			player.draw(up, down, left, right, gRenderer); // Draw player and its health 
			player.draw_health(health_asset, gRenderer); 

			if (!(player.isAlive()))  // If the player is not alive then game is lost 
			{
				cout << "You loose " << endl; 
				level_over = true; 
				win = false; 
				return;  
			}

			if (player.getMover().x >=700  and player.getMover().y >= 475) // If reach destination, level over. 
			{
				level_over = true; 
				if (player.isAlive()) 
					win = true; 		
				else 
					win = false; 
				return ; 
			}	
			SDL_RenderPresent(gRenderer); //displays the updated renderer
			SDL_Delay(100);	//causes sdl engine to delay for specified miliseconds
	
		}
		else {
			SDL_RenderCopy(gRenderer, loadTexture("resume.png"), NULL, NULL);
			SDL_RenderPresent(gRenderer); //displays the updated renderer
			SDL_Delay(200);
		}
	}			
}

bool Game::gamewin()
{	
	if (win)
	{
		SDL_RenderCopy(gRenderer, loadTexture("gamewin.png"), NULL, NULL);
		SDL_RenderPresent(gRenderer); //displays the updated renderer
		SDL_Delay(800);
	}
}


/** Returns is the game is won or not 
 * 
 */
bool Game::getWin() 
{
	if (win)
	SDL_RenderCopy(gRenderer, loadTexture("level_passed.png"), NULL, NULL);
	else 
	SDL_RenderCopy(gRenderer, loadTexture("game_over.jpg"), NULL, NULL); 
	SDL_RenderPresent(gRenderer); //displays the updated renderer
	SDL_Delay(800);
	return win; 
}

/** Returns if the game is over or not 
 */
bool Game::Over() 
{
	return level_over; 
}

/** Run function for level 2 
 * 
 */

void Game::run2() // Run for level 2 
{
	level = 2; 
    SDL_RenderClear( gRenderer );
	//Main loop flag
	bool quit = false;

	Aang player(level2_aang); 
	//Event handler
	SDL_Event e;
		bool air = false; 
		bool water = false; 
		bool fire = false; 
		bool earth = false; 
		
	//While application is running
	while( !quit )
	{
		bool down = false; 
		bool up = false; 
		bool left = false; 
		bool right = false;
		// power to use 
		
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) // Find ot which key is pressed 
		{
		
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			else if( e.type == SDL_KEYDOWN)
			{
	
				SDL_Keycode key = e.key.keysym.sym;
						if (key == SDLK_DOWN) { 

							down = true; 
						}
						if (key == SDLK_UP) {
							up = true; 
						}
						if (key == SDLK_LEFT) {
							right = true; 
						}
						if (key == SDLK_RIGHT) {
							left = true; 
						}
						if (key == SDLK_SPACE) {
							pause = true; 
						}
						if (key == SDLK_a) {
							air = true; 
							water = false; 
							fire = false; 
							earth = false; 
							
						}
						if (key == SDLK_w) {
							water = true; 
							air = false; 
							fire = false; 
							earth = false; 
						}
						if (key == SDLK_f) {
							fire = true; 
							air = false; 
							earth = false; 
							water = false; 
						}
						if (key == SDLK_e) {
							earth = true; 
							air = false; 
							water = false; 
							fire = false; 
						}
						else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) 
						{
							int xMouse, yMouse; 
							SDL_GetMouseState(&xMouse,&yMouse);
							if (xMouse >= 60 and xMouse <= 840 and yMouse >=40 and yMouse <= 460) {
								pause=false;
							}
							else if (xMouse >= 950 and xMouse <= 1860 and yMouse >= 38 and yMouse <= 460) 
								quit=true;  
						}
			}
		}
		
		if (!pause){
			SDL_RenderClear(gRenderer); //removes everything from renderer
			SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
			updateEnemy(); 
			makeEnemy(); 
			updateScoring(player); 
			drawAllObjects();//draws all objects
			playerAttacks(player,earth, fire, water, air);  
			attackPersists(); 
			attackCollidesAttack(); 
			player.draw(up, down, left, right, gRenderer); 
			player.draw_health(health_asset, gRenderer); 

			if (!(player.isAlive())) {
				level_over = false; 
				win = false; 
				return;  // for the run function to end 
			}

			if (player.getMover().x >=700  and player.getMover().y >= 475) 
			{
				level_over = true; 
				if (player.isAlive()) 
				{
					win = true;  	
				}	
				else 
					win = false; // win is default false; so this is not needed 
				return ; // for the run function to end 
			}	
			
			SDL_RenderPresent(gRenderer); //displays the updated renderer
			SDL_Delay(100);	//causes sdl engine to delay for specified miliseconds
		} 
		else 
		{
			SDL_RenderCopy(gRenderer, loadTexture("resume.png"), NULL, NULL);
			SDL_RenderPresent(gRenderer); //displays the updated renderer
			SDL_Delay(200);
		}
		
	}		
}

/**  Player uses elemental powers in level 2 
 * 
 */
void Game::playerAttacks(Aang &player, bool& earth, bool& fire, bool& water, bool& air) {
	
	if (earth or fire or water or air) {
		if (air)
			powers.push_back(new Airbending(airbend_asset, player.getMover())); 
		if (fire)
			powers.push_back(new Firebending(firebend_asset, (player.getMover()))); 
		if (water)
			powers.push_back(new Waterbending(waterbend_asset, (player.getMover()))); 
		if (earth)
			powers.push_back(new Earthbending(earthbend_asset, (player.getMover())));
		air = false;
		water = false; 
		fire = false; 
		earth = false; 
	}
}

/** Resets the game 
 * 
 */
void Game::reset() {
    level_over = false; 
    win = false; 
}

/**  move the attack forward and check its collision . ALso delete attacks that go out of screen 
 * 
 */
void Game::attackPersists()
{ 
	for (auto i: powers) {
		i -> show(gRenderer); 
	}
	auto iterator = powers.begin(); 
	while (iterator != powers.end())
	{ 							// delete when it goes out of screen 
		if (((*iterator) -> getMover()).x >= 800 or ((*iterator) -> getMover()).y >= 600 or ((*iterator) -> getMover()).x <= 0 or ((*iterator) -> getMover()).y <= 0)
		{
			delete (*iterator); 
			(*iterator) = NULL; 
			iterator = powers.erase(iterator); 
		}
		else {
			iterator ++ ; 
		}
	}
}

/** Plays music 
 */
void Game::playMusic() {
	if( Mix_PlayingMusic() == 0 )
	{			
		Mix_PlayMusic( bgMusic, 2 ); // Play music 
		Mix_VolumeMusic(2); 
	}
	
}

/** Shows menu page of game and takes input for next page
 */
bool Game::show_menu() {
	SDL_RenderClear( gRenderer );
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	int choice = menu; 
	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
				int xMouse, yMouse; 
				SDL_GetMouseState(&xMouse,&yMouse);
				// back button 
				if ((choice == instructions or choice == credits) and (xMouse >= 21 and xMouse <= 76 and yMouse >= 42 and yMouse <= 61)) 
					choice = menu; 

				else if (xMouse >= 526 and xMouse <= 758 and yMouse >=32 and yMouse <= 263) 
					return true; 

				else if (xMouse >= 44 and xMouse <= 264 and yMouse >= 38 and yMouse <= 263) 
					choice = instructions; 

				else if (xMouse >= 65 and xMouse <= 285 and yMouse >= 312 and yMouse <= 553) 
					choice = credits; 

				else if (xMouse >= 537 and xMouse <= 767 and yMouse >= 322 and yMouse <= 554) 
					return false; 
			}
		}

		SDL_RenderClear(gRenderer); //removes everything from renderer
		playMusic(); 
		if (choice == instructions) // Better to use enum 
			SDL_RenderCopy(gRenderer, loadTexture("instructions.png"), NULL, NULL);
		else if (choice == credits)
			SDL_RenderCopy(gRenderer, loadTexture("credits.png"), NULL, NULL);
		else 
			SDL_RenderCopy(gRenderer, loadTexture("menu.png"), NULL, NULL);//Draws background to renderer

		SDL_RenderPresent(gRenderer); //displays the updated renderer
		SDL_Delay(100);	//causes sdl engine to delay for specified miliseconds
	}
}

/** Run function for level 3 
 */
void Game::run3() // Run for level 3 
{
	level = 3; 
    SDL_RenderClear( gRenderer );
	//Main loop flag
	bool quit = false;

	Aang player(level3_aang); 
	PrinceZuko prince_zuko(zuko); 

	
	//Event handler
	SDL_Event e;
		bool air = false; 
		bool water = false; 
		bool fire = false; 
		bool earth = false; 
		
	//While application is running
	while( !quit )
	{
		 
		bool down = false; 
		bool up = false; 
		bool left = false; 
		bool right = false;
		// power to use 
		
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			else if( e.type == SDL_KEYDOWN){
	
				SDL_Keycode key = e.key.keysym.sym;
						if (key == SDLK_DOWN) {  
							down = true; 
						}
						if (key == SDLK_UP) {
							up = true; 
						}
						if (key == SDLK_LEFT) {
							right = true; 
						}
						if (key == SDLK_RIGHT) {
							left = true; 
						}
						if (key == SDLK_SPACE) {
							pause = true; 
						}
						if (key == SDLK_a) {
							air = true; 
							water = false; 
							fire = false; 
							earth = false; 	
						}
						if (key == SDLK_w) {
							water = true; 
							air = false; 
							fire = false; 
							earth = false; 
						}
						if (key == SDLK_f) {
							fire = true; 
							air = false; 
							earth = false; 
							water = false; 
						}
						if (key == SDLK_e) {
							earth = true; 
							air = false; 
							water = false; 
							fire = false; 
						}
						else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) 
						{
							int xMouse, yMouse; 

							SDL_GetMouseState(&xMouse,&yMouse);
							if (xMouse >= 60 and xMouse <= 840 and yMouse >=40 and yMouse <= 460) {
								pause=false;
							}
							else if (xMouse >= 950 and xMouse <= 1860 and yMouse >= 38 and yMouse <= 460) 
								quit=true;  
						}
						
			}
		}
		
		if (!pause)
		{
			SDL_RenderClear(gRenderer); //removes everything from renderer
			SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
			updateEnemy(); 
			makeEnemy(); 
			updateScoring(player, prince_zuko); 
			drawAllObjects();		 //draws all objects
			playerAttacks(player,earth, fire, water, air);  
			attackPersists(); 
			attackCollidesAttack();  
			prince_zuko.draw(gRenderer); // Draws prince Zuko and his health poinst 
			prince_zuko.draw_health(zuko_health, gRenderer); 
			player.draw(up, down, left, right, gRenderer); // Draws Aang and his health poinst
			player.draw_health(health_asset, gRenderer); 

			writeState(player, prince_zuko); 

			if (!(player.isAlive()) or !(prince_zuko.isAlive())) {
				if (!player.isAlive()) {
					cout << "you lost game " << endl; 
					win = false; 
				}	
				else {
					cout << "you won game " << endl; 
					win = true; 
				}
					
				level_over = true; 

				return;  				// for the run function to end 
			}

			if (player.getMover().x >=700  and player.getMover().y >= 475) {
				level_over = false; 
				if (player.isAlive()) 
					win = true; 		
				else 
					win = false; 	// win is default false; so this is not needed 
				return; 			// for the run function to end 
			}	

			if (prince_zuko.attack()) { // when zuko attacks : create a new fire object in array of fire 
				fire_list.push_back(new Fire(fire_asset, (prince_zuko.getMover()))); 
			}
			SDL_RenderPresent(gRenderer); //displays the updated renderer
			SDL_Delay(100);					//causes sdl engine to delay for specified miliseconds
		}
		else {
			SDL_RenderCopy(gRenderer, loadTexture("resume.png"), NULL, NULL);
			SDL_RenderPresent(gRenderer); //displays the updated renderer
			SDL_Delay(200);
		}
		
	}		
}

/** stores all the relevent information in txt file of game state 
 * to be able to resume the game 
 * 
 */
void Game::writeState(Aang& aang, PrinceZuko& prince_zuko) {
	ofstream myfile("gameState.txt"); 
	if (myfile.is_open()) {
		myfile << level << "\n" ; 
		myfile << aang;  
		myfile << prince_zuko; 
	}
	myfile.close(); 
}

/** reads all the contents of readState.txt file 
 * 
 */
void Game::readState() {

    string line; 
	SDL_Rect aang_mover = {0, 0, 70, 70}; 
	SDL_Rect zuko_mover = {500, 0, 180, 180}; 
	int aanghealth = 0; 
	int zukohealth = 0;  

    ifstream myfile("gameState.txt"); 
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			level = stoi(line); // first line gives level 

			getline(myfile, line); 
			(aang_mover.x) = stoi(line); // Aang mover x  

			getline(myfile, line); 
			(aang_mover.y) = stoi(line); // Aang mover y 

			getline(myfile, line);
			aanghealth = stoi(line); // Aang Health 

			getline(myfile, line); 
			(zuko_mover.x) = stoi(line); // Zuko mover x  

			getline(myfile, line); 
			(zuko_mover.y) = stoi(line); // Zuko mover y 

			getline(myfile, line);
			zukohealth = stoi(line); // Zuko Health 


		}
	
	}
	myfile.close(); 

}