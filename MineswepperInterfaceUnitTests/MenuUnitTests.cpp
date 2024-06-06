#include "gtest/gtest.h"
#include "../MineswepperMenuLibrary/Menu.h"

namespace MenuUnitTests
{
	TEST(Constructor, deafult)
	{
		EXPECT_EQ(1, 1);
		Menu menu(800, 600);
	}
}