/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** main.cpp
*/

#include "DisplaySdl2.hpp"
#include <chrono>

namespace sc = std::chrono;

int main(int ac, char **av)
{
    arcade::sdl2::DisplaySdl2 display({ 16, 8 });
    arcade::FrameBuffer frame_buffer;
    std::list<arcade::EVENT> evt;

    for (int i = 0; i < 128; i++) {
        frame_buffer.pixels.push_back({ true, { 127, 0, 127 }, { 10, 10, 10 }, static_cast<char>(i) });
    }
    frame_buffer.size.height = 8;
    frame_buffer.size.width = 16;
    while (1) {
        auto time = sc::system_clock::now();

        auto since_epoch = time.time_since_epoch();
        auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);
        std::cout << millis.count() << std::endl;
        display.draw(frame_buffer);
        display.display();
        evt = display.pollEvents(evt);
        for (auto &e : evt) {
            std::cout << e << std::endl;
        }
        evt.clear();
    }
    return 0;
}