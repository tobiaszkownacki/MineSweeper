#include "Board.h"
#include <random>

Board::Board(int width, int height, int mines) noexcept
{
	initializeBoard();
	generateMines();
	calculateAdjacentMines();
}

void Board::initializeBoard() noexcept
{
	this->width = width;
	this->height = height;
	this->mines = mines;
	revealedFields = 0;
	flagsLeft = mines;
	gameLost = false;
	gameWon = false;

	fields = std::vector<std::vector<Field>>(height, std::vector<Field>(width));

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
			fields[y][x] = Field();
	}
}

void Board::generateMines() noexcept
{
	std::random_device device;
	std::mt19937 generator(device());

	std::uniform_int_distribution<int> distY(0, height - 1);
	std::uniform_int_distribution<int> distX(0, width - 1);

	int minesToPlace = mines;
	while(minesToPlace > 0)
	{
		int x = distX(generator);
		int y = distY(generator);

		if (!fields[y][x].IsMine())
		{
			fields[y][x].SetMine();
			--minesToPlace;
		}
	}
}

void Board::calculateAdjacentMines() noexcept
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (!fields[y][x].IsMine())
				continue;

			// Calculate the range of neighboring cells
			int topY = std::max(0, y - 1);
			int downY = std::min(height - 1, y + 1);
			int leftX = std::max(0, x - 1);
			int rightX = std::min(width - 1, x + 1);

			// Increment adjacent mines for each neighboring cell
			for (int i = topY; i <= downY; ++i)
			{
				for (int j = leftX; j <= rightX; ++j)
				{
					if(!fields[i][j].IsMine())
						fields[i][j].incrementAdjacentMines();
				}
			}
		}
	}
}







