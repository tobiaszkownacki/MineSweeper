#include "gtest/gtest.h"
#include "../MineswepperMenuLibrary/Menu.h"

namespace MenuUnitTests
{
	TEST(Constructor, default)
	{
		Menu menu(800, 600);
		EXPECT_EQ(menu.GetPressedItem(), 0);

	}

	TEST(HandleInput, Down)
	{
		Menu menu(800, 600);
		sf::Event event;
		EXPECT_EQ(menu.GetPressedItem(), 0);

		event.type = sf::Event::KeyPressed;
		event.key.code = sf::Keyboard::Down;
		menu.handleInput(event);
		EXPECT_EQ(menu.GetPressedItem(), 1);

		menu.handleInput(event);
		EXPECT_EQ(menu.GetPressedItem(), 2);

		menu.handleInput(event);
		EXPECT_EQ(menu.GetPressedItem(), 3);

		menu.handleInput(event);
		EXPECT_EQ(menu.GetPressedItem(), 3);

	}

	TEST(HandleInput, Up)
	{
		Menu menu(800, 600);
		sf::Event event;
		EXPECT_EQ(menu.GetPressedItem(), 0);

		event.type = sf::Event::KeyPressed;
		event.key.code = sf::Keyboard::Up;
		menu.handleInput(event);
		EXPECT_EQ(menu.GetPressedItem(), 0);

		menu.handleInput(event);
		EXPECT_EQ(menu.GetPressedItem(), 0);

		menu.MoveDown();
		menu.MoveDown();
		menu.MoveDown();
		EXPECT_EQ(menu.GetPressedItem(), 3);

		menu.handleInput(event);
		EXPECT_EQ(menu.GetPressedItem(), 2);

		menu.handleInput(event);
		EXPECT_EQ(menu.GetPressedItem(), 1);

		menu.handleInput(event);
		EXPECT_EQ(menu.GetPressedItem(), 0);

		menu.handleInput(event);
		EXPECT_EQ(menu.GetPressedItem(), 0);
	}

	TEST(InitializeText, ColorRedPosition0)
	{
		Menu menu(800, 600);
		sf::Text text;
		menu.initializeText(text, "Test", 12, sf::Color::Red, sf::Vector2f(0, 0));
		EXPECT_EQ(text.getString(), "Test");
		EXPECT_EQ(text.getCharacterSize(), 12);
		EXPECT_EQ(text.getFillColor(), sf::Color::Red);
		EXPECT_EQ(text.getPosition(), sf::Vector2f(0, 0));
	}

	TEST(InitializeText, ColorBlackPosition100)
	{
		Menu menu(800, 600);
		sf::Text text;
		menu.initializeText(text, "Test", 20, sf::Color::Black, sf::Vector2f(100, 100));
		EXPECT_EQ(text.getString(), "Test");
		EXPECT_EQ(text.getCharacterSize(), 20);
		EXPECT_EQ(text.getFillColor(), sf::Color::Black);
		EXPECT_EQ(text.getPosition(), sf::Vector2f(100, 100));
	}
}