#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "gamefile.h"
#include "gameMenu.h"
#include "gamePlay.h"

using namespace std;

string stringscore;
int score, level, life;
double gameSpeed;
//Position of all sprites
double RacerX, RacerY;
double Obs1X, Obs1Y;
double Obs2X, Obs2Y;
double Obs3X, Obs3Y;
double Obs4X, Obs4Y;
double BackgroundY1, BackgroundY2;

void setNewGame(){
    //Setting position
	RacerX=SCREEN_WIDTH/2;
	RacerY=SCREEN_HEIGHT-racerHeight;
	Obs1X=getRandomNumber(borderLeft,borderRight);
	Obs2X=getRandomNumber(borderLeft,borderRight);
	Obs3X=getRandomNumber(borderLeft,borderRight);
	Obs4X=getRandomNumber(borderLeft,borderRight);
    Obs1Y=0,Obs2Y=-100,Obs3Y=-200;Obs4Y=-300;
    BackgroundY1=0;
    BackgroundY2=-600;
    stringscore="";
    score=0;
    level=1;
    gameSpeed=0.3;
    life = 3;
}//end of function

void setLoadGame(){
    //Setting position
    double (&a)[N]=load();
	RacerX=a[0];
	RacerY=a[1];
	Obs1X=a[2];
	Obs1Y=a[3];
	Obs2X=a[4];
	Obs2Y=a[5];
    Obs3X=a[6];
    Obs3Y=a[7];
    Obs4X=a[8];
    Obs4Y=a[9];
    score=(int)a[10];
    level=(int)a[11];
    gameSpeed=a[12];
    life=(int)a[13];
    BackgroundY1=0;
    BackgroundY2=-600;
    stringscore="";
}//end of function

