/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** main.cpp
*/

#include "DisplayNcurses.hpp"

int main(int ac, char **av)
{
    int a = 0;
    arcade::DisplayNcurses display({ 16, 8 });
    arcade::FrameBuffer frame_buffer;
    std::list<arcade::EVENT> evt;

    for (int i = 0; i < 128; i++) {
        frame_buffer.pixels.push_back({ true, { 127, 0, 127 }, { 10, 10, 10 }, static_cast<char>(i) });
    }
    frame_buffer.size.height = 8;
    frame_buffer.size.width = 16;
    while (1) {
        display.draw(frame_buffer);
        display.display();
        while (1)
            ;
        evt = display.pollEvents(evt);
        evt.clear();
    }
    return 0;
}
