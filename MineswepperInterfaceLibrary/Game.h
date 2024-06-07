#pragma once
#include <SFML/Graphics.hpp>
#include "../MinesweeperLogicalLib/Board.h"
#include <iostream>

class Game
{
public:
	Game(int width, int height, int mines, sf::RenderWindow& window);
	~Game() = default;
	//void initializeText(sf::Text& text, const std::string& str, int size, sf::Color color, sf::Vector2f position) const noexcept;
	void handleMouseEvent(sf::Event event);
	void draw();

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

	sf::RenderWindow& window;
	Board board;

	std::vector<sf::Texture> textures;
	std::vector<std::vector<sf::Sprite>> sprites;

	sf::Font font;
	sf::Text FlagsLeft;
	sf::Text Timer;
	sf::Text GameOver;
	sf::Text GameWon;

	
};