int startGame(sf::RenderWindow &app)
{
    //For game music
    sf::SoundBuffer gameSoundBuffer, carSmash;
    sf::Sound GameSound, smash;
    gameSoundBuffer.loadFromFile("sound/Cymbal_Groove.wav");
    GameSound.setBuffer(gameSoundBuffer);
    carSmash.loadFromFile("sound/crash.wav");
    smash.setBuffer(carSmash);
    //Initialize font
    sf::Font myfont;
    myfont.loadFromFile("font/xirod.ttf");
    //For Textures and Sprites
    sf::Texture background, racer, obs1, obs2, obs3 ,obs4;
    sf::Sprite Background, Background1, Racer, Obs1, Obs2, Obs3, Obs4;
    //Load all images
    if (!background.loadFromFile("cars/background.png")) return EXIT_FAILURE;
    if (!racer.loadFromFile("cars/racer.png")) return EXIT_FAILURE;
    if (!obs1.loadFromFile("cars/obs1.png")) return EXIT_FAILURE;
    if (!obs2.loadFromFile("cars/obs2.png")) return EXIT_FAILURE;
    if (!obs3.loadFromFile("cars/obs3.png")) return EXIT_FAILURE;
    if (!obs4.loadFromFile("cars/obs4.png")) return EXIT_FAILURE;
    //Create sprite
    Background.setTexture(background);
    Background1.setTexture(background);
    Racer.setTexture(racer);
    Obs1.setTexture(obs1);
    Obs2.setTexture(obs2);
    Obs3.setTexture(obs3);
    Obs4.setTexture(obs4);
    Racer.setColor(sf::Color(150,100,50));

    GameSound.play();
    GameSound.setLoop(true);
    //GAME LOOP
    while (app.isOpen())
    {
        //Initialize and count score and level
        stringscore="SCORE:"+to_string(score);
        sf::Text text1(stringscore, myfont, 15);
        text1.setPosition(5,0);

        stringscore="LEVEL:"+to_string(level);
        sf::Text text2(stringscore, myfont, 15);
        text2.setPosition(5,15);

        stringscore="LIFE:"+to_string(life);
        sf::Text text3(stringscore, myfont, 15);
        text3.setPosition(5,30);
        if(life==3) text3.setFillColor(sf::Color::Green);
        else if(life==2) text3.setFillColor(sf::Color::Yellow);
        else if(life==1) text3.setFillColor(sf::Color::Red);

        stringscore="Press S to save";
        sf::Text text4(stringscore, myfont, 15);
        text4.setPosition(570,0);

        stringscore="Press ESC to exit";
        sf::Text text5(stringscore, myfont, 15);
        text5.setPosition(570,15);
        //Set car position
        Racer.setPosition(RacerX,RacerY);
        Obs1.setPosition(Obs1X,Obs1Y);
        Obs2.setPosition(Obs2X,Obs2Y);
        Obs3.setPosition(Obs3X,Obs3Y);
        Obs4.setPosition(Obs4X,Obs4Y);
        //Create scrolling background
        Background.setPosition(0,BackgroundY1);
        Background1.setPosition(0,BackgroundY2);
        if (BackgroundY2>0)
        {
            BackgroundY1=0;
            BackgroundY2=BackgroundY1-500;
        }
        BackgroundY1+=0.1;
        BackgroundY2+=0.1;

        //Set Obs LOOP
        if (Obs1Y>SCREEN_HEIGHT){
             Obs1Y=0;
             Obs1X=getRandomNumber(borderLeft,borderRight);
             score++;
            }
        else
            {Obs1Y=Obs1Y+gameSpeed;}
        if (Obs2Y>SCREEN_HEIGHT){
             Obs2Y=0;
             Obs2X=getRandomNumber(borderLeft,borderRight);
             score++;
            }
        else
            {Obs2Y=Obs2Y+gameSpeed;}
        if (Obs3Y>SCREEN_HEIGHT){
             Obs3Y=0;
             Obs3X=getRandomNumber(borderLeft,borderRight);
             score++;
            }
        else
            {Obs3Y=Obs3Y+gameSpeed;}
        if (Obs4Y>SCREEN_HEIGHT){
             Obs4Y=0;
             Obs4X=getRandomNumber(borderLeft,borderRight);
             score++;
            }
        else
            {Obs4Y=Obs4Y+gameSpeed;}

        //Game level
        if(score>10 && score<20)
            {gameSpeed=0.4; level=2;}
        else if(score>20 && score<32)
            {gameSpeed=0.5; level=3;}
        else if(score>32 && score<44)
            {gameSpeed=0.6; level=4;}
        else if(score>44 && score<58)
            {gameSpeed=0.7; level=5;}
        else if(score>58 && score<75)
            {gameSpeed=0.8; level=6;}
        else if(score>99)
            {
                GameSound.stop();
                gameOver(app,"YOU WIN");
                return 0;
            }
        //Create event to handle input from keyboard
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
            else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Left)
                        {if(RacerX>borderLeft) RacerX=RacerX-10;}
                    else if (event.key.code == sf::Keyboard::Right)
                        {if(RacerX<borderRight) RacerX=RacerX+10;}
                    else if (event.key.code == sf::Keyboard::Up)
                        {if(RacerY>0)RacerY=RacerY-10;}
                    else if (event.key.code == sf::Keyboard::Down)
                        {if(RacerY<SCREEN_HEIGHT-racerHeight)RacerY=RacerY+10;}
                    else if (event.key.code == sf::Keyboard::S)
                        {
                         double z[]={RacerX,RacerY,Obs1X,Obs1Y,Obs2X,Obs2Y,Obs3X,Obs3Y,Obs4X,Obs4Y,(double)score,(double)level,gameSpeed,(double)life};
                         save(z);
                         GameSound.stop();
                         return 0; //returning to main for game menu
                        }
                    else if (event.key.code == sf::Keyboard::Escape)
                        app.close();
                }
        }//end of while
        //Check if accident happen
        if (  ((RacerX>=Obs1X-acc && RacerX<=Obs1X+acc)&&(RacerY>=Obs1Y-acc && RacerY<=Obs1Y+acc))
            ||((RacerX>=Obs2X-acc && RacerX<=Obs2X+acc)&&(RacerY>=Obs2Y-acc && RacerY<=Obs2Y+acc))
            ||((RacerX>=Obs3X-acc && RacerX<=Obs3X+acc)&&(RacerY>=Obs3Y-acc && RacerY<=Obs3Y+acc))
            ||((RacerX>=Obs4X-acc && RacerX<=Obs4X+acc)&&(RacerY>=Obs4Y-acc && RacerY<=Obs4Y+acc)) )
            {   //re-setting player position
                RacerX=SCREEN_WIDTH/2;
                RacerY=SCREEN_HEIGHT-racerHeight;
                life--;
                smash.play();
                if(life<=0)
                {
                    GameSound.stop();
                    gameOver(app,"YOU LOSE");
                    return 0;
                }
            } //end of if
        //Clear and draw position
        app.clear();
        app.draw(Background);
        app.draw(Background1);
        app.draw(Racer);
        app.draw(Obs1);
        app.draw(Obs2);
        app.draw(Obs3);
        app.draw(Obs4);
        app.draw(text1);
        app.draw(text2);
        app.draw(text3);
        app.draw(text4);
        app.draw(text5);
        app.display();
    }//end of game loop
    return EXIT_SUCCESS;
}//end of function
//Game over
int gameOver(sf::RenderWindow &app,string str)
{
    sf::Texture gameover;
    if (!gameover.loadFromFile("cars/over.png")) return EXIT_FAILURE;
    sf::Sprite Gameover(gameover);

    sf::Font myfont;
    myfont.loadFromFile("font/xirod.ttf");

    sf::SoundBuffer gameOver;
    gameOver.loadFromFile("sound/crash.wav");
    sf::Sound GameOver;
    GameOver.setBuffer(gameOver);
    GameOver.play();
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyReleased && event.key.code==sf::Keyboard::Escape))
                {remove("game_save.txt");return 0;}
        }//end of while
        stringscore="YOUR SCORE:"+to_string(score);
        sf::Text text1(stringscore, myfont, 25);
        text1.setPosition(210,450);

        stringscore=str;
        sf::Text text2(stringscore, myfont, 25);
        text2.setPosition(300,150);
        // Clear and draw
        app.clear();
        app.draw(Gameover);
        app.draw(text1);
        app.draw(text2);
        app.display();
    }//end of file
    if(remove("game_save.txt")==0)
        cout<<"Save file deleted!"<<endl;;
    return 0;
}//end of function
//To generate random numbers
int getRandomNumber(int a, int b)
{
        static bool first = true;
        if (first){
            srand( time(NULL) );
            first = false;
        }
        int result=a + rand() % (( b + 1 ) - a);
        result=(result/10)*10;
        return result;
}//end of function
