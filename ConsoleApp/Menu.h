#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
	public:
		Menu(float width, float height);
		~Menu() = default;
		void draw(sf::RenderWindow &window);
		void handleInput(sf::Event event);
		void MoveUp();
		void MoveDown();
		int GetPressedItem() const;
	private:
		int selectedItemIndex;
		sf::Font font;
		std::vector<sf::Text> menuOptions;
		sf::Text title;
};

