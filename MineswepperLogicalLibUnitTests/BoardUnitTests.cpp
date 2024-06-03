#include "gtest/gtest.h"
#include "../MinesweeperLogicalLib/Board.h"

class MockBoard : public Board
{

	void GenerateMines(std::vector<std::vector<bool>> bombs) noexcept
	{
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				if (bombs[y][x])
					fields[y][x].SetMine();
			}
		}
	}


public:
    MockBoard(int width, int height, int mines, std::vector<std::vector<bool>> wherebomb) noexcept 
		: Board(width, height, mines)
    {
					InitializeBoard(width, height, mines);  // to zero out the fields
					GenerateMines(wherebomb);
					CalculateAdjacentMines();
    }
};

namespace MockBoardUnitTest
{
	TEST(Constructor, OneBombInTheMiddle)
	{
		std::vector<std::vector<bool>> wherebomb = {
			{false, false, false},
			{false, true, false},
			{false, false, false}
		};
		MockBoard board(3, 3, 1, wherebomb);


		// check if the board is initialized correctly
		EXPECT_EQ(3, board.getWidth());
		EXPECT_EQ(3, board.getHeight());
		EXPECT_EQ(1, board.getMines());
		EXPECT_EQ(0, board.getRevealedFields());
		EXPECT_EQ(1, board.getFlagsLeft());
		EXPECT_FALSE(board.isGameLost());
		EXPECT_FALSE(board.isGameWon());

		// check if the bombs are placed correctly
		EXPECT_FALSE(board.getField(0, 0).IsMine());
		EXPECT_FALSE(board.getField(0, 1).IsMine());
		EXPECT_FALSE(board.getField(0, 2).IsMine());
		EXPECT_FALSE(board.getField(1, 0).IsMine());
		EXPECT_TRUE(board.getField(1, 1).IsMine());
		EXPECT_FALSE(board.getField(1, 2).IsMine());
		EXPECT_FALSE(board.getField(2, 0).IsMine());
		EXPECT_FALSE(board.getField(2, 1).IsMine());
		EXPECT_FALSE(board.getField(2, 2).IsMine());

		// check if the adjacent mines are calculated correctly
		EXPECT_EQ(1, board.getField(0, 0).getAdjacentMines());
		EXPECT_EQ(1, board.getField(0, 1).getAdjacentMines());
		EXPECT_EQ(1, board.getField(0, 2).getAdjacentMines());
		EXPECT_EQ(1, board.getField(1, 0).getAdjacentMines());
		EXPECT_EQ(0, board.getField(1, 1).getAdjacentMines());
		EXPECT_EQ(1, board.getField(1, 2).getAdjacentMines());
		EXPECT_EQ(1, board.getField(2, 0).getAdjacentMines());
		EXPECT_EQ(1, board.getField(2, 1).getAdjacentMines());
		EXPECT_EQ(1, board.getField(2, 2).getAdjacentMines());

	}

	TEST(Constructor, TwoBombsInTheMiddle)
	{
		std::vector<std::vector<bool>> wherebomb = {
			{false, false, false},
			{false, true, false},
			{false, true, false}
		};
		MockBoard board(3, 3, 2, wherebomb);

		// check if the bombs are placed correctly
		EXPECT_FALSE(board.getField(0, 0).IsMine());
		EXPECT_FALSE(board.getField(0, 1).IsMine());
		EXPECT_FALSE(board.getField(0, 2).IsMine());
		EXPECT_FALSE(board.getField(1, 0).IsMine());
		EXPECT_TRUE(board.getField(1, 1).IsMine());
		EXPECT_FALSE(board.getField(1, 2).IsMine());
		EXPECT_FALSE(board.getField(2, 0).IsMine());
		EXPECT_TRUE(board.getField(2, 1).IsMine());
		EXPECT_FALSE(board.getField(2, 2).IsMine());

		// check if the adjacent mines are calculated correctly
		EXPECT_EQ(1, board.getField(0, 0).getAdjacentMines());
		EXPECT_EQ(1, board.getField(0, 1).getAdjacentMines());
		EXPECT_EQ(1, board.getField(0, 2).getAdjacentMines());
		EXPECT_EQ(2, board.getField(1, 0).getAdjacentMines());
		EXPECT_EQ(0, board.getField(1, 1).getAdjacentMines());
		EXPECT_EQ(2, board.getField(1, 2).getAdjacentMines());
		EXPECT_EQ(2, board.getField(2, 0).getAdjacentMines());
		EXPECT_EQ(0, board.getField(2, 1).getAdjacentMines());
		EXPECT_EQ(2, board.getField(2, 2).getAdjacentMines());
	}

