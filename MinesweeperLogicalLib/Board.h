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

	void InitializeBoard() noexcept;
	void GenerateMines() noexcept;	
	void CalculateAdjacentMines() noexcept;
	void RevealAdjacentFields(int x, int y) noexcept;

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

	void RevealField(int x, int y) noexcept;
	void ToggleFlag(int x, int y) noexcept;

	void RevealBombs() noexcept;

};

