/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-arcade-melissa.laget
** File description:
** arcade.cpp
*/

#include "arcade.hpp"

std::ostream &operator<<(std::ostream &stream, arcade::LibType type)
{
    switch (type) {
    case arcade::LibType::GAME:
        stream << "GAME";
        break;
    case arcade::LibType::GRAPHICAL:
        stream << "DISPLAY";
        break;
    default:
        stream << "UNKNOWN";
        break;
    }
    return stream;
}

namespace arcade {
    std::string to_string(const arcade::LibType &type)
    {
        switch (type) {
        case arcade::LibType::GAME:
            return "GAME";
        case arcade::LibType::GRAPHICAL:
            return "DISPLAY";
        default:
            return "UNKNOWN";
        }
    }
}// namespace arcade
