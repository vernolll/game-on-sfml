#include "Internal_menu.h"

int internal_settings(RenderWindow& window, Music& music)
{
	window.setMouseCursorVisible(true);
	//регул€ци€ громкости
	int vl;
	std::ifstream file("volume.txt");
	if (file.is_open()) { file >> vl; file.close(); }
	music.setVolume(vl);

	music.play();
	music.setLoop(true);

	SoundBuffer button;
	if (!button.loadFromFile("music/button.wav"))
		return 10;
	Sound click;
	click.setBuffer(button);

	Font font;
	if (!font.loadFromFile("font/HomeVideo-Regular.otf")) return 5;

	Text volume_txt;
	volume_txt.setFont(font);
	volume_txt.setString("Volume");
	volume_txt.setCharacterSize(20);
	volume_txt.setFillColor(Color(200, 200, 200));
	volume_txt.setPosition(300 - volume_txt.getGlobalBounds().width / 2, 70 - volume_txt.getGlobalBounds().height / 2);

	Text menu_txt;
	menu_txt.setFont(font);
	menu_txt.setString("Menu");
	menu_txt.setCharacterSize(20);
	menu_txt.setFillColor(Color(200, 200, 200));
	menu_txt.setPosition(460 - menu_txt.getGlobalBounds().width / 2, 310 - menu_txt.getGlobalBounds().height / 2);

	Text artist;
	artist.setFont(font);
	artist.setString("Artist: Yagyaeva Ava");
	artist.setCharacterSize(20);
	artist.setFillColor(Color(200, 200, 200));
	artist.setPosition(200 - artist.getGlobalBounds().width / 2, 200 - artist.getGlobalBounds().height / 2);

	Text developer;
	developer.setFont(font);
	developer.setString("developer: Karas Marina");
	developer.setCharacterSize(20);
	developer.setFillColor(Color(200, 200, 200));
	developer.setPosition(220 - developer.getGlobalBounds().width / 2, 230 - developer.getGlobalBounds().height / 2);

	window.clear();
	Texture Background;
	Background.loadFromFile("images/main_background.png");
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

	int x = vl * 5;

	RectangleShape sliderButton(Vector2f(10, 10));
	sliderButton.setFillColor(Color(255, 218, 185));
	sliderButton.setOutlineThickness(2);
	sliderButton.setOutlineColor(Color(210, 180, 140));
	sliderButton.setPosition(x, 95);

	RectangleShape main_menu(Vector2f(120, 30));
	main_menu.setFillColor(Color(169, 169, 169));
	main_menu.setOutlineThickness(5);
	main_menu.setOutlineColor(Color(128, 128, 128));
	main_menu.setPosition(400, 300);

	//организовать выход в главное меню

	bool isSet = true;
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
					isDragging = true; click.play();
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

		}

		int v = sliderButton.getPosition().x / 5;
		music.setVolume(v);

		std::ofstream out;
		out.open("volume.txt");
		if (out.is_open()) { out << v; }
		out.close();

		bool exit = false;
		Vector2i mousePos = Mouse::getPosition(window);
		if (esc.getGlobalBounds().contains(mousePos.x, mousePos.y)) { exit = true; }
		if (exit && (Mouse::isButtonPressed(Mouse::Left))) { click.play(); music.pause(); isSet = false; return game(window), v; }

		bool ex_to_menu = false;
		if (main_menu.getGlobalBounds().contains(mousePos.x, mousePos.y)) { ex_to_menu = true; }
		if (ex_to_menu && (Mouse::isButtonPressed(Mouse::Left))) { click.play(); music.pause(); isSet = false; return menu(window), v; }

		window.draw(background);
		window.draw(rect);
		window.draw(slider);
		window.draw(sliderButton);
		window.draw(volume_txt);
		window.draw(esc);
		window.draw(main_menu);
		window.draw(menu_txt);
		window.draw(artist);
		window.draw(developer);
		window.display();
	}
}