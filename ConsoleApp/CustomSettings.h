#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

class CustomSettings
{
	public:
		CustomSettings(float width, float height) noexcept;
		~CustomSettings() = default;
		void initializeText(sf::Text& text, const std::string& str, int size, sf::Color color, sf::Vector2f position) const noexcept;
		void draw(sf::RenderWindow &window) noexcept;
		void handleInput(sf::Event event) noexcept;
		int getWidth() const noexcept;
		int getHeight() const noexcept;
		int getMines() const noexcept;
		void setErrorMessage(const std::string& message) noexcept;
	private:
		sf::Font font;
		sf::Text title;
		sf::Text widthText;
		sf::Text heightText;
		sf::Text minesText;
		sf::Text errorMessage;
		int width, height, mines;
		int selectedItemIndex;
		void updateText() noexcept;
};

