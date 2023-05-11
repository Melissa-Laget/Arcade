/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** DisplaySfml.hpp
*/

#pragma once

#include "IDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

namespace arcade::sfml {

    class DisplaySfml : public arcade::IDisplay
    {
        public:
        DisplaySfml();
        DisplaySfml(arcade::Size size);
        DisplaySfml(const DisplaySfml &) = delete;
        DisplaySfml(DisplaySfml &&) = delete;
        DisplaySfml &operator=(const DisplaySfml &) = delete;
        DisplaySfml &operator=(DisplaySfml &&) = delete;
        ~DisplaySfml();

        void init(arcade::Size size);

        arcade::Size getSize() const override;
        void setSize(arcade::Size size);

        std::list<arcade::EVENT> pollEvents(std::list<arcade::EVENT> &events) override;

        void draw(arcade::FrameBuffer &frameBuffer) override;
        void clear() override;
        void display() override;

        private:
        sf::RenderWindow window_;
        arcade::Size windowSize_;

        std::array<sf::Sprite, 128> sprite_;
        sf::Texture texture_;

        sf::Clock clock_;

        const std::unordered_map<sf::Keyboard::Key, arcade::EVENT> events_ = {
            { sf::Keyboard::Key::A, arcade::EVENT::ARCADE_KEY_A },
            { sf::Keyboard::Key::B, arcade::EVENT::ARCADE_KEY_B },
            { sf::Keyboard::Key::C, arcade::EVENT::ARCADE_KEY_C },
            { sf::Keyboard::Key::D, arcade::EVENT::ARCADE_KEY_D },
            { sf::Keyboard::Key::E, arcade::EVENT::ARCADE_KEY_E },
            { sf::Keyboard::Key::F, arcade::EVENT::ARCADE_KEY_F },
            { sf::Keyboard::Key::G, arcade::EVENT::ARCADE_KEY_G },
            { sf::Keyboard::Key::H, arcade::EVENT::ARCADE_KEY_H },
            { sf::Keyboard::Key::I, arcade::EVENT::ARCADE_KEY_I },
            { sf::Keyboard::Key::J, arcade::EVENT::ARCADE_KEY_J },
            { sf::Keyboard::Key::K, arcade::EVENT::ARCADE_KEY_K },
            { sf::Keyboard::Key::L, arcade::EVENT::ARCADE_KEY_L },
            { sf::Keyboard::Key::M, arcade::EVENT::ARCADE_KEY_M },
            { sf::Keyboard::Key::N, arcade::EVENT::ARCADE_KEY_N },
            { sf::Keyboard::Key::O, arcade::EVENT::ARCADE_KEY_O },
            { sf::Keyboard::Key::P, arcade::EVENT::ARCADE_KEY_P },
            { sf::Keyboard::Key::Q, arcade::EVENT::ARCADE_KEY_Q },
            { sf::Keyboard::Key::R, arcade::EVENT::ARCADE_KEY_R },
            { sf::Keyboard::Key::S, arcade::EVENT::ARCADE_KEY_S },
            { sf::Keyboard::Key::T, arcade::EVENT::ARCADE_KEY_T },
            { sf::Keyboard::Key::U, arcade::EVENT::ARCADE_KEY_U },
            { sf::Keyboard::Key::V, arcade::EVENT::ARCADE_KEY_V },
            { sf::Keyboard::Key::W, arcade::EVENT::ARCADE_KEY_W },
            { sf::Keyboard::Key::X, arcade::EVENT::ARCADE_KEY_X },
            { sf::Keyboard::Key::Y, arcade::EVENT::ARCADE_KEY_Y },
            { sf::Keyboard::Key::Z, arcade::EVENT::ARCADE_KEY_Z },
            { sf::Keyboard::Key::Num1, arcade::EVENT::ARCADE_KEY_1 },
            { sf::Keyboard::Key::Num2, arcade::EVENT::ARCADE_KEY_2 },
            { sf::Keyboard::Key::Num3, arcade::EVENT::ARCADE_KEY_3 },
            { sf::Keyboard::Key::Num4, arcade::EVENT::ARCADE_KEY_4 },
            { sf::Keyboard::Key::Num5, arcade::EVENT::ARCADE_KEY_5 },
            { sf::Keyboard::Key::Num6, arcade::EVENT::ARCADE_KEY_6 },
            { sf::Keyboard::Key::Num7, arcade::EVENT::ARCADE_KEY_7 },
            { sf::Keyboard::Key::Num8, arcade::EVENT::ARCADE_KEY_8 },
            { sf::Keyboard::Key::Num9, arcade::EVENT::ARCADE_KEY_9 },
            { sf::Keyboard::Key::Num0, arcade::EVENT::ARCADE_KEY_0 },
            { sf::Keyboard::Key::Right, arcade::EVENT::ARCADE_KEY_RIGHT },
            { sf::Keyboard::Key::Left, arcade::EVENT::ARCADE_KEY_LEFT },
            { sf::Keyboard::Key::Up, arcade::EVENT::ARCADE_KEY_UP },
            { sf::Keyboard::Key::Down, arcade::EVENT::ARCADE_KEY_DOWN },
            { sf::Keyboard::Key::Space, arcade::EVENT::ARCADE_KEY_SPACE },
            { sf::Keyboard::Key::Enter, arcade::EVENT::ARCADE_KEY_ENTER },
            { sf::Keyboard::Key::Escape, arcade::EVENT::ARCADE_KEY_ESC },
            { sf::Keyboard::Key::Tab, arcade::EVENT::ARCADE_KEY_TAB },
            { sf::Keyboard::Key::LShift, arcade::EVENT::ARCADE_KEY_SHIFT },
            { sf::Keyboard::Key::LControl, arcade::EVENT::ARCADE_KEY_CTRL },
            { sf::Keyboard::Key::LAlt, arcade::EVENT::ARCADE_KEY_ALT },
            { sf::Keyboard::Key::F1, arcade::EVENT::ARCADE_SYS_MENU },
            { sf::Keyboard::Key::F2, arcade::EVENT::ARCADE_SYS_NEXT_DISPLAY },
            { sf::Keyboard::Key::F3, arcade::EVENT::ARCADE_SYS_PREV_DISPLAY },
            { sf::Keyboard::Key::F4, arcade::EVENT::ARCADE_SYS_PREV_GAME },
            { sf::Keyboard::Key::F5, arcade::EVENT::ARCADE_SYS_NEXT_GAME },
            { sf::Keyboard::Key::F8, arcade::EVENT::ARCADE_SYS_EXIT },
            { sf::Keyboard::Key::F6, arcade::EVENT::ARCADE_SYS_RESTART },
            { sf::Keyboard::Key::F7, arcade::EVENT::ARCADE_WIN_CLOSE },
        };
    };
}// namespace arcade::sfml
