#include "gtest/gtest.h"
#include "../MineswepperInterfaceLibrary/CustomSettings.h"

namespace CustomSettingsUnitTests
{
	TEST(Constructor, typical)
	{
		CustomSettings customMenu(800, 600);
		EXPECT_EQ(customMenu.getHeight(), 9);
		EXPECT_EQ(customMenu.getWidth(), 9);
		EXPECT_EQ(customMenu.getMines(), 10);
	}

	TEST(HandleInput, IncreaseAndDownWidth)
	{
		CustomSettings customMenu(800, 600);
		sf::Event event;
		EXPECT_EQ(customMenu.getWidth(), 9);

		event.type = sf::Event::KeyPressed;
		event.key.code = sf::Keyboard::Right;
		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getWidth(), 10);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getWidth(), 11);

		event.key.code = sf::Keyboard::Left;
		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getWidth(), 10);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getWidth(), 9);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getWidth(), 8);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getWidth(), 8);
	}

	TEST(HandleInput, IncreaseAndDownHeight)
	{
		CustomSettings customMenu(800, 600);
		sf::Event event;

		event.type = sf::Event::KeyPressed;
		event.key.code = sf::Keyboard::Down;
		customMenu.handleInput(event);

		EXPECT_EQ(customMenu.getHeight(), 9);

		event.key.code = sf::Keyboard::Right;
		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getHeight(), 10);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getHeight(), 11);

		event.key.code = sf::Keyboard::Left;
		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getHeight(), 10);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getHeight(), 9);

		customMenu.handleInput(event);
		customMenu.handleInput(event);
		customMenu.handleInput(event);
		customMenu.handleInput(event);
		customMenu.handleInput(event);
		customMenu.handleInput(event);
		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getHeight(), 2);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getHeight(), 1);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getHeight(), 1);

	}

	TEST(HandleInput, IncreaseAndDownMines)
	{
		CustomSettings customMenu(800, 600);
		sf::Event event;

		event.type = sf::Event::KeyPressed;
		event.key.code = sf::Keyboard::Down;
		customMenu.handleInput(event);
		customMenu.handleInput(event);

		EXPECT_EQ(customMenu.getMines(), 10);

		event.key.code = sf::Keyboard::Right;
		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getMines(), 11);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getMines(), 12);

		event.key.code = sf::Keyboard::Left;
		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getMines(), 11);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getMines(), 10);

		customMenu.handleInput(event);
		customMenu.handleInput(event);
		customMenu.handleInput(event);
		customMenu.handleInput(event);
		customMenu.handleInput(event);
		customMenu.handleInput(event);
		customMenu.handleInput(event);
		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getMines(), 2);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getMines(), 1);

		customMenu.handleInput(event);
		EXPECT_EQ(customMenu.getMines(), 1);
	}
}