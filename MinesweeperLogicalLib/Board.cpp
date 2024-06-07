#include "Board.h"
#include <random>
#include <cmath>

Board::Board(int width, int height, int mines) noexcept
{
	this->width = width;
	this->height = height;
	this->mines = mines;
	revealedFields = 0;
	flagsLeft = mines;
	gameLost = false;
	gameWon = false;
	generatedMines = false;
	fields = std::vector<std::vector<Field>>(height, std::vector<Field>(width));
}

void Board::GenerateMines(int y, int x) noexcept
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distY(0, height - 1);
	std::uniform_int_distribution<int> distX(0, width - 1);
	int minesToPlace = mines;
	int totalFields = width * height;
	while(minesToPlace > 0)
	{
		int bomb_x = distX(generator);
		int bomb_y = distY(generator);
		if (totalFields - mines >= 9)
		{
			if (std::abs(y - bomb_y) <= 1 && std::abs(x - bomb_x) <= 1)
				continue;
		} else {
			if (y == bomb_y && x == bomb_x)
				continue;
		}
		if (!fields[bomb_y][bomb_x].IsMine())
		{
			fields[bomb_y][bomb_x].SetMine();
			--minesToPlace;
		}
	}
	CalculateAdjacentMines();
	generatedMines = true;
}

void Board::CalculateAdjacentMines() noexcept
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (!fields[y][x].IsMine())
				continue;
			int topY = std::max(0, y - 1);
			int downY = std::min(height - 1, y + 1);
			int leftX = std::max(0, x - 1);
			int rightX = std::min(width - 1, x + 1);
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

int Board::getWidth() const noexcept
{
	return width;
}

int Board::getHeight() const noexcept
{
	return height;
}

int Board::getMines() const noexcept
{
	return mines;
}


int Board::getRevealedFields() const noexcept
{
	return revealedFields;
}

int Board::getFlagsLeft() const noexcept
{
	return flagsLeft;
}

bool Board::isGameLost() const noexcept
{
	return gameLost;
}

bool Board::isGameWon() const noexcept
{
	return gameWon;
}

Field& Board::getField(int y, int x) noexcept
{
	return fields[y][x];
}

void Board::RevealField(int y, int x) noexcept
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
		RevealAdjacentFields(y, x);
	if (revealedFields == width * height - mines)
		gameWon = true;
}

void Board::RevealAdjacentFields(int y, int x) noexcept
{
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
			if (fields[i][j].IsFlagged() && fields[i][j].getAdjacentMines() == 0)
			{
				fields[i][j].ToggleFlag();
				++flagsLeft;
			}
			else if (fields[i][j].IsFlagged())
				continue;
			fields[i][j].Reveal();
			++revealedFields;
			if (fields[i][j].getAdjacentMines() == 0)
				RevealAdjacentFields(i, j);
		}
	}
}

void Board::ToggleFlag(int y, int x) noexcept
{
	if (fields[y][x].IsRevealed())
		return;
	if (flagsLeft == 0 && !fields[y][x].IsFlagged())
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