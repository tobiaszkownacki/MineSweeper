#include "Game.h"


Game::Game(int width, int height, int mines, sf::RenderWindow& window)
	: width(width), height(height), mines(mines), window(window), board(width, height, mines)
{
	if (!font.loadFromFile("../arial.ttf"))
	{
		std::cerr << "Error loading font\n";
	}

	textures.resize(14);
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
	if (!textures[13].loadFromFile("../images/clickedMine.png"))
		std::cerr << "Error loading texture clickedMine.png\n";

	windowWidth = static_cast<float>(width * 40);
	windowHeight = static_cast<float>(100 + height * 40);

    window.setSize(sf::Vector2u(static_cast<unsigned int>(windowWidth),
		static_cast<unsigned int>(windowHeight)));
	sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
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

void Game::handleMouseEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if(event.mouseButton.y < 100 || event.mouseButton.y > windowHeight)
			return;
		if(event.mouseButton.x < 0 || event.mouseButton.x > windowWidth)
			return;

		if (event.mouseButton.button == sf::Mouse::Left)
		{
			int x = event.mouseButton.x / 40;
			int y = (event.mouseButton.y - 100) / 40;
			leftClick(y, x);
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			int x = event.mouseButton.x / 40;
			int y = (event.mouseButton.y - 100) / 40;
			rightClick(y, x);
		}
	}

}

void Game::leftClick(int y, int x)
{
	std::cerr << board.getField(y, x).getAdjacentMines() << std::endl;
	if(board.getField(y, x).IsFlagged())
		return;
	board.RevealField(y, x);

	if (board.isGameWon())
	{
		wonGame(y, x);
		return;
	}
		
	else if (board.isGameLost())
	{
		gameOver(y, x);
		return;
	}

	sprites[y][x].setTexture(textures[board.getField(y, x).getAdjacentMines()]);

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			Field field = board.getField(i, j);
			int mines = field.getAdjacentMines();
			if (!field.IsRevealed())
				continue;
			else
				sprites[i][j].setTexture(textures[mines]);

		}
	}

}

void Game::rightClick(int y, int x)
{
	if (board.getField(y, x).IsRevealed())
		return;

	board.ToggleFlag(y, x);
	if(board.getField(y, x).IsFlagged())
		sprites[y][x].setTexture(textures[10]);
	else
		sprites[y][x].setTexture(textures[9]);
}


void Game::gameOver(int y, int x)
{
	// Reveal all mines and show mistakes
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			Field field = board.getField(i, j);
			if (field.IsMine())
				sprites[i][j].setTexture(textures[11]);
			else if (field.IsFlagged() && !field.IsMine())
				sprites[i][j].setTexture(textures[12]);
		}
	}

	// Show clicked incorrect mine
	sprites[y][x].setTexture(textures[13]);
}

void Game::wonGame(int y, int x)
{
	// TODO
	std::cerr << "Game Won\n";

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
