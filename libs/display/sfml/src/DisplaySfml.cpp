/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** displaySfml.cpp
*/

#include "DisplaySfml.hpp"

namespace arcade::sfml {

    DisplaySfml::DisplaySfml()
    {
        this->init({ 800, 600 });
    }

    DisplaySfml::DisplaySfml(arcade::Size size)
    {
        this->init(size);
    }

    void DisplaySfml::init(arcade::Size size)
    {
        this->window_.create(
            sf::VideoMode(size.width * 20, size.height * 20), "Arcade", sf::Style::Titlebar | sf::Style::Close);
        this->windowSize_ = { size.width, size.height };
        this->window_.setFramerateLimit(60);

        if (!this->texture_.loadFromFile("assets/spriteSheet.png"))
            throw std::runtime_error("Error while loading texture");
        for (int i = 0; i < 10; i++) {
            this->sprite_[i].setTexture(this->texture_);
            this->sprite_[i].setTextureRect(sf::IntRect(i * 20, 20, 20, 20));
        }
        for (int i = 0; i < 26; i++) {
            this->sprite_[i + 10].setTexture(this->texture_);
            this->sprite_[i + 10].setTextureRect(sf::IntRect(i * 20, 0, 20, 20));
        }
        for (int i = 0; i < 27; i++) {
            this->sprite_[i + 36].setTexture(this->texture_);
            this->sprite_[i + 36].setTextureRect(sf::IntRect(i * 20, 40, 20, 20));
        }
        for (int i = 0; i < 26; i++) {
            this->sprite_[i + 63].setTexture(this->texture_);
            this->sprite_[i + 63].setTextureRect(sf::IntRect(i * 20, 60, 20, 20));
        }
        for (int i = 0; i < 26; i++) {
            this->sprite_[i + 89].setTexture(this->texture_);
            this->sprite_[i + 89].setTextureRect(sf::IntRect(i * 20, 80, 20, 20));
        }
    }

    arcade::Size DisplaySfml::getSize() const
    {
        return this->windowSize_;
    }

    void DisplaySfml::setSize(arcade::Size size)
    {
        this->windowSize_ = { size.width, size.height };
        this->window_.setSize(sf::Vector2u(size.width * 20, size.height * 20));
    }

    void DisplaySfml::draw(arcade::FrameBuffer &frameBuffer)
    {
        sf::Sprite *sprite = nullptr;
        arcade::Pixel *pixel = nullptr;
        sf::RectangleShape bg(sf::Vector2f(20, 20));

        for (size_t y = 0; y < frameBuffer.size.height; y++) {
            for (size_t x = 0; x < frameBuffer.size.width; x++) {
                pixel = &frameBuffer.pixels.at(x + (y * frameBuffer.size.width));
                if (!pixel->up)
                    continue;
                bg.setFillColor(sf::Color(pixel->bg[0] * 2, pixel->bg[1] * 2, pixel->bg[2] * 2));
                bg.setPosition(static_cast<float>(x * 20), static_cast<float>(y * 20));
                this->window_.draw(bg);
                sprite = &this->sprite_[pixel->c];
                sprite->setColor(sf::Color(pixel->fg[0] * 2, pixel->fg[1] * 2, pixel->fg[2] * 2));
                sprite->setPosition(static_cast<float>(x * 20), static_cast<float>(y * 20));
                this->window_.draw(*sprite);
            }
        }
    }

    void DisplaySfml::clear()
    {
        this->window_.clear();
    }

    void DisplaySfml::display()
    {
        this->window_.display();

        if (1000 / 60 > this->clock_.getElapsedTime().asMilliseconds()) {
            sf::sleep(sf::milliseconds(1000 / 60 - this->clock_.getElapsedTime().asMilliseconds()));
        }
        this->clock_.restart();
    }

    std::list<arcade::EVENT> DisplaySfml::pollEvents(std::list<arcade::EVENT> &events)
    {
        sf::Event event;

        while (this->window_.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                auto key = this->events_.find(event.key.code);
                if (key != this->events_.end())
                    events.push_back(key->second);
            } else if (event.type == sf::Event::Closed)
                events.push_back(arcade::EVENT::ARCADE_WIN_CLOSE);
        }
        return events;
    }

    DisplaySfml::~DisplaySfml()
    {
        this->window_.close();
    }

}// namespace arcade::sfml

extern "C" const arcade::LibType getType()
{
    return arcade::LibType::GRAPHICAL;
}

extern "C" std::unique_ptr<arcade::IDisplay> createLibrary(arcade::Size size)
{
    return std::make_unique<arcade::sfml::DisplaySfml>(size);
}
