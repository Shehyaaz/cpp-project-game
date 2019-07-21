#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "gameMenu.h"
#include "gamePlay.h"
#include "gamefile.h"

using namespace std;

int main()
{
	sf::RenderWindow app(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "CAR WAR!");
    //For game music
	sf::SoundBuffer startSoundBuffer;
	sf::Sound startSound;
	startSoundBuffer.loadFromFile("sound/start.wav");
    startSound.setBuffer(startSoundBuffer);
    //For texture and sprite
    sf::Texture startScreen;
    if (!startScreen.loadFromFile("cars/start-screen.png")) return EXIT_FAILURE;
    sf::Sprite StartScr(startScreen);
	gameMenu menu(app.getSize().x, app.getSize().y);

    startSound.play();
	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			switch (event.type)
			{
			  case sf::Event::KeyReleased :
				switch (event.key.code)
				{
				  case sf::Keyboard::Up :
					menu.MoveUp();
					break;

				  case sf::Keyboard::Down :
					menu.MoveDown();
					break;

				  case sf::Keyboard::Return :
					switch (menu.GetPressedItem())
					{
					 case 0:
                        remove("game_save.txt");
					    setNewGame();
						startGame(app);
						break;
					 case 1:
					     if(checkGameFile())
                            break;
                         else{
						  setLoadGame();
						  startGame(app);
                         }
						break;
					 case 2:
						app.close();
						break;
                     default : break;
					}//end of switch
					break;
                  case sf::Keyboard::Escape :
                        app.close();
                  default : break;
				}//end of switch
				break;
			  case sf::Event::Closed:
				app.close();
				break;
              default : break;
			}//end of switch
		}//end of while
		app.clear();
		app.draw(StartScr);
		menu.draw(app);
		app.display();
	}//end of game loop
	return 0;
}//end of main
//end of program
