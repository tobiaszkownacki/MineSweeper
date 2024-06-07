#include "Board.h"
#include <random>

Board::Board(int width, int height, int mines) noexcept
{
	this->width = width;
	this->height = height;
	this->mines = mines;
	revealedFields = 0;
	flagsLeft = mines;
	gameLost = false;
	gameWon = false;
	firstClick = true;

	fields = std::vector<std::vector<Field>>(height, std::vector<Field>(width));

	GenerateMines();
	CalculateAdjacentMines();
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


	// If first click is a mine, move it to right corner
	if (firstClick && fields[y][x].IsMine())
	{
		TransportFirstClickedMine(y, x);

		fields[y][x].SetMine(false);
		// zero out adjacent mines
		for (auto& row : fields)
			for (auto& field : row)
				field.setAdjacentMines(0);

		CalculateAdjacentMines();
	}

	firstClick = false;


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

			// unflag the field if it has no adjacent mines
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

void Board::TransportFirstClickedMine(int y, int x) noexcept
{
	for (int i = 0; i < height; ++i)
		for (int j = width - 1; j >= 0; --j)
		{
			if (!fields[i][j].IsMine())
			{
				fields[i][j].SetMine();
				return;
			}
		}
}


