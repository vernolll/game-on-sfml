#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;


float offsetX = 0, offsetY = 0;


const int H = 12;
const int W = 40;


String TileMap[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B         0000                BBBB     B",
"B                                B     B",
"BBB                              B     B",
"B              BB                BB    B",
"B              BB                      B",
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};

class PLAYER {

public:

	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;

	PLAYER(Texture& image)
	{
		sprite.setTexture(image);
		rect = FloatRect(320, 240, 60, 60);

		dx = dy = 0.1;
		currentFrame = 0;
	}


	void update(float time)
	{

		rect.left += dx * time;
		Collision(0);

		if (!onGround) dy = dy + 0.0005 * time;
		rect.top += dy * time;
		onGround = false;
		Collision(1);


		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;

		if (dx > 0) sprite.setTextureRect(IntRect(62 * int(currentFrame), 196, 60, 60));
		if (dx < 0) sprite.setTextureRect(IntRect(62 * int(currentFrame), 130, 60, 60));


		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

		dx = 0;
	}



	void Collision(int dir)
	{
		for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
			{
				if (TileMap[i][j] == 'B')
				{
					if ((dx > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
					if ((dx < 0) && (dir == 0)) rect.left = j * 32 + 32;
					if ((dy > 0) && (dir == 1)) { rect.top = i * 32 - rect.height;  dy = 0;   onGround = true; }
					if ((dy < 0) && (dir == 1)) { rect.top = i * 32 + 32;   dy = 0; }
				}

				if (TileMap[i][j] == '0')
				{
					TileMap[i][j] = ' ';
				}

			}

	}
};

int menu(RenderWindow& window);

int setting(RenderWindow& window)
{
	window.clear();
	Texture Background;
	Background.loadFromFile("images/background4.png");
	Sprite background(Background);
	

	std::cout << "hi";

	window.draw(background);
	window.display();
	window.clear();
	
	bool isSet = true;
	while (isSet == true) {
		if ((Keyboard::isKeyPressed(Keyboard::Space)))
		{
			isSet = false;  return 300, menu(window);
		}
	}
	// здесь долно храниться число, говорящее о громкости звука
	// также здесь должны быть картинки и анимации регуляции звука
	// не забыть организовать выход из настроек в меню
	//sound.setVolume(50.f);

}


void game(RenderWindow& window)
{
	Texture backtexture;
	backtexture.loadFromFile("images/background1.png");
	Sprite back1;
	back1.setTexture(backtexture);
	back1.setTextureRect(IntRect(0, 0, 600, 400));
	back1.setPosition(0, 0);

	Music music;
	if (!music.openFromFile("music/main.ogg"))
		return;
	music.play();
	music.setLoop(true);

	SoundBuffer buffer_jump;
	if (!buffer_jump.loadFromFile("music/jump.wav"))
		return;
	Sound jump;
	jump.setBuffer(buffer_jump);

	SoundBuffer buffer_walk;
	buffer_walk.loadFromFile("music/walk.wav");
	Sound walk;
	walk.setBuffer(buffer_walk);


	Texture t;
	t.loadFromFile("images/hero.png");
	float currentFrame = 0;
	PLAYER p(t);

	Clock clock;

	RectangleShape rectangle(Vector2f(32, 32));

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 700;

		if (time > 20) time = 20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)))
		{
			p.dx = -0.1;
			walk.play();
		}


		if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)))
		{
			p.dx = 0.1;
			walk.play();
		}


		//jumpingg
		if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W)) || (Keyboard::isKeyPressed(Keyboard::Space)))
		{
			if (p.onGround)
			{
				p.dy = -0.35;
				p.onGround = false;
				jump.play();
			}
		}


		p.update(time);

		if (p.rect.left > 300) offsetX = p.rect.left - 300;
		offsetY = p.rect.top - 200;

		window.clear();

		window.draw(back1);

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'B') rectangle.setFillColor(Color::White);

				if (TileMap[i][j] == '0')  rectangle.setFillColor(Color::Red);

				if (TileMap[i][j] == ' ') continue;

				rectangle.setPosition(j * 32 - offsetX, i * 32 - offsetY);
				window.draw(rectangle);
			}

		window.draw(p.sprite);
		window.display();
	}
}

int menu(RenderWindow& window)
{
	Music music;
	if (!music.openFromFile("music/menu.ogg"))
		return 1;
	music.play();
	music.setLoop(true);

	Texture button1, button2, button3;
	button1.loadFromFile("images/start.png");
	button2.loadFromFile("images/settings.png");
	button3.loadFromFile("images/exit.png");
	Sprite start(button1), settings(button2), exit(button3);
	start.setPosition(120, 30);
	settings.setPosition(90, 150);
	exit.setPosition(160, 265);

	Texture MenuBackground;
	MenuBackground.loadFromFile("images/menu.png");
	Sprite background(MenuBackground);

	bool isMenu = -1;
	int menuNum = 0;

	background.setTextureRect(IntRect(0, 0, 600, 400));
	
	window.draw(background);
	window.draw(start);
	window.draw(settings);
	window.draw(exit);
	window.display();
	window.clear();

	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		start.setColor(Color::White);
		settings.setColor(Color::White);
		exit.setColor(Color::White);

		Vector2i mousePos = Mouse::getPosition(window);
		if(start.getGlobalBounds().contains(mousePos.x, mousePos.y)){ start.setColor(Color::Blue); menuNum = 1; }
		if (settings.getGlobalBounds().contains(mousePos.x, mousePos.y)) { settings.setColor(Color::Blue); menuNum = 2; }
		if (exit.getGlobalBounds().contains(mousePos.x, mousePos.y)) { exit.setColor(Color::Blue); menuNum = 3; }

		std::cout << menuNum;
		
		if(menuNum == 1 && (Mouse::isButtonPressed(Mouse::Left))) { music.stop();  isMenu = false; game(window); }
		if (menuNum == 2 && (Mouse::isButtonPressed(Mouse::Left))) { music.stop(); window.clear(); isMenu = false; setting(window); }
		if (menuNum == 3 && (Mouse::isButtonPressed(Mouse::Left))) { window.close(); isMenu = false; }
	}
}



int main()
{
	RenderWindow window(VideoMode(600, 400), "cute cat");

	menu(window);

	return 0;
}