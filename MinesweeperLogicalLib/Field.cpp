#include "Field.h"
#include <iostream>

Field::Field() noexcept
{
	isMine = false;
	isFlagged = false;
	isRevealed = false;
	adjacentMines = 0;
}

bool Field::IsMine() const noexcept
{
	return isMine;
}

void Field::SetMine() noexcept
{
	isMine = true;
}

bool Field::IsFlagged() const noexcept
{
	return isFlagged;
}

void Field::ToggleFlag() noexcept
{
	isFlagged = !isFlagged;
}

bool Field::IsRevealed() const noexcept
{
	return isRevealed;
}

void Field::Reveal() noexcept
{
	if (isRevealed = false) {
		isRevealed = true;
	}
}

int Field::getAdjacentMines() noexcept
{
	return adjacentMines;
}

void Field::setAdjacentMines(int mines) noexcept
{
	adjacentMines = mines;
}

void Field::incrementAdjacentMines() noexcept
{
	++adjacentMines;
}