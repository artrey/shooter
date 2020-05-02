#include <iostream>
#include <filesystem>
#include "fs.h"
#include "resources_manager.h"
#include "../constants.h"

std::unique_ptr<shooter::ResourcesManager> shooter::ResourcesManager::m_manager = {};

shooter::ResourcesManager::ResourcesManager() = default;

shooter::ResourcesManager& shooter::ResourcesManager::instance()
{
    if (!m_manager)
    {
        m_manager.reset(new ResourcesManager);

        m_manager->m_resourcesPath = findFolder(fs::current_path(), RESOURCES_DIR);
        if (m_manager->m_resourcesPath.empty())
        {
            m_manager->m_resourcesPath = findFolder(fs::current_path().parent_path(), RESOURCES_DIR);
        }

        if (m_manager->m_resourcesPath.empty())
        {
            m_manager.reset();  // removing invalid manager
            throw std::runtime_error("Resources folder '" + RESOURCES_DIR + "' not found!");
        }
    }
    return *m_manager;
}

sf::Font const& shooter::ResourcesManager::getFont(std::string const& name)
{
    if (!instance().m_fonts.count(name))
    {
        if (!instance().m_fonts[name].loadFromFile(instance().m_resourcesPath / "fonts" / name))
        {
            throw std::runtime_error("Font '" + name + "' not loaded!");
        }
    }
    return instance().m_fonts[name];
}

sf::Font const& shooter::ResourcesManager::getDefaultFont()
{
    return getFont(DEFAULT_FONT);
}

sf::Texture const& shooter::ResourcesManager::getTexture(std::string const& name)
{
    if (!instance().m_textures.count(name))
    {
        if (!instance().m_textures[name].loadFromFile(instance().m_resourcesPath / "images" / name))
        {
            throw std::runtime_error("Texture '" + name + "' not loaded!");
        }
    }
    return instance().m_textures[name];
}
