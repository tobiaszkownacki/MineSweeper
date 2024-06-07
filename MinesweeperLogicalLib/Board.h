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

	bool firstClick;

	std::vector<std::vector<Field>> fields;

	void GenerateMines() noexcept;	
	void CalculateAdjacentMines() noexcept;
	void RevealAdjacentFields(int y, int x) noexcept;
	void RevealBombs() noexcept;
	void TransportFirstClickedMine(int y, int x) noexcept;

public:
	Board(int width, int height, int mines) noexcept;
	~Board() noexcept = default;

	int getWidth() const noexcept;
	int getHeight() const noexcept;
	int getMines() const noexcept;
	int getRevealedFields() const noexcept;
	int getFlagsLeft() const noexcept;

	bool isGameLost() const noexcept;
	bool isGameWon() const noexcept;

	Field& getField(int y, int x) noexcept;

	void RevealField(int y, int x) noexcept;
	void ToggleFlag(int y, int x) noexcept;

};