	TEST(Constructor, ThreeBombsInTheBoard)
	{
		std::vector<std::vector<bool>> wherebomb = {
		{false, false, false, true},
		{false, true, false, false},
		{false, true, false, false}
		};
		MockBoard board(4, 3, 3, wherebomb);

		// check if the bombs are placed correctly
		EXPECT_FALSE(board.getField(0, 0).IsMine());
		EXPECT_FALSE(board.getField(0, 1).IsMine());
		EXPECT_FALSE(board.getField(0, 2).IsMine());
		EXPECT_TRUE(board.getField(0, 3).IsMine());
		EXPECT_FALSE(board.getField(1, 0).IsMine());
		EXPECT_TRUE(board.getField(1, 1).IsMine());
		EXPECT_FALSE(board.getField(1, 2).IsMine());
		EXPECT_FALSE(board.getField(1, 3).IsMine());
		EXPECT_FALSE(board.getField(2, 0).IsMine());
		EXPECT_TRUE(board.getField(2, 1).IsMine());
		EXPECT_FALSE(board.getField(2, 2).IsMine());
		EXPECT_FALSE(board.getField(2, 3).IsMine());

		// check if the adjacent mines are calculated correctly
		EXPECT_EQ(1, board.getField(0, 0).getAdjacentMines());
		EXPECT_EQ(1, board.getField(0, 1).getAdjacentMines());
		EXPECT_EQ(2, board.getField(0, 2).getAdjacentMines());
		EXPECT_EQ(0, board.getField(0, 3).getAdjacentMines());
		EXPECT_EQ(2, board.getField(1, 0).getAdjacentMines());
		EXPECT_EQ(0, board.getField(1, 1).getAdjacentMines());
		EXPECT_EQ(3, board.getField(1, 2).getAdjacentMines());
		EXPECT_EQ(1, board.getField(1, 3).getAdjacentMines());
		EXPECT_EQ(2, board.getField(2, 0).getAdjacentMines());
		EXPECT_EQ(0, board.getField(2, 1).getAdjacentMines());
		EXPECT_EQ(2, board.getField(2, 2).getAdjacentMines());
		EXPECT_EQ(0, board.getField(2, 3).getAdjacentMines());
	}

	TEST(ToggleFlag, retoggleField)
	{
		std::vector<std::vector<bool>> wherebomb = {
			{false, false, false},
			{false, true, false},
			{false, true, false}
		};
		MockBoard board(3, 3, 2, wherebomb);

		EXPECT_FALSE(board.getField(0, 0).IsFlagged());
		board.ToggleFlag(0, 0);
		EXPECT_TRUE(board.getField(0, 0).IsFlagged());
		board.ToggleFlag(0, 0);
		EXPECT_FALSE(board.getField(0, 0).IsFlagged());

		EXPECT_FALSE(board.getField(1, 1).IsFlagged());
		board.ToggleFlag(1, 1);
		EXPECT_TRUE(board.getField(1, 1).IsFlagged());
		board.ToggleFlag(1, 1);
		EXPECT_FALSE(board.getField(1, 1).IsFlagged());
	}

	TEST(ToggleFlag, tryToSetMoreFlagsThatAreBombs)
	{
		std::vector<std::vector<bool>> wherebomb = {
			{false, false, false},
			{false, true, false},
			{false, true, false}
		};
		MockBoard board(3, 3, 2, wherebomb);

		EXPECT_EQ(2, board.getFlagsLeft());
		board.ToggleFlag(0, 0);
		EXPECT_EQ(1, board.getFlagsLeft());
		board.ToggleFlag(0, 1);
		EXPECT_EQ(0, board.getFlagsLeft());
		board.ToggleFlag(0, 2);
		EXPECT_EQ(0, board.getFlagsLeft());
	}

