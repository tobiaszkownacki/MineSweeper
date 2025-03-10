#include "../MineswepperInterfaceLibrary/Menu.h"
#include "../MineswepperInterfaceLibrary/CustomSettings.h"
#include "../MineswepperInterfaceLibrary/Game.h"
#include <iostream>

enum class GameState {
	Menu,
	CustomSettings,
    Game
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper Menu", sf::Style::Titlebar | sf::Style::Close);
    Menu menu(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    CustomSettings customSettings(window.getSize().x, window.getSize().y);
    Game * game = nullptr;
    GameState currentState = GameState::Menu;
    sf::Color backgroundColor = sf::Color(237, 232, 215);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (currentState)
            {
                case GameState::Menu:
                    if (event.type == sf::Event::KeyPressed)
                    {
                        menu.handleInput(event);
                        switch (event.key.code)
                        {
                            case sf::Keyboard::Enter:
                            {
                                int selectedItem = menu.GetPressedItem();
                                switch (selectedItem)
                                {
                                case 0:
                                    game = new Game(9, 9, 10, window);
                                    currentState = GameState::Game;
                                    break;
                                case 1:
                                    game = new Game(16, 16, 40, window);
                                    currentState = GameState::Game;
                                    break;
                                case 2:
                                    game = new Game(30, 16, 99, window);
                                    currentState = GameState::Game;
                                    break;
                                case 3:
                                    currentState = GameState::CustomSettings;
                                    break;
                                }
                                break;
                            }  
                            case sf::Keyboard::Escape:
								window.close();
								break;
                        }
                    }
                    break;
                case GameState::CustomSettings:
                    customSettings.handleInput(event);
                    if (event.type == sf::Event::KeyPressed)
                    {
                        switch (event.key.code)
                        {
                            case sf::Keyboard::Enter:
                            {
                                int customWidth = customSettings.getWidth();
                                int customHeight = customSettings.getHeight();
                                int customMines = customSettings.getMines();
                                if (customMines < customWidth * customHeight)
                                {
                                    game = new Game(customWidth, customHeight, customMines, window);
                                    currentState = GameState::Game;
                                }
                                break;
                            }
                            case sf::Keyboard::Escape:
                                currentState = GameState::Menu;
                                break;
                        }
                    }
					break;
                case GameState::Game:
                    game->handleMouseEvent(event);
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    {
                        delete game;
                        game = nullptr;
                        currentState = GameState::Menu;
                        window.setSize(sf::Vector2u(800, 600));
                        sf::View view(sf::FloatRect(0, 0, 800, 600));
                        window.setView(view);
                    }
					break;
            }
            
        }
        if(currentState == GameState::Game)
            backgroundColor = sf::Color(192, 192, 192);
        else
            backgroundColor = sf::Color(237, 232, 215);
        window.clear(backgroundColor);
        switch (currentState)
        {
            case GameState::Menu:
                menu.draw(window);
			    break;
            case GameState::CustomSettings:
			    customSettings.draw(window);
                break;
            case GameState::Game:
				game->draw();
                break;
        }
        window.display();
    }
    return 0;
}