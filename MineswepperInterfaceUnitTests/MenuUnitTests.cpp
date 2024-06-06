#include "gtest/gtest.h"
#include "../ConsoleApp/Menu.h"

namespace MenuUnitTests
{
	TEST(Constructor, deafult)
	{



		Menu menu(800, 600);
		EXPECT_EQ(menu.GetPressedItem(), 0);
	}
}