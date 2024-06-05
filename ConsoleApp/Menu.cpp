#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("../arial.ttf"))
	{
		std::cerr << "Error loading font\n";
	}
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setString("Select the difficulty");
	title.setCharacterSize(48);
	sf::FloatRect titleRect = title.getLocalBounds();
	title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	title.setPosition(sf::Vector2f(width / 2.0f, height / 10.0f));
	std::vector<std::string> menuItems = { "Easy", "Medium", "Extreme", "Custom" };
	for (int i = 0; i < menuItems.size(); ++i)
	{
		sf::Text text;
		text.setFont(font);
		text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::Black);
		text.setString(menuItems[i]);
		text.setCharacterSize(48);
		text.setPosition(sf::Vector2f(width / 10.0f, height / (menuItems.size() + 1) * (i + 1)));
		menuOptions.push_back(text);
	}
	selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow &window)
{
	window.draw(title);
	for (const auto &text : menuOptions)
	{
		window.draw(text);
	}
}

void Menu::handleInput(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			MoveUp();
		}
		if (event.key.code == sf::Keyboard::Down)
		{
			MoveDown();
		}
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < menuOptions.size())
	{
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::GetPressedItem() const
{
	return selectedItemIndex;
}