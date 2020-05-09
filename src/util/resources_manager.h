#ifndef SHOOTER_RESOURCES_MANAGER_H
#define SHOOTER_RESOURCES_MANAGER_H

#include <filesystem>
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

namespace shooter
{
    class ResourcesManager
    {
    private:
        fs::path m_resourcesPath;
        std::unordered_map<std::string, sf::Font> m_fonts;
        std::unordered_map<std::string, sf::Texture> m_textures;

    private:
        ResourcesManager();
        static ResourcesManager& instance();
        static std::unique_ptr<ResourcesManager> m_manager;

    private:
        [[nodiscard]] static std::string combineFontPath(std::string const& fontName);
        [[nodiscard]] static std::string combineImagePath(std::string const& imageName);

    public:
        static void init(std::string const& resourcesFolder);

        static sf::Font const& getFont(std::string const& name);

        static sf::Font const& getDefaultFont();

        static sf::Texture const& getTexture(std::string const& name);
    };
}

#endif //SHOOTER_RESOURCES_MANAGER_H
