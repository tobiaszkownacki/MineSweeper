#pragma once
#include <SFML/Graphics.hpp>
#include "../MinesweeperLogicalLib/Board.h"
#include <iostream>

class Game
{
public:
	Game(int width, int height, int mines, sf::RenderWindow& window);
	~Game() = default;
	void handleMouseEvent(sf::Event event);
	void draw();
	bool isGameOver() const noexcept;
	bool isGameWon() const noexcept;

private:
	int width;
	int height;
	int mines;
	float windowWidth;
	float windowHeight;

	void leftClick(int y, int x);
	void rightClick(int y, int x);

	void gameOver(int y, int x);
	void wonGame(int y, int x);

	void initializeText(sf::Text& text, const std::string& str, int size, sf::Color color, sf::Vector2f position) const noexcept;
	void updateFlagsLeft() noexcept;

	sf::RenderWindow& window;
	Board board;

	std::vector<sf::Texture> textures;
	std::vector<std::vector<sf::Sprite>> sprites;

	sf::Sprite smiley;
	void resetBoard() noexcept;

	sf::Font font;
	sf::Text FlagsLeft;
	sf::Text Timer;
	sf::Clock gameClock;

	void updateClock() noexcept;
	int seconds;
};

