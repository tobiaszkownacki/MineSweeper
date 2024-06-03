#pragma once
#include <vector>
#include "Field.h"

class Board
{
private:
	int width;
	int height;
	int mines;
	int revealedFields;
	int flagsLeft;
	bool gameLost;
	bool gameWon;

	std::vector<std::vector<Field>> fields;

	void generateMines() noexcept;	
	void calculateAdjacentMines() noexcept;
	void revealAdjacentFields(int x, int y) noexcept;

public:
	Board(int width, int height, int mines) noexcept;
	~Board() noexcept = default;

	int getWidth() noexcept;
	int getHeight() noexcept;
	int getMines() noexcept;
	int getRevealedFields() noexcept;
	int getFlagsLeft() noexcept;

	bool isGameLost() noexcept;
	bool isGameWon() noexcept;

	Field& getField(int x, int y) noexcept;

	void revealField(int x, int y) noexcept;
	void toggleFlag(int x, int y) noexcept;

	void revealAllFields() noexcept;

};

