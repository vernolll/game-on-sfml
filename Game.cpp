#include "Game.h"
#include "Internal_menu.h"

void game(RenderWindow& window)
{
	window.setMouseCursorVisible(false); //отключаем видимость курсора

	Texture backtexture;
	backtexture.loadFromFile("images/main_background.png");
	Sprite back1;
	back1.setTexture(backtexture);
	back1.setTextureRect(IntRect(0, 0, 600, 400));
	back1.setPosition(0, 0);

	Music music;
	if (!music.openFromFile("music/main.ogg"))
		return;
	music.play();
	music.setLoop(true);


	int vl;
	std::ifstream file("volume.txt");
	if (file.is_open()) { file >> vl; file.close(); }
	music.setVolume(vl);

	SoundBuffer buffer_jump;
	if (!buffer_jump.loadFromFile("music/jump.wav"))
		return;
	Sound jump;
	jump.setBuffer(buffer_jump);

	SoundBuffer buffer_walk;
	buffer_walk.loadFromFile("music/walking.wav");
	Sound walk;
	walk.setBuffer(buffer_walk);


	Texture t;
	t.loadFromFile("images/hero2.png");
	float currentFrame = 0;
	PLAYER p(t);

	Clock clock;

	RectangleShape rectangle(Vector2f(32, 32));

	Texture earth;
	earth.loadFromFile("images/earth.png");

	Texture  earth_edge;
	earth_edge.loadFromFile("images/earth_edge.png");

	Texture	box;
	box.loadFromFile("images/box.png");

	Texture  earth_edge1;
	earth_edge1.loadFromFile("images/earth_edge1.png");

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

		bool is_moving = false;
		if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)))
		{
			is_moving = true;
			p.dx = -0.1;
		}


		if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)))
		{
			is_moving = true;
			p.dx = 0.1;
		}

		if (is_moving) {
			if (walk.getStatus() != sf::Sound::Playing) {
				walk.play();
			}
		}
		else {
			walk.stop();
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
				if (TileMap[i][j] == 'B') rectangle.setTexture(&earth);

				if (TileMap[i][j] == 'E') rectangle.setTexture(&earth_edge);

				if (TileMap[i][j] == '0')  rectangle.setTexture(&earth_edge);

				if (TileMap[i][j] == 'X')  rectangle.setTexture(&box);

				if (TileMap[i][j] == 'e')  rectangle.setTexture(&earth_edge1);

				if (TileMap[i][j] == ' ') continue;

				rectangle.setPosition(j * 32 - offsetX, i * 32 - offsetY);
				window.draw(rectangle);
			}

		window.draw(p.sprite);


		bool is_menu = false;
		if ((Keyboard::isKeyPressed(Keyboard::Escape)))
		{
			vl = internal_settings(window, music);
		}
		window.display();
	}
}