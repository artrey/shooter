#ifndef SHOOTER_TEXT_BUILDER_H
#define SHOOTER_TEXT_BUILDER_H

#include <SFML/Graphics/Text.hpp>

namespace shooter
{
    class TextBuilder
    {
    private:
        sf::Text m_text;

    public:
        TextBuilder();

        TextBuilder& setDefaultParameters();
        TextBuilder& setSize(unsigned size);
        TextBuilder& setFont(std::string const& fontName);
        TextBuilder& setText(sf::String const& text);
        TextBuilder& setColor(sf::Color const& color);

        static TextBuilder defaultParameters();
        [[nodiscard]] sf::Text build() const;
    };
}

#endif //SHOOTER_TEXT_BUILDER_H
