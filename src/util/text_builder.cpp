#include "text_builder.h"

#include <utility>
#include "resource_manager.h"
#include "../constants.h"

shooter::TextBuilder::TextBuilder() = default;

shooter::TextBuilder& shooter::TextBuilder::setDefaultParameters()
{
    return setFont(DEFAULT_FONT).setSize(DEFAULT_FONT_SIZE).setColor(MAIN_COLOR);
}

shooter::TextBuilder& shooter::TextBuilder::setSize(unsigned size)
{
    m_text.setCharacterSize(size);
    return *this;
}

shooter::TextBuilder& shooter::TextBuilder::setFont(std::string const& fontName)
{
    m_text.setFont(ResourceManager::getFont(fontName));
    return *this;
}

shooter::TextBuilder& shooter::TextBuilder::setText(sf::String const& text)
{
    m_text.setString(text);
    return *this;
}

shooter::TextBuilder& shooter::TextBuilder::setColor(const sf::Color& color)
{
    m_text.setFillColor(color);
    return *this;
}

shooter::TextBuilder shooter::TextBuilder::defaultParameters()
{
    return TextBuilder().setDefaultParameters();
}

sf::Text shooter::TextBuilder::build() const
{
    return m_text;
}
