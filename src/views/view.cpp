#include "view.h"

#include <iostream>

shooter::View::View(std::string_view title, Game& game)
    : m_title{title}, m_game{game}
{
}

shooter::View::~View()
{
    std::cout << "Destroyed view " << title() << std::endl;
}

std::string shooter::View::title() const
{
    return m_title;
}
