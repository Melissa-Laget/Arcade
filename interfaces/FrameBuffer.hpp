/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-arcade-melissa.laget
** File description:
** IFrameBuffer.hpp
*/

#pragma once

#include <array>
#include <iostream>
#include <vector>

namespace arcade {

    struct Size
    {
        size_t width;
        size_t height;
    };

    struct Pixel
    {
        bool up;
        std::array<char, 3> fg;
        std::array<char, 3> bg;
        char c;
    };

    struct FrameBuffer
    {
        std::vector<Pixel> pixels;
        Size size;
    };

};// namespace arcade
