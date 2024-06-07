#include "CustomSettings.h"
#include <iostream>

CustomSettings::CustomSettings(float windowWidth, float windowHeight) noexcept : width(9), height(9), mines(10), selectedItemIndex(0)
{
	if (!font.loadFromFile("../arial.ttf"))
	{
		std::cerr << "Error loading font\n";
	}
	sf::Text widthText, heightText, minesText;
	initializeText(title, "Enter Custom Settings", 48, sf::Color::Black, sf::Vector2f(windowWidth / 2.0f, windowHeight / 10.0f));
	initializeText(widthText, "", 48, sf::Color::Black, sf::Vector2f(windowWidth / 10.0f, windowHeight / 3.0f));
	initializeText(heightText, "", 48, sf::Color::Black, sf::Vector2f(windowWidth / 10.0f, windowHeight / 3.0f + 150));
	initializeText(minesText, "", 48, sf::Color::Black, sf::Vector2f(windowWidth / 10.0f, windowHeight / 3.0f + 300));
	menuOptions.push_back(widthText);
	menuOptions.push_back(heightText);
	menuOptions.push_back(minesText);
	initializeText(errorMessage, "", 24, sf::Color::Red, sf::Vector2f(windowWidth / 15.0f, windowHeight / 10.0f + 60));
	menuOptions[0].setFillColor(sf::Color::Red);
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
	menuOptions[0].setString("Width: " + std::to_string(width));
	menuOptions[1].setString("Height: " + std::to_string(height));
	menuOptions[2].setString("Mines: " + std::to_string(mines));
}

void CustomSettings::draw(sf::RenderWindow& window) noexcept
{
	window.draw(title);
	for (const auto& text : menuOptions)
		window.draw(text);

	if (width * height <= mines)
	{
		errorMessage.setString("Error: Number of mines must be less than the total number of cells.");
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
				MoveUp();
				break;
			case sf::Keyboard::Down:
				MoveDown();
				break;
			case sf::Keyboard::Left:
				MoveLeft();
				break;
			case sf::Keyboard::Right:
				MoveRight();
				break;
		}
		updateText();
	}
}

void CustomSettings::MoveUp() noexcept
{
	if (selectedItemIndex > 0)
	{
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void CustomSettings::MoveDown() noexcept
{
	if (selectedItemIndex + 1 < menuOptions.size())
	{
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void CustomSettings::MoveLeft() noexcept
{
	switch (selectedItemIndex)
	{
		case 0: if (width > 8) width--; break;
		case 1: if (height > 1) height--; break;
		case 2: if (mines > 1) mines--; break;
	}
}

void CustomSettings::MoveRight() noexcept
{
	switch (selectedItemIndex)
	{
	case 0: if (width < 45) width++; break;
	case 1: if (height < 20) height++; break;
	case 2: mines++; break;
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