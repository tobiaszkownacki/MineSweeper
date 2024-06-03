#pragma once
#include <vector>
#include "Field.h"

class Board
{
protected:
	int width;
	int height;
	int mines;
	int revealedFields;
	int flagsLeft;
	bool gameLost;
	bool gameWon;

	std::vector<std::vector<Field>> fields;

	void InitializeBoard(int width, int height, int mines) noexcept;
	void GenerateMines() noexcept;	
	void CalculateAdjacentMines() noexcept;
	void RevealAdjacentFields(int y, int x) noexcept;
	void RevealBombs() noexcept;

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

	Field& getField(int y, int x) noexcept;

	void RevealField(int y, int x) noexcept;
	void ToggleFlag(int y, int x) noexcept;

};

