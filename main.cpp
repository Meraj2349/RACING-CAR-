#include <iostream>
#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf; 

//Init game const
const double SCREEN_WIDTH = 800;
const double SCREEN_HEIGH = 600;
const int borderLeft = 30;
const int borderRight = 730;
const int racerWidth = 40;
const int racerHeight = 70;
string stringscore = "";
int score = 0;
double gameSpeed = 0.3;


//Create Main Windows
RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "Car Racing");

int getRandomNumber(int a, int b)
{
	static bool first = true; if (first) { srand(time(NULL)); first = false; }
	int result = a + rand() % ((b + 1) - a);
	result = (result / 10) * 10;
	return result;
}


int gameOver()
{
	Texture gameover, troll;
	if (!gameover.loadFromFile("over.png")) { cout << "over\n"; }
	
	Sprite Gameover(gameover);
	
	
	//sound 
	SoundBuffer gameOver;
	gameOver.loadFromFile("crash.wav");
	Sound GameOver;
	GameOver.setBuffer(gameOver);

	GameOver.play();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		Font myfont;
		myfont.loadFromFile("xirod.ttf");
		stringscore = "YOUR SCORE:" + to_string(score);
		Text text(stringscore, myfont, 30);
		text.setPosition(210, 450);


		window.clear();
		window.draw(Gameover);
		window.draw(text);
		window.display();
	}
	return 0;
}


int main()
{
	//window size
	//sf::RenderWindow window(sf::VideoMode(800, 600), "CAR GAME");


	//Init game music
	SoundBuffer gameSoundBuffer;
	gameSoundBuffer.loadFromFile("game.wav");
	Sound GameSound;
	GameSound.setBuffer(gameSoundBuffer);


	//image lode 
	sf::Texture background, racer, obs1, obs2, obs3, obs4, gameover;

	// font
	Font myfont;
	myfont.loadFromFile("xirod.ttf");

	//lode into code ->image 
	//background image file lode 
	if (!background.loadFromFile("background.png"))
	{
		cout << "background loding error!";
	}
	//main car file 
	if (!racer.loadFromFile("racer.png")) 
	{
		cout << "racer loding error!";
	}

	// random car file
	if (!obs1.loadFromFile("obs1.png"))   
	{
		cout << "obs1 loding error!";
	}
	if (!obs2.loadFromFile("obs2.png"))   
	{
		cout << "obs2 loding error!";
	}
	
	
	sf::Sprite Background(background), Background1(background), Racer(racer), Obs1(obs1), Obs2(obs2);
	double RacerX, RacerY, Obs1X, Obs1Y, Obs2X, Obs2Y;

	//Set racer and Obs pos

	RacerX = SCREEN_WIDTH / 2;
	RacerY = SCREEN_HEIGH - racerHeight;

	Obs1X = getRandomNumber(borderLeft, borderRight);
	Obs2X = getRandomNumber(borderLeft, borderRight);
	

	Obs1Y = 0,
	Obs2Y = -100;    // Obs3Y = -200, Obs4Y = -300;

	double BackgroundY1 = 0;
	double BackgroundY2 = -600;

	GameSound.play();
	GameSound.setLoop(true);

	//Racer.setPosition(sf::Vector2f(395, 520));
	
	//loop for game 

	while (window.isOpen())
	{

		//Init and count score
		stringscore = "SCORE:" + to_string(score);
		Text text(stringscore, myfont, 15);
		text.setPosition(5, 0);

		//Set car position
		Racer.setPosition(RacerX, RacerY);
		Obs1.setPosition(Obs1X, Obs1Y);
		Obs2.setPosition(Obs2X, Obs2Y);
		



		//Creat scrolling background movement 
		Background.setPosition(0, BackgroundY1);
		Background1.setPosition(0, BackgroundY2);
		if (BackgroundY2 > 0)
		{
			BackgroundY1 = 0;
			BackgroundY2 = BackgroundY1 - 500;
		}
		BackgroundY1 += 0.2;
		BackgroundY2 += 0.2;

		//Set Obs LOOP
		if (Obs1Y > SCREEN_HEIGH)
		{
			Obs1Y = 0; Obs1X = getRandomNumber(borderLeft, borderRight); score++;
		}
		else { Obs1Y = Obs1Y + gameSpeed; }
		if (Obs2Y > SCREEN_HEIGH)
		{
			Obs2Y = 0; Obs2X = getRandomNumber(borderLeft, borderRight); score++;
		}
		else { Obs2Y = Obs2Y + gameSpeed; }
	


		//Game level
		if (score > 50 && score < 100) { gameSpeed = 0.4; }
		if (score > 100 && score < 150) { gameSpeed =0.5; }
		if (score > 150&& score < 200) { gameSpeed  =0.6; }



		//Cre;ate event to handle input from keyboard
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					if (RacerX > borderLeft)
					{
						RacerX = RacerX - 30; 
					}
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					if (RacerX < borderRight) 
					{ 
						RacerX = RacerX + 30; 
					}
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					if (RacerY > 0) 
					{
						RacerY = RacerY - 30; 
					}
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					if (RacerY < SCREEN_HEIGH - 70)
					{ 
						RacerY = RacerY + 0;
					}
				}
			}
		}

		//Check if accident happen

		if (((RacerX >= (Obs1X - 30)) && (RacerX <= (Obs1X + 30))) && ((RacerY >= (Obs1Y - 30)) && (RacerY) <= (Obs1Y + 30)))
		{
			GameSound.stop(); gameOver();
		};
		if (((RacerX >= (Obs2X - 30)) && (RacerX <= (Obs2X + 30))) && ((RacerY >= (Obs2Y - 30)) && (RacerY) <= (Obs2Y + 30)))
		{
			GameSound.stop(); gameOver();
		};
		

		


		window.clear();
		window.draw(Background);
		window.draw(Background1);
		window.draw(Racer);
		window.draw(Obs1);
		window.draw(Obs2);
		window.draw(text);
		window.display();

	}
	
}


