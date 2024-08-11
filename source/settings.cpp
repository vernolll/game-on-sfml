#include "settings.h"

using namespace sf;

int setting(RenderWindow& window, Music& music) 
{
	// setting volume
	int vl;
	std::ifstream file("volume.txt");
	if (file.is_open()) { file >> vl; file.close(); }
	music.setVolume(vl);

	music.play();
	music.setLoop(true);

	SoundBuffer button;
	if (!button.loadFromFile("resource/music/button.wav"))
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

	Text leng;
	leng.setFont(font);
	leng.setString("Language");
	leng.setCharacterSize(20);
	leng.setFillColor(Color(200, 200, 200));
	leng.setPosition(300 - leng.getGlobalBounds().width / 2, 150 - leng.getGlobalBounds().height / 2);

	window.clear();
	Texture Background;
	Background.loadFromFile("resource/images/menu.png");
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

	RectangleShape rect1(Vector2f(150, 20));
	rect1.setFillColor(Color(169, 169, 169));
	rect1.setOutlineThickness(5);
	rect1.setOutlineColor(Color(128, 128, 128));
	rect1.setPosition(225, 200);

	RectangleShape rect2(Vector2f(150, 20));
	rect2.setFillColor(Color(169, 169, 169));
	rect2.setOutlineThickness(5);
	rect2.setOutlineColor(Color(128, 128, 128));
	rect2.setPosition(225, 250);

	Text eng;
	eng.setFont(font);
	eng.setString("English");
	eng.setCharacterSize(15);
	eng.setFillColor(Color(220, 220, 220));
	eng.setPosition(300 - eng.getGlobalBounds().width / 2, 205 - eng.getGlobalBounds().height / 2);

	Text rus;
	rus.setFont(font);
	rus.setString("Russian");
	rus.setCharacterSize(15);
	rus.setFillColor(Color(220, 220, 220));
	rus.setPosition(300 - rus.getGlobalBounds().width / 2, 255 - rus.getGlobalBounds().height / 2);
	
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
		if (exit && (Mouse::isButtonPressed(Mouse::Left))) { click.play();music.pause(); isSet = false; return menu(window), v; }

		window.draw(background);
		window.draw(rect);
		window.draw(slider);
		window.draw(sliderButton);
		window.draw(volume_txt);
		window.draw(leng);
		window.draw(esc);
		window.draw(rect1);
		window.draw(rect2);
		window.draw(eng);
		window.draw(rus);
		window.display();
	}
}