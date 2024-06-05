#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

class CustomSettings
{
	public:
		CustomSettings(float width, float height);
		~CustomSettings() = default;
		void draw(sf::RenderWindow &window);
		void handleInput(sf::Event event);
		int getWidth() const;
		int getHeight() const;
		int getMines() const;
		void setErrorMessage(const std::string& message);
	private:
		sf::Font font;
		sf::Text title;
		sf::Text widthText;
		sf::Text heightText;
		sf::Text minesText;
		sf::Text errorMessage;
		int width, height, mines;
		int selectedItemIndex;
		void updateText();
};

