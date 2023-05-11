/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** DisplayNcurses.hpp
*/

#pragma once

#include "IDisplay.hpp"
#include <array>
#include <chrono>
#include <list>
#include <memory>
#include <ncursesw/ncurses.h>
#include <unordered_map>
#include <vector>

namespace arcade::ncurses {
    class DisplayNcurses : public arcade::IDisplay
    {
        public:
        DisplayNcurses();
        DisplayNcurses(arcade::Size size);
        DisplayNcurses(const DisplayNcurses &) = delete;
        DisplayNcurses(DisplayNcurses &&) = delete;
        DisplayNcurses &operator=(const DisplayNcurses &) = delete;
        DisplayNcurses &operator=(DisplayNcurses &&) = delete;
        ~DisplayNcurses();

        arcade::Size getSize() const override;
        void setSize(arcade::Size size);

        std::list<arcade::EVENT> pollEvents(std::list<arcade::EVENT> &events) override;

        void draw(arcade::FrameBuffer &frameBuffer) override;
        void clear() override;
        void display() override;

        private:
        std::unique_ptr<WINDOW, decltype(&delwin)> InitWindow();

        void checkSize();

        std::chrono::time_point<std::chrono::system_clock> time_;

        arcade::Size windowSize_;
        std::unique_ptr<WINDOW, decltype(&delwin)> window_;


        std::array<const wchar_t, 128> characters_ = {
            '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  'a',  'b',  'c',  'd',  'e',  'f',
            'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',  'p',  'q',  'r',  's',  't',  'u',  'v',
            'w',  'x',  'y',  'z',  '?',  '!',  ',',  '.',  '#',  '+',  '-',  '*',  ':',  ';',  '_',  '$',
            '=',  '(',  ')',  '%',  '.',  L'‧', L'○', L'●', L'□', L'■', L'☆', L'↑', L'↓', L'←', L'→', L'─',
            L'│', L'┌', L'┐', L'└', L'┘', L'├', L'┤', L'┬', L'┴', L'┼', L'═', L'║', L'╔', L'╗', L'╚', L'╝',
            L'╠', L'╣', L'╦', L'╩', L'╬', L'◁', L'▷', L'△', L'▽', L'◀', L'▶', L'▲', L'▼', L'█', L'✗', L'✓',
            L'•', '/',  '\\', '&',  '@',  '"',  '\'', '<',  '>',  '~',  '|',  L'⚑', L'➤', L'↻', L'⚡', L'×',
            L'★', ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' '
        };

        std::unordered_map<int, arcade::EVENT> events_ = {
            { KEY_UP, arcade::EVENT::ARCADE_KEY_UP },
            { KEY_DOWN, arcade::EVENT::ARCADE_KEY_DOWN },
            { KEY_LEFT, arcade::EVENT::ARCADE_KEY_LEFT },
            { KEY_RIGHT, arcade::EVENT::ARCADE_KEY_RIGHT },
            { 'a', arcade::EVENT::ARCADE_KEY_A },
            { 'b', arcade::EVENT::ARCADE_KEY_B },
            { 'c', arcade::EVENT::ARCADE_KEY_C },
            { 'd', arcade::EVENT::ARCADE_KEY_D },
            { 'e', arcade::EVENT::ARCADE_KEY_E },
            { 'f', arcade::EVENT::ARCADE_KEY_F },
            { 'g', arcade::EVENT::ARCADE_KEY_G },
            { 'h', arcade::EVENT::ARCADE_KEY_H },
            { 'i', arcade::EVENT::ARCADE_KEY_I },
            { 'j', arcade::EVENT::ARCADE_KEY_J },
            { 'k', arcade::EVENT::ARCADE_KEY_K },
            { 'l', arcade::EVENT::ARCADE_KEY_L },
            { 'm', arcade::EVENT::ARCADE_KEY_M },
            { 'n', arcade::EVENT::ARCADE_KEY_N },
            { 'o', arcade::EVENT::ARCADE_KEY_O },
            { 'p', arcade::EVENT::ARCADE_KEY_P },
            { 'q', arcade::EVENT::ARCADE_KEY_Q },
            { 'r', arcade::EVENT::ARCADE_KEY_R },
            { 's', arcade::EVENT::ARCADE_KEY_S },
            { 't', arcade::EVENT::ARCADE_KEY_T },
            { 'u', arcade::EVENT::ARCADE_KEY_U },
            { 'v', arcade::EVENT::ARCADE_KEY_V },
            { 'w', arcade::EVENT::ARCADE_KEY_W },
            { 'x', arcade::EVENT::ARCADE_KEY_X },
            { 'y', arcade::EVENT::ARCADE_KEY_Y },
            { 'z', arcade::EVENT::ARCADE_KEY_Z },
            { '1', arcade::EVENT::ARCADE_KEY_1 },
            { '2', arcade::EVENT::ARCADE_KEY_2 },
            { '3', arcade::EVENT::ARCADE_KEY_3 },
            { '4', arcade::EVENT::ARCADE_KEY_4 },
            { '5', arcade::EVENT::ARCADE_KEY_5 },
            { '6', arcade::EVENT::ARCADE_KEY_6 },
            { '7', arcade::EVENT::ARCADE_KEY_7 },
            { '8', arcade::EVENT::ARCADE_KEY_8 },
            { '9', arcade::EVENT::ARCADE_KEY_9 },
            { '0', arcade::EVENT::ARCADE_KEY_0 },
            { ' ', arcade::EVENT::ARCADE_KEY_SPACE },
            { KEY_ENTER, arcade::EVENT::ARCADE_KEY_ENTER },
            { 27, arcade::EVENT::ARCADE_KEY_ESC },
            { '\t', arcade::EVENT::ARCADE_KEY_TAB },
            { KEY_SLEFT, arcade::EVENT::ARCADE_KEY_SHIFT },
            { KEY_SRIGHT, arcade::EVENT::ARCADE_KEY_SHIFT },
            { KEY_C1, arcade::EVENT::ARCADE_KEY_CTRL },
            { KEY_C3, arcade::EVENT::ARCADE_KEY_CTRL },
            { KEY_A1, arcade::EVENT::ARCADE_KEY_ALT },
            { KEY_A3, arcade::EVENT::ARCADE_KEY_ALT },
            { KEY_F(1), arcade::EVENT::ARCADE_SYS_MENU },
            { KEY_F(3), arcade::EVENT::ARCADE_SYS_PREV_DISPLAY },
            { KEY_F(4), arcade::EVENT::ARCADE_SYS_NEXT_DISPLAY },
            { KEY_F(6), arcade::EVENT::ARCADE_SYS_PREV_GAME },
            { KEY_F(7), arcade::EVENT::ARCADE_SYS_NEXT_GAME },
            { KEY_F(10), arcade::EVENT::ARCADE_WIN_CLOSE },
            { KEY_F(11), arcade::EVENT::ARCADE_SYS_RESTART },
            { KEY_F(12), arcade::EVENT::ARCADE_SYS_EXIT },
        };
    };
}// namespace arcade::ncurses
