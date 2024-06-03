#include "Board.h"
#include <random>

Board::Board(int width, int height, int mines) noexcept
{
	InitializeBoard();
	GenerateMines();
	CalculateAdjacentMines();
}

void Board::InitializeBoard() noexcept
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

void Board::GenerateMines() noexcept
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

void Board::CalculateAdjacentMines() noexcept
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

int Board::getWidth() noexcept
{
	return width;
}

int Board::getHeight() noexcept
{
	return height;
}

int Board::getMines() noexcept
{
	return mines;
}


int Board::getRevealedFields() noexcept
{
	return revealedFields;
}

int Board::getFlagsLeft() noexcept
{
	return flagsLeft;
}

bool Board::isGameLost() noexcept
{
	return gameLost;
}

bool Board::isGameWon() noexcept
{
	return gameWon;
}

Field& Board::getField(int x, int y) noexcept
{
	return fields[y][x];
}

void Board::RevealField(int x, int y) noexcept
{
	if (fields[y][x].IsFlagged() || fields[y][x].IsRevealed())
		return;

	if (fields[y][x].IsMine())
	{
		gameLost = true;
		RevealBombs();
		return;
	}

	fields[y][x].Reveal();
	++revealedFields;

	if (fields[y][x].getAdjacentMines() == 0)
		RevealAdjacentFields(x, y);

	if (revealedFields == width * height - mines)
		gameWon = true;
}

void Board::RevealAdjacentFields(int x, int y) noexcept
{
	// Calculate the range of neighboring cells
	int topY = std::max(0, y - 1);
	int downY = std::min(height - 1, y + 1);
	int leftX = std::max(0, x - 1);
	int rightX = std::min(width - 1, x + 1);

	for (int i = topY; i <= downY; ++i)
	{
		for (int j = leftX; j <= rightX; ++j)
		{
			if (fields[i][j].IsRevealed())
				continue;

			fields[i][j].Reveal();
			++revealedFields;

			if (fields[i][j].getAdjacentMines() == 0)
				RevealAdjacentFields(j, i);
		}
	}
}

void Board::ToggleFlag(int x, int y) noexcept
{
	if (fields[y][x].IsRevealed())
		return;

	fields[y][x].ToggleFlag();
	if (fields[y][x].IsFlagged())
		--flagsLeft;
	else
		++flagsLeft;
}

void Board::RevealBombs() noexcept
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (fields[y][x].IsMine())
				fields[y][x].Reveal();
		}
	}
}


