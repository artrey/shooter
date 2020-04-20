#include "view.h"

#include <iostream>
#include <utility>

shooter::View::View(std::string title)
    : m_title{std::move(title)}
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
