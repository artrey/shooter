#ifndef SHOOTER_CONSTANTS_H
#define SHOOTER_CONSTANTS_H

#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

// TODO: make changeable class (for customizing settings from menu)
static const std::wstring GAME_TITLE = L"SPACE SHOOTER";
static const std::wstring NEW_GAME_OPTION = L"Новая игра";
static const std::wstring RESUME_GAME_OPTION = L"Продолжить";
static const std::wstring EXIT_OPTION = L"Выйти";
static const std::string RESOURCES_DIR = "resources";
static const std::string DEFAULT_FONT = "Cousine-Regular.ttf";
static const unsigned DEFAULT_FONT_SIZE = 32;
static const sf::Color MAIN_COLOR = sf::Color::White;
static const sf::Color OPTION_SELECTED_COLOR = sf::Color(250, 180, 2);
static const sf::Vector2f BULLET_SIZE = {8, 40};
static const sf::Color BULLET_COLOR = sf::Color::Green;
static const int SHIFT_POS = 10;

#endif //SHOOTER_CONSTANTS_H
