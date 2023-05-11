/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-arcade-melissa.laget
** File description:
** IDisplay.hpp
*/

#pragma once

#include "Enum.hpp"
#include "FrameBuffer.hpp"
#include <cstddef>
#include <iostream>
#include <list>
#include <tuple>

namespace arcade {

    class IDisplay
    {
        public:
        IDisplay() = default;
        IDisplay(arcade::Size size);
        IDisplay(const IDisplay &) = delete;
        IDisplay(IDisplay &&) = delete;
        IDisplay &operator=(const IDisplay &) = delete;
        IDisplay &operator=(IDisplay &&) = delete;
        virtual ~IDisplay() = default;

        virtual Size getSize() const = 0;
        virtual void setSize(arcade::Size size) = 0;

        virtual std::list<arcade::EVENT> pollEvents(std::list<arcade::EVENT> &events) = 0;

        virtual void draw(arcade::FrameBuffer &frameBuffer) = 0;

        virtual void clear() = 0;
        virtual void display() = 0;
    };
};// namespace arcade
