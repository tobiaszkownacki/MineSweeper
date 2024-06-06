#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "CustomSettings.h"
#include <iostream>

enum class GameState {
	Menu,
	CustomSettings
    // TODO Game
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper Menu", sf::Style::Titlebar | sf::Style::Close);
    Menu menu(window.getSize().x, window.getSize().y);
    CustomSettings customSettings(window.getSize().x, window.getSize().y);
    GameState currentState = GameState::Menu;
    sf::Color backgroundColor = sf::Color(237, 232, 215);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
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
                                    std::cout << "Easy | Width: 9 | Height: 9 | Bombs: 10" << std::endl;
                                    // TODO game = new Game(9, 9, 10);
                                    // TODO currentState = GameState::Game;
                                    break;
                                case 1:
                                    std::cout << "Medium | Width: 16 | Height: 16 | Bombs: 40" << std::endl;
                                    // TODO game = new Game(16, 16, 40);
                                    // TODO currentState = GameState::Game;
                                    break;
                                case 2:
                                    std::cout << "Extreme | Width: 30 | Height: 16 | Bombs: 99" << std::endl;
                                    // TODO game = new Game(30, 16, 99);
                                    // TODO currentState = GameState::Game;
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
                                    std::cout << "Custom | Width: " << customWidth << " | Height: " << customHeight << " | Bombs: " << customMines << std::endl;
                                    // TODO game = new Game(customWidth, customHeight, customMines);
                                    // TODO currentState = GameState::Game;
                                }
                                else
                                {
                                    customSettings.setErrorMessage("Error: Number of mines must be less than the total number of cells.");
                                }
                                break;
                            }
                            case sf::Keyboard::Escape:
                                currentState = GameState::Menu;
                                break;
                        }
                    }
					break;
                // TODO case GameState::Game:
                    // TODO Implement this!
            }
            
        }
        window.clear(backgroundColor);
        switch (currentState)
        {
            case GameState::Menu:
                menu.draw(window);
			    break;
            case GameState::CustomSettings:
			    customSettings.draw(window);
                break;
            // TODO case GameState::Game:
				// TODO Implement this!
        }
        window.display();
    }
    return 0;
}