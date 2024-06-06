#include "CustomSettings.h"
#include <iostream>

CustomSettings::CustomSettings(float windowWidth, float windowHeight) noexcept : width(9), height(9), mines(10), selectedItemIndex(0)
{
	if (!font.loadFromFile("../arial.ttf"))
	{
		std::cerr << "Error loading font\n";
	}
	initializeText(title, "Enter Custom Settings", 48, sf::Color::Black, sf::Vector2f(windowWidth / 2.0f, windowHeight / 10.0f));
	initializeText(widthText, "", 48, sf::Color::Black, sf::Vector2f(windowWidth / 10.0f, windowHeight / 3.0f));
	initializeText(heightText, "", 48, sf::Color::Black, sf::Vector2f(windowWidth / 10.0f, windowHeight / 3.0f + 150));
	initializeText(minesText, "", 48, sf::Color::Black, sf::Vector2f(windowWidth / 10.0f, windowHeight / 3.0f + 300));
	initializeText(errorMessage, "", 24, sf::Color::Red, sf::Vector2f(windowWidth / 15.0f, windowHeight / 10.0f + 60));
	updateText();
}

void CustomSettings::initializeText(sf::Text& text, const std::string& str, int size, sf::Color color, sf::Vector2f position) const noexcept
{
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setPosition(position);
	if (str == "Enter Custom Settings")
	{
		sf::FloatRect titleRect = text.getLocalBounds();
		text.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);

	}
}

void CustomSettings::updateText() noexcept
{
	widthText.setString("Width: " + std::to_string(width));
	heightText.setString("Height: " + std::to_string(height));
	minesText.setString("Mines: " + std::to_string(mines));
	widthText.setFillColor(selectedItemIndex == 0 ? sf::Color::Red : sf::Color::Black);
	heightText.setFillColor(selectedItemIndex == 1 ? sf::Color::Red : sf::Color::Black);
	minesText.setFillColor(selectedItemIndex == 2 ? sf::Color::Red : sf::Color::Black);
}

void CustomSettings::draw(sf::RenderWindow& window) noexcept
{
	window.draw(title);
	window.draw(widthText);
	window.draw(heightText);
	window.draw(minesText);
	if (errorMessage.getString().isEmpty())
	{
		window.draw(errorMessage);
	}
}

void CustomSettings::handleInput(sf::Event event) noexcept
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
			case sf::Keyboard::Up:
				selectedItemIndex = (selectedItemIndex + 2) % 3;
				break;
			case sf::Keyboard::Down:
				selectedItemIndex = (selectedItemIndex + 1) % 3;
				break;
			case sf::Keyboard::Left:
				switch (selectedItemIndex)
				{
					case 0: if (width > 1) width--; break;
					case 1: if (height > 1) height--; break;
					case 2: if (mines > 1) mines--; break;
				}
				break;
			case sf::Keyboard::Right:
				switch (selectedItemIndex)
				{
					case 0: width++; break;
					case 1: height++; break;
					case 2: mines++; break;
				}
				break;
		}
		updateText();
	}
}

int CustomSettings::getWidth() const noexcept
{
	return width;
}

int CustomSettings::getHeight() const noexcept
{
	return height;
}

int CustomSettings::getMines() const noexcept
{
	return mines;
}

void CustomSettings::setErrorMessage(const std::string& message) noexcept
{
	errorMessage.setString(message);
}