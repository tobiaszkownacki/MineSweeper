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
	//void handleInput(sf::Event event);
	void draw();

private:
	int width;
	int height;
	int mines;
	sf::RenderWindow& window;

	void setWindow();
	Board board;

	//sf::Texture zeroMinesNeighbour;
	//sf::Texture oneMineNeighbour;
	//sf::Texture twoMinesNeighbour;
	//sf::Texture threeMinesNeighbour;
	//sf::Texture fourMinesNeighbour;
	//sf::Texture fiveMinesNeighbour;
	//sf::Texture sixMinesNeighbour;
	//sf::Texture sevenMinesNeighbour;
	//sf::Texture eightMinesNeighbour;
	//sd::Texture field;
	//sf::Texture flag;
	//sf::Texture mine;
	//sf::Texture flagMistake;

	std::vector<sf::Texture> textures;
	std::vector<std::vector<sf::Sprite>> sprites;

	sf::Font font;
	sf::Text FlagsLeft;
	sf::Text Timer;
	sf::Text GameOver;
	sf::Text GameWon;

	
};