	TEST(RevealField, revealBombGameOver)
	{
		std::vector<std::vector<bool>> wherebomb = {
			{false, false, false},
			{false, true, false},
			{false, true, false}
		};
		MockBoard board(3, 3, 2, wherebomb);

		EXPECT_FALSE(board.isGameLost());
		board.RevealField(1, 1);
		EXPECT_TRUE(board.isGameLost());
		EXPECT_TRUE(board.getField(2, 1).IsRevealed());
	}

	TEST(RevealField, WinTheGame)
	{
		std::vector<std::vector<bool>> wherebomb = {
			{false, false, false},
			{false, true, false},
			{false, true, false}
		};
		MockBoard board(3, 3, 2, wherebomb);

		EXPECT_FALSE(board.isGameWon());
		board.RevealField(0, 0);
		EXPECT_FALSE(board.isGameWon());
		board.RevealField(0, 1);
		EXPECT_FALSE(board.isGameWon());
		board.RevealField(0, 2);
		EXPECT_FALSE(board.isGameWon());
		board.RevealField(1, 0);
		EXPECT_FALSE(board.isGameWon());
		board.RevealField(1, 2);
		EXPECT_FALSE(board.isGameWon());
		board.RevealField(2, 0);
		EXPECT_FALSE(board.isGameWon());
		board.RevealField(2, 2);
		EXPECT_TRUE(board.isGameWon());
	}

	TEST(RevealField, RevealAdjacentFields)
	{
		std::vector<std::vector<bool>> wherebomb = {
			{false, false, false},
			{false, false, false},
			{false, true, false}
		};
		MockBoard board(3, 3, 2, wherebomb);

		EXPECT_EQ(0, board.getRevealedFields());
		board.RevealField(0, 0);

		EXPECT_EQ(6, board.getRevealedFields());
		EXPECT_TRUE(board.getField(0, 0).IsRevealed());
		EXPECT_TRUE(board.getField(0, 1).IsRevealed());
		EXPECT_TRUE(board.getField(0, 2).IsRevealed());
		EXPECT_TRUE(board.getField(1, 0).IsRevealed());
		EXPECT_TRUE(board.getField(1, 1).IsRevealed());
		EXPECT_TRUE(board.getField(1, 2).IsRevealed());

		board.RevealField(2, 2);
		EXPECT_EQ(7, board.getRevealedFields());
		board.RevealField(2, 0);
		EXPECT_EQ(8, board.getRevealedFields());
		EXPECT_TRUE(board.isGameWon());
	}

	TEST(RevealField, RevealAdjacentFieldsTwoTimes)
	{
		std::vector<std::vector<bool>> wherebomb = {
			{false, false, false, false},
			{false, false, true, false},
			{false, false, false, false},
			{false, true, false, false}
		};
		MockBoard board(4, 4, 3, wherebomb);

		EXPECT_EQ(0, board.getRevealedFields());
		board.RevealField(3, 3);

		EXPECT_EQ(4, board.getRevealedFields());
		EXPECT_TRUE(board.getField(3, 3).IsRevealed());
		EXPECT_TRUE(board.getField(3, 2).IsRevealed());
		EXPECT_TRUE(board.getField(2, 3).IsRevealed());
		EXPECT_TRUE(board.getField(2, 2).IsRevealed());

		board.RevealField(0, 0);
		EXPECT_EQ(10, board.getRevealedFields());
		EXPECT_TRUE(board.getField(0, 0).IsRevealed());
		EXPECT_TRUE(board.getField(0, 1).IsRevealed());
		EXPECT_TRUE(board.getField(1, 0).IsRevealed());
		EXPECT_TRUE(board.getField(1, 1).IsRevealed());
		EXPECT_TRUE(board.getField(2, 0).IsRevealed());
		EXPECT_TRUE(board.getField(2, 1).IsRevealed());
	}


}