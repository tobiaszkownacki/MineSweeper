#pragma once
#include <SFML/Graphics.hpp>

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
		void MoveUp() noexcept;
		void MoveDown() noexcept;
		void MoveLeft() noexcept;
		void MoveRight() noexcept;
		void setErrorMessage(const std::string& message) noexcept;
	private:
		sf::Font font;
		sf::Text title;
		sf::Text errorMessage;
		std::vector<sf::Text> menuOptions;
		int width, height, mines;
		int selectedItemIndex;
		void updateText() noexcept;
};

