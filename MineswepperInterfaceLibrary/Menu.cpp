#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) noexcept
{
	if (!font.loadFromFile("../arial.ttf"))
	{
		std::cerr << "Error loading font\n";
	}
	initializeText(title, "Select the difficulty", 48, sf::Color::Black, sf::Vector2f(width / 2.0f, height / 10.0f));
	std::vector<std::string> menuItems = { "Easy", "Medium", "Extreme", "Custom" };
	for (size_t i = 0; i < menuItems.size(); ++i)
	{
		sf::Text text;
		initializeText(text, menuItems[i], 48, (i == 0) ? sf::Color::Red : sf::Color::Black, { width / 10.0f, height / (menuItems.size() + 1) * (i + 1) });
		menuOptions.push_back(text);
	}
	selectedItemIndex = 0;
}

void Menu::initializeText(sf::Text& text, const std::string& str, int size, sf::Color color, sf::Vector2f position) const noexcept
{
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(size);
	text.setFillColor(color);
	if (str == "Select the difficulty")
	{
		sf::FloatRect titleRect = text.getLocalBounds();
		text.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	}
	text.setPosition(position);
}

void Menu::draw(sf::RenderWindow &window) noexcept
{
	window.draw(title);
	for (const auto &text : menuOptions)
	{
		window.draw(text);
	}
}

void Menu::handleInput(sf::Event event) noexcept
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
		}
	}
}

void Menu::MoveUp() noexcept
{
	if (selectedItemIndex > 0)
	{
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown() noexcept
{
	if (selectedItemIndex + 1 < menuOptions.size())
	{
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::GetPressedItem() const noexcept
{
	return selectedItemIndex;
}