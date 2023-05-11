/*
** EPITECH PROJECT, 2023
** snake
** File description:
** snake.hpp
*/

#pragma once

#include "IGame.hpp"
#include <array>
#include <experimental/random>
#include <filesystem>
#include <list>
#include <ncurses.h>
#include <unordered_map>

namespace arcade::menu {
    enum TextAction { LIBGAME, LIBGRAPH, REFRESH, RETURN };

    struct Text
    {
        std::string text;
        size_t x;
        size_t y;
        arcade::STATUS status;
        arcade::menu::TextAction action;
    };

    class Menu : public IGame
    {
        public:
        Menu();
        Menu(const Menu &) = delete;
        Menu(Menu &&) = delete;
        Menu &operator=(const Menu &) = delete;
        Menu &operator=(Menu &&) = delete;
        ~Menu() override = default;

        arcade::STATUS run(std::list<arcade::EVENT> &events) override;
        arcade::FrameBuffer &getFrameBuffer() override;
        std::pair<arcade::OPTIONS, std::string> option() override;
        arcade::Size getSize() const override;

        private:
        void drawStr(size_t x, size_t y, const std::string &str, std::array<char, 3> fg, std::array<char, 3> bg);
        void drawText();
        void getLibs();
        void addText(arcade::menu::Text text);
        arcade::STATUS loadOptions();

        std::vector<arcade::menu::Text> texts_;
        size_t selected_ = 1;

        std::pair<arcade::OPTIONS, std::string> option_;

        size_t ngames_ = 0;
        size_t ndisplay_ = 0;

        arcade::FrameBuffer frameBuffer_;
        arcade::Size size_ = { 35, 40 };

        const std::unordered_map<char, arcade::Characters> chars_ = {
            { '0', arcade::Characters::ZERO },
            { '1', arcade::Characters::ONE },
            { '2', arcade::Characters::TWO },
            { '3', arcade::Characters::THREE },
            { '4', arcade::Characters::FOUR },
            { '5', arcade::Characters::FIVE },
            { '6', arcade::Characters::SIX },
            { '7', arcade::Characters::SEVEN },
            { '8', arcade::Characters::EIGHT },
            { '9', arcade::Characters::NINE },
            { 'a', arcade::Characters::A },
            { 'b', arcade::Characters::B },
            { 'c', arcade::Characters::C },
            { 'd', arcade::Characters::D },
            { 'e', arcade::Characters::E },
            { 'f', arcade::Characters::F },
            { 'g', arcade::Characters::G },
            { 'h', arcade::Characters::H },
            { 'i', arcade::Characters::I },
            { 'j', arcade::Characters::J },
            { 'k', arcade::Characters::K },
            { 'l', arcade::Characters::L },
            { 'm', arcade::Characters::M },
            { 'n', arcade::Characters::N },
            { 'o', arcade::Characters::O },
            { 'p', arcade::Characters::P },
            { 'q', arcade::Characters::Q },
            { 'r', arcade::Characters::R },
            { 's', arcade::Characters::S },
            { 't', arcade::Characters::T },
            { 'u', arcade::Characters::U },
            { 'v', arcade::Characters::V },
            { 'w', arcade::Characters::W },
            { 'x', arcade::Characters::X },
            { 'y', arcade::Characters::Y },
            { 'z', arcade::Characters::Z },
            { '?', arcade::Characters::QUESTION_MARK },
            { '!', arcade::Characters::EXCLAMATION_MARK },
            { ',', arcade::Characters::COMMA },
            { '.', arcade::Characters::PERIOD },
            { '#', arcade::Characters::HASHTAG },
            { '+', arcade::Characters::PLUS },
            { '-', arcade::Characters::MINUS },
            { '*', arcade::Characters::ASTERISK },
            { ':', arcade::Characters::COLON },
            { ';', arcade::Characters::SEMICOLON },
            { '_', arcade::Characters::UNDERSCORE },
            { '$', arcade::Characters::DOLLAR },
            { '=', arcade::Characters::EQUALS },
            { '(', arcade::Characters::LEFT_PARENTHESIS },
            { ')', arcade::Characters::RIGHT_PARENTHESIS },
            { '%', arcade::Characters::PERCENT },
            { ' ', arcade::Characters::NULL_CHR },
        };
    };
}// namespace arcade::menu
