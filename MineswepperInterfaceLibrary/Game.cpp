#include "Game.h"


Game::Game(int width, int height, int mines, sf::RenderWindow& window)
	: width(width), height(height), mines(mines), window(window), board(width, height, mines)
{
	if (!font.loadFromFile("../arial.ttf"))
	{
		std::cerr << "Error loading font\n";
	}

	textures.resize(13);
	if(!textures[0].loadFromFile("../images/zeroMinesNeighbour.png"))
		std::cerr << "Error loading texture zero\n";
	if (!textures[1].loadFromFile("../images/oneMineNeighbour.png"))
		std::cerr << "Error loading texture one\n";
	if (!textures[2].loadFromFile("../images/twoMinesNeighbour.png"))
		std::cerr << "Error loading texture two\n";
	if (!textures[3].loadFromFile("../images/threeMinesNeighbour.png"))
		std::cerr << "Error loading texture three\n";
	if (!textures[4].loadFromFile("../images/fourMinesNeighbour.png"))
		std::cerr << "Error loading texture four\n";
	if (!textures[5].loadFromFile("../images/fiveMinesNeighbour.png"))
		std::cerr << "Error loading texture five\n";
	if (!textures[6].loadFromFile("../images/sixMinesNeighbour.png"))
		std::cerr << "Error loading texture six\n";
	if (!textures[7].loadFromFile("../images/sevenMinesNeighbour.png"))
		std::cerr << "Error loading texture seven\n";
	if (!textures[8].loadFromFile("../images/eightMinesNeighbour.png"))
		std::cerr << "Error loading texture eight\n";
	if (!textures[9].loadFromFile("../images/field.png"))
		std::cerr << "Error loading texture field\n";
	if (!textures[10].loadFromFile("../images/flag.png"))
		std::cerr << "Error loading texture flag\n";
	if (!textures[11].loadFromFile("../images/mine.png"))
		std::cerr << "Error loading texture mine\n";
	if (!textures[12].loadFromFile("../images/flagMistake.png"))
		std::cerr << "Error loading texture flagMistake\n";

	window.setSize(sf::Vector2u(width * 40, 100 + height * 40));

	// Ustawienie widoku
	sf::View view(sf::FloatRect(0, 0, static_cast<float>(width * 40), static_cast<float>(100 + height * 40)));
	window.setView(view);

	sprites.resize(height);
	for (int i = 0; i < height; ++i)
	{
		sprites[i].resize(width);
		for (int j = 0; j < width; ++j)
		{
			
			sprites[i][j].setTexture(textures[9]);
			sprites[i][j].setScale(1.0f, 1.0f);
			sprites[i][j].setPosition(static_cast<float>(j * 40), static_cast<float>(100 + i * 40));
		}
	}
}

void Game::draw()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			window.draw(sprites[i][j]);
		}
	}
}
