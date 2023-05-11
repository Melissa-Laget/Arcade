/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** DisplayNcurses.cpp
*/

#include "DisplayNcurses.hpp"
#include <memory>

namespace arcade::ncurses {

    std::unique_ptr<WINDOW, decltype(&delwin)> DisplayNcurses::InitWindow()
    {
        WINDOW *window = nullptr;

        if (initscr() == nullptr)
            throw std::runtime_error("Error: initscr() failed");
        this->checkSize();
        window = newwin(this->windowSize_.height, this->windowSize_.width, 0, 0);
        nodelay(stdscr, TRUE);
        nodelay(window, TRUE);
        return { window, delwin };
    }

    DisplayNcurses::DisplayNcurses() : DisplayNcurses({ 10, 10 }) {}

    DisplayNcurses::DisplayNcurses(arcade::Size size)
        : time_(std::chrono::system_clock::now()), windowSize_(size), window_(InitWindow())
    {
        setlocale(LC_ALL, "");
        keypad(stdscr, TRUE);
        keypad(this->window_.get(), TRUE);
        curs_set(0);
    }

    Size DisplayNcurses::getSize() const
    {
        return this->windowSize_;
    }

    void DisplayNcurses::setSize(arcade::Size size)
    {
        if (this->windowSize_.height == size.height && this->windowSize_.width == size.width)
            DisplayNcurses::getSize();
        this->checkSize();
        wresize(this->window_.get(), size.height, size.width);
        this->windowSize_ = size;
    }

    void DisplayNcurses::checkSize()
    {
        int row;
        int col;

        getmaxyx(stdscr, row, col);
    }

    void DisplayNcurses::draw(arcade::FrameBuffer &frameBuffer)
    {
        cchar_t Character = cchar_t();
        arcade::Pixel *pixel = nullptr;
        wchar_t whiteChar = L' ';

        this->checkSize();
        for (size_t y = 0; y < frameBuffer.size.height; y++) {
            for (size_t x = 0; x < frameBuffer.size.width; x++) {
                pixel = &frameBuffer.pixels.at(x + (y * frameBuffer.size.width));
                if (!pixel->up)
                    continue;
                whiteChar = this->characters_[pixel->c];
                setcchar(&Character, &whiteChar, A_COLOR, 0, nullptr);
                mvwadd_wch(this->window_.get(), y, x, &Character);
            }
        }
    }

    void DisplayNcurses::clear()
    {
        wclear(this->window_.get());
    }

    void DisplayNcurses::display()
    {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(this->time_ - now).count();

        if (ms < 1000 / 60)
            usleep((1000 / 60 - ms) * 1000);
        this->time_ = std::chrono::system_clock::now();
        wrefresh(this->window_.get());
    }

    std::list<arcade::EVENT> DisplayNcurses::pollEvents(std::list<arcade::EVENT> &events)
    {
        int const key = getch();

        if (key != ERR)
            events.push_back(this->events_[key]);
        return events;
    }

    DisplayNcurses::~DisplayNcurses()
    {
        endwin();
    }

}// namespace arcade::ncurses

extern "C" const arcade::LibType getType()
{
    return arcade::LibType::GRAPHICAL;
}

extern "C" std::unique_ptr<arcade::IDisplay> createLibrary(arcade::Size size)
{
    return std::make_unique<arcade::ncurses::DisplayNcurses>(size);
}
