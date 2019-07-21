#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
    // Game constants
    #define SCREEN_WIDTH 800
    #define SCREEN_HEIGHT 600
    #define borderLeft 140
    #define borderRight 660
    #define racerWidth 40
    #define racerHeight 70
    #define acc 30  // for accident detection
    extern std::string stringscore;
    extern int score, level, life;
    extern double gameSpeed;

    //Position of all sprites
    extern double RacerX, RacerY;
    extern double Obs1X, Obs1Y;
    extern double Obs2X, Obs2Y;
    extern double Obs3X, Obs3Y;
    extern double Obs4X, Obs4Y;
    extern double BackgroundY1, BackgroundY2;

    //To Play the game
    extern int startGame(sf::RenderWindow &app);
    // Create gameover screen
    extern int gameOver(sf::RenderWindow &app,std::string str);
    //To set position of sprites
    extern void setNewGame();
    extern void setLoadGame();
    //Create random Number for game loop
    extern int getRandomNumber(int a, int b);

#endif // GAMEPLAY_H_INCLUDED
