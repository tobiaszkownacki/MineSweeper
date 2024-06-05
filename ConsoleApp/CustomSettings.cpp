#include "CustomSettings.h"
#include <iostream>

CustomSettings::CustomSettings(float windowWidth, float windowHeight) : width(9), height(9), mines(10), selectedItemIndex(0)
{
	if (!font.loadFromFile("../arial.ttf"))
	{
		std::cerr << "Error loading font\n";
	}
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setString("Enter Custom Settings");
	title.setCharacterSize(48);
	sf::FloatRect titleRect = title.getLocalBounds();
	title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	title.setPosition(sf::Vector2f(windowWidth / 2.0f, windowHeight / 10.0f));
	widthText.setFont(font);
	widthText.setCharacterSize(48);
	widthText.setPosition(sf::Vector2f(windowWidth / 10.0f, windowHeight / 3.0f));
	heightText.setFont(font);
	heightText.setCharacterSize(48);
	heightText.setPosition(sf::Vector2f(windowWidth / 10.0f, windowHeight / 3.0f + 150));
	minesText.setFont(font);
	minesText.setCharacterSize(48);
	minesText.setPosition(sf::Vector2f(windowWidth / 10.0f, windowHeight / 3.0f + 300));
	errorMessage.setFont(font);
	errorMessage.setCharacterSize(24);
	errorMessage.setFillColor(sf::Color::Red);
	errorMessage.setPosition(sf::Vector2f(windowWidth / 15.0f, windowHeight / 10.0f + 60));
	updateText();
}

void CustomSettings::updateText()
{
	widthText.setString("Width: " + std::to_string(width));
	heightText.setString("Height: " + std::to_string(height));
	minesText.setString("Mines: " + std::to_string(mines));
	widthText.setFillColor(selectedItemIndex == 0 ? sf::Color::Red : sf::Color::Black);
	heightText.setFillColor(selectedItemIndex == 1 ? sf::Color::Red : sf::Color::Black);
	minesText.setFillColor(selectedItemIndex == 2 ? sf::Color::Red : sf::Color::Black);
}

void CustomSettings::draw(sf::RenderWindow& window)
{
	window.draw(title);
	window.draw(widthText);
	window.draw(heightText);
	window.draw(minesText);
	if (errorMessage.getString() != "")
	{
		window.draw(errorMessage);
	}
}

void CustomSettings::handleInput(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			selectedItemIndex = (selectedItemIndex + 2) % 3;
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			selectedItemIndex = (selectedItemIndex + 1) % 3;
		}
		else if (event.key.code == sf::Keyboard::Left)
		{
			switch (selectedItemIndex)
			{
				case 0: if (width > 1) width--; break;
				case 1: if (height > 1) height--; break;
				case 2: if (mines > 1) mines--; break;
			}
		}
		else if (event.key.code == sf::Keyboard::Right)
		{
			switch (selectedItemIndex)
			{
			case 0: width++; break;
			case 1: height++; break;
			case 2: mines++; break;
			}
		}
		updateText();
	}
}

int CustomSettings::getWidth() const
{
	return width;
}

int CustomSettings::getHeight() const
{
	return height;
}

int CustomSettings::getMines() const
{
	return mines;
}

void CustomSettings::setErrorMessage(const std::string& message)
{
	errorMessage.setString(message);
}