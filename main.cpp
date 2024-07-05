#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;


float offsetX = 0, offsetY = 0;


const int H = 12;
const int W = 40;

//map
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

//main character
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


	// collision
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

// settings from main menu
int setting(RenderWindow& window, Music& music)
{
	music.play();
	music.setLoop(true);

	Font font;
	if (!font.loadFromFile("font/HomeVideo-Regular.otf")) return 5;

	Text volume_txt;
	volume_txt.setFont(font);
	volume_txt.setString("Volume");
	volume_txt.setCharacterSize(20);
	volume_txt.setFillColor(Color(200, 200, 200));
	volume_txt.setPosition(300 - volume_txt.getGlobalBounds().width / 2, 70 - volume_txt.getGlobalBounds().height / 2);

	Text leng;
	leng.setFont(font);
	leng.setString("Language");
	leng.setCharacterSize(20);
	leng.setFillColor(Color(200, 200, 200));
	leng.setPosition(300 - leng.getGlobalBounds().width / 2, 150 - leng.getGlobalBounds().height / 2);

	window.clear();
	Texture Background;
	Background.loadFromFile("images/background4.png");
	Sprite background(Background);

	RectangleShape esc(Vector2f(15, 15));
	esc.setFillColor(Color::White);
	esc.setOutlineThickness(2);
	esc.setOutlineColor(Color(105, 105, 105));
	esc.setPosition(520, 60);

	RectangleShape rect(Vector2f(500, 300));
	rect.setFillColor(Color(169, 169, 169));
	rect.setOutlineThickness(5);
	rect.setOutlineColor(Color(105, 105, 105));
	rect.setPosition(50, 50);

	RectangleShape slider(Vector2f(400, 5));
	slider.setFillColor(Color::White);
	slider.setOutlineThickness(2);
	slider.setOutlineColor(Color(105, 105, 105));
	slider.setPosition(100, 100);

	int x = 500;

	RectangleShape sliderButton(Vector2f(10, 10));
	sliderButton.setFillColor(Color(255, 218, 185));
	sliderButton.setOutlineThickness(2);
	sliderButton.setOutlineColor(Color(210, 180, 140));
	sliderButton.setPosition(x, 95);
	
	bool isSet = true;
	int volume = 100;
	bool isDragging = false;
	while (isSet == true) 
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left &&
					sliderButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					isDragging = true;
				}
			}
			if (event.type == Event::MouseButtonReleased)
			{
				isDragging = false;
			}

			if (isDragging && event.type == Event::MouseMoved)
			{
				float newX = event.mouseMove.x - sliderButton.getSize().x / 2;
				if (newX < slider.getPosition().x)
					newX = slider.getPosition().x;
				if (newX + sliderButton.getSize().x > slider.getPosition().x + slider.getSize().x)
					newX = slider.getPosition().x + slider.getSize().x - sliderButton.getSize().x;
				sliderButton.setPosition(newX, sliderButton.getPosition().y);
			}

			if ((Keyboard::isKeyPressed(Keyboard::Space)))
			{
				music.stop(); return menu(window), 300;
			}
		}
		window.draw(background);
		window.draw(rect);
		window.draw(slider);
		window.draw(sliderButton);
		window.draw(volume_txt);
		window.draw(leng);
		window.draw(esc);
		window.display();
	}

	// ораганзовать перевод на русский

	// здесь долно храниться число, говорящее о громкости звука
	// также здесь должны быть картинки и анимации регуляции звука
	// не забыть организовать выход из настроек в меню
	//sound.setVolume(50.f);
}


void game(RenderWindow& window)
{
	window.setMouseCursorVisible(false); //отключаем видимость курсора
	
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
		if ((Keyboard::isKeyPressed(Keyboard::Escape)))
		{
			// сделать внтриигровое меню
			window.close();
		}

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


		//jumping
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

	SoundBuffer button;
	if (!button.loadFromFile("music/button.wav"))
		return 10;
	Sound click;
	click.setBuffer(button);

	Font font;
	if (!font.loadFromFile("font/HomeVideo-Bold.otf")) return 5;

	Text start;
	start.setFont(font);
	start.setString("start");
	start.setCharacterSize(75);
	
	start.setPosition(300 - start.getGlobalBounds().width / 2, start.getGlobalBounds().height);

	Text settings;
	settings.setFont(font);
	settings.setString("settings");
	settings.setCharacterSize(75);

	settings.setPosition(300 - settings.getGlobalBounds().width / 2, 200 - settings.getGlobalBounds().height / 2);

	Text exit;
	exit.setFont(font);
	exit.setString("exit");
	exit.setCharacterSize(75);

	exit.setPosition(300 - exit.getGlobalBounds().width / 2, 300 - exit.getGlobalBounds().height / 2);

	// надо чтобы экран появлялся плавно из темноты
	Texture MenuBackground;
	MenuBackground.loadFromFile("images/menu.png");
	Sprite background(MenuBackground);
	background.setTextureRect(IntRect(0, 0, 600, 400));

	window.draw(background);
	window.draw(start);
	window.draw(settings);
	window.draw(exit);
	window.display();

	bool isMenu = true;
	int menuNum = 0;

	while (isMenu)
	{
		start.setFillColor(Color::White);
		settings.setFillColor(Color::White);
		exit.setFillColor(Color::White);

		// криво работает крестик
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		// почему-то не меняется цвета
		Vector2i mousePos = Mouse::getPosition(window);
		if (start.getGlobalBounds().contains(mousePos.x, mousePos.y)) { start.setFillColor(Color::Blue); menuNum = 1; }
		else { start.setFillColor(Color::White); }
		if (settings.getGlobalBounds().contains(mousePos.x, mousePos.y)) { settings.setFillColor(Color::Blue); menuNum = 2; }
		else { settings.setFillColor(Color::White); }
		if (exit.getGlobalBounds().contains(mousePos.x, mousePos.y)) { exit.setFillColor(Color::Blue); menuNum = 3; }
		else { exit.setFillColor(Color::White); }

		std::cout << menuNum;

		if (menuNum == 1 && (Mouse::isButtonPressed(Mouse::Left))) { click.play(); music.stop(); isMenu = false; game(window); }
		if (menuNum == 2 && (Mouse::isButtonPressed(Mouse::Left))) { click.play(); music.stop(); window.clear(); isMenu = false; setting(window, music); }
		if (menuNum == 3 && (Mouse::isButtonPressed(Mouse::Left))) { click.play(); window.close(); isMenu = false; }
	}
}

int main()
{
	RenderWindow window(VideoMode(600, 400), "cute cat");

	menu(window);

	return 0;
}