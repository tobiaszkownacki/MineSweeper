#include "gtest/gtest.h"
#include "../MinesweeperLogicalLib/Field.h"

namespace FieldUnitTests
{
	TEST(FieldIsMine, typical)
	{
		Field field;
		EXPECT_FALSE(field.IsMine());
		field.SetMine();
		EXPECT_TRUE(field.IsMine());
	}

	TEST(FieldIsFlagged, typical)
	{
		Field field;
		EXPECT_FALSE(field.IsFlagged());
		field.ToggleFlag();
		EXPECT_TRUE(field.IsFlagged());
		field.ToggleFlag();
		EXPECT_FALSE(field.IsFlagged());
	}

	TEST(FieldIsRevealed, typical)
	{
		Field field;
		EXPECT_FALSE(field.IsRevealed());
		field.Reveal();
		EXPECT_TRUE(field.IsRevealed());
	}

	TEST(FieldAdjacentMines, typical)
	{
		Field field;
		EXPECT_EQ(0, field.getAdjacentMines());
		field.setAdjacentMines(5);
		EXPECT_EQ(5, field.getAdjacentMines());
		field.incrementAdjacentMines();
		EXPECT_EQ(6, field.getAdjacentMines());
	}

	TEST(FieldIsFlagged, multipleToggles)
	{
		Field field;
		EXPECT_FALSE(field.IsFlagged());
		field.ToggleFlag();
		EXPECT_TRUE(field.IsFlagged());
		field.ToggleFlag();
		EXPECT_FALSE(field.IsFlagged());
		field.ToggleFlag();
		EXPECT_TRUE(field.IsFlagged());
	}
}