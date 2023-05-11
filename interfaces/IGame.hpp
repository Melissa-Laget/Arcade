/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-arcade-melissa.laget
** File description:
** IGame.hpp
*/

#pragma once

#include "Enum.hpp"
#include "FrameBuffer.hpp"
#include <list>
#include <tuple>

namespace arcade {
    class IGame
    {
        public:
        IGame() = default;
        IGame(const IGame &) = delete;
        IGame(IGame &&) = delete;
        IGame &operator=(const IGame &) = delete;
        IGame &operator=(IGame &&) = delete;
        virtual ~IGame() = default;

        virtual arcade::Size getSize() const = 0;

        virtual arcade::STATUS run(std::list<arcade::EVENT> &events) = 0;

        virtual arcade::FrameBuffer &getFrameBuffer() = 0;

        virtual std::pair<arcade::OPTIONS, std::string> option() = 0;
    };
};// namespace arcade
