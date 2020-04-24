#include <iostream>
#include "resource_manager.h"
#include "constants.h"

std::unordered_map<std::string, sf::Font> shooter::ResourceManager::m_fonts = {};

sf::Font const &shooter::ResourceManager::getFont(std::string const& name)
{
    if (!m_fonts.count(name))
    {
        try
        {
            if (!m_fonts[name].loadFromFile(name))
            {
                throw std::runtime_error("Font " + name + " not loaded!");
            }
        }
        catch (std::exception const& ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }
    return m_fonts[name];
}

sf::Font const &shooter::ResourceManager::getDefaultFont()
{
    return getFont(DEFAULT_FONT);
}
