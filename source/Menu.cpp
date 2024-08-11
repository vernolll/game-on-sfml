#include "Menu.h"
#include "Game.h"


int menu(RenderWindow& window)
{
	Music music;
	if (!music.openFromFile("resource/music/menu.ogg"))
		return 1;
	music.play();
	music.setLoop(true);

	int v = 0;
	std::ifstream file("volume.txt");
	if (file.is_open()) { file >> v; file.close(); }
	music.setVolume(v);

	SoundBuffer button;
	if (!button.loadFromFile("resource/music/button.wav"))
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
	MenuBackground.loadFromFile("resource/images/menu.png");
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
		

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		
		Vector2i mousePos = Mouse::getPosition(window);
		if (start.getGlobalBounds().contains(mousePos.x, mousePos.y)) { start.setFillColor(Color::Blue); menuNum = 1; }
		else { start.setFillColor(Color::White); }
		if (settings.getGlobalBounds().contains(mousePos.x, mousePos.y)) { settings.setFillColor(Color::Blue); menuNum = 2; }
		else { settings.setFillColor(Color::White); }
		if (exit.getGlobalBounds().contains(mousePos.x, mousePos.y)) { exit.setFillColor(Color::Blue); menuNum = 3; }
		else { exit.setFillColor(Color::White); }


		if (menuNum == 1 && (Mouse::isButtonPressed(Mouse::Left))) { click.play(); music.stop(); isMenu = false; game(window); }
		if (menuNum == 2 && (Mouse::isButtonPressed(Mouse::Left))) { click.play(); music.pause(); window.clear(); isMenu = false; setting(window, music); }
		if (menuNum == 3 && (Mouse::isButtonPressed(Mouse::Left))) { click.play(); window.close(); isMenu = false; }
	}
}