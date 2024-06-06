#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
	public:
		Menu(float width, float height) noexcept;
		~Menu() = default;
		void initializeText(sf::Text& text, const std::string& str, int size, sf::Color color, sf::Vector2f position) const noexcept;
		void draw(sf::RenderWindow &window) noexcept;
		void handleInput(sf::Event event) noexcept;
		void MoveUp() noexcept;
		void MoveDown() noexcept;
		int GetPressedItem() const noexcept;
	private:
		int selectedItemIndex;
		sf::Font font;
		std::vector<sf::Text> menuOptions;
		sf::Text title;
};

