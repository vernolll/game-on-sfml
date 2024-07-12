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
	if (!music.openFromFile("music/main_theme.ogg"))
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

	Texture  apple;
	apple.loadFromFile("images/apple.png");

	Texture character;
	character.loadFromFile("images/marshroom.png");
	Sprite ch;
	ch.setTexture(character);
	ch.setTextureRect(IntRect(0, 0, 60, 60));

	Texture cloud;
	cloud.loadFromFile("images/talking1.png");
	Sprite cl;
	cl.setTexture(cloud);
	cl.setTextureRect(IntRect(0, 0, 60, 60));

	Texture cloud1;
	cloud1.loadFromFile("images/talking.png");
	Sprite cl1;
	cl1.setTexture(cloud1);
	cl1.setTextureRect(IntRect(0, 0, 60, 60));

	Texture  nothing;
	nothing.loadFromFile("images/nothing.png");

	Texture tree1;
	tree1.loadFromFile("images/tree2.png");
	Sprite tr1;
	tr1.setTexture(tree1);
	tr1.setTextureRect(IntRect(0, 0, 65, 153));

	Texture tree2;
	tree2.loadFromFile("images/tree6.png");
	Sprite tr2;
	tr2.setTexture(tree2);
	tr2.setTextureRect(IntRect(0, 0, 96, 117));

	Texture tree3;
	tree3.loadFromFile("images/tree5.png");
	Sprite tr3;
	tr3.setTexture(tree3);
	tr3.setTextureRect(IntRect(0, 0, 111, 128));

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
			if (walk.getStatus() != Sound::Playing) {
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

		tr1.setPosition(200 - offsetX, 210 - offsetY);
		window.draw(tr1);
		tr2.setPosition(600 - offsetX, 120 - offsetY);
		window.draw(tr2);
		tr3.setPosition(900 - offsetX, 245 - offsetY);
		window.draw(tr3);

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'B') rectangle.setTexture(&earth);
				if (TileMap[i][j] == 'L') rectangle.setTexture(&nothing);
				if (TileMap[i][j] == 'E') rectangle.setTexture(&earth_edge);
				if (TileMap[i][j] == '0')  rectangle.setTexture(&apple);
				if (TileMap[i][j] == 'X')  rectangle.setTexture(&box);
				if (TileMap[i][j] == 'e')  rectangle.setTexture(&earth_edge1);
				if (TileMap[i][j] == ' ') continue;
				
				rectangle.setPosition(j * 32 - offsetX, i * 32 - offsetY);
				window.draw(rectangle);
			}

		ch.setPosition(700 - offsetX, 292 - offsetY);
		window.draw(ch);
		window.draw(p.sprite);


		if ((p.sprite.getGlobalBounds().intersects(ch.getGlobalBounds())) && (pick_up == false))
		{
			cl.setPosition(650 - offsetX, 280 - offsetY);
			window.draw(cl);
		}

		if ((p.sprite.getGlobalBounds().intersects(ch.getGlobalBounds())) && (pick_up == true))
		{
			cl1.setPosition(650 - offsetX, 280 - offsetY);
			window.draw(cl1);
		}

		bool is_menu = false;
		if ((Keyboard::isKeyPressed(Keyboard::Escape)))
		{
			music.pause(); vl = internal_settings(window);
		}
		window.display();
	}
}