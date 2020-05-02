#include <iostream>
#include <filesystem>
#include "resource_manager.h"
#include "../constants.h"

std::unordered_map<std::string, sf::Font> shooter::ResourceManager::m_fonts = {};
fs::path shooter::ResourceManager::m_resourcesPath = {};

fs::path findResources(fs::path const& folder)
{
    for (auto const& entry : fs::directory_iterator(folder))
    {
        if (!entry.is_directory()) continue;
        if (entry.path().filename() == RESOURCES_DIR)
        {
            return entry.path();
        }
    }
    return {};
}

sf::Font const &shooter::ResourceManager::getFont(std::string const& name)
{
    if (!m_fonts.count(name))
    {
        if (m_resourcesPath.empty())
        {
            m_resourcesPath = findResources(fs::current_path());
            if (m_resourcesPath.empty())
            {
                m_resourcesPath = findResources(fs::current_path().parent_path());
            }

            if (m_resourcesPath.empty())
            {
                throw std::runtime_error("Resources folder not found!");
            }
        }

        try
        {
            if (!m_fonts[name].loadFromFile(m_resourcesPath / "fonts" / name))
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
