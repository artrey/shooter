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
    }
    return *m_manager;
}

std::string shooter::ResourcesManager::combineFontPath(const std::string& fontName)
{
    return (instance().m_resourcesPath / FONTS_RELATIVE_DIR / fontName).string();
}

std::string shooter::ResourcesManager::combineImagePath(const std::string& imageName)
{
    return (instance().m_resourcesPath / IMAGES_RELATIVE_DIR / imageName).string();
}

void shooter::ResourcesManager::init(std::string const& resourcesFolder)
{
    ResourcesManager& manager = instance();

    manager.m_resourcesPath = findFolder(fs::current_path(), resourcesFolder);
    if (manager.m_resourcesPath.empty())
    {
        manager.m_resourcesPath = findFolder(fs::current_path().parent_path(), resourcesFolder);
    }

    if (manager.m_resourcesPath.empty())
    {
        throw std::runtime_error("Resources folder '" + resourcesFolder + "' not found!");
    }
}

sf::Font const& shooter::ResourcesManager::getFont(std::string const& name)
{
    if (!instance().m_fonts.count(name))
    {
        if (!instance().m_fonts[name].loadFromFile(combineFontPath(name)))
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
        if (!instance().m_textures[name].loadFromFile(combineImagePath(name)))
        {
            throw std::runtime_error("Texture '" + name + "' not loaded!");
        }
    }
    return instance().m_textures[name];
}
