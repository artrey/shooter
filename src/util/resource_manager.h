#ifndef SHOOTER_RESOURCE_MANAGER_H
#define SHOOTER_RESOURCE_MANAGER_H

#include <filesystem>
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

namespace shooter
{
    class ResourceManager
    {
    private:
        static std::unordered_map<std::string, sf::Font> m_fonts;
        static fs::path m_resourcesPath;

    public:
        static sf::Font const& getFont(std::string const& name);
        static sf::Font const& getDefaultFont();
    };
}

#endif //SHOOTER_RESOURCE_MANAGER_H
