/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-arcade-melissa.laget
** File description:
** main.cpp
*/

#include "IDisplay.hpp"
#include "IGame.hpp"
#include <Core.hpp>
#include <spdlog/spdlog.h>

int main(int ac, char **av)
{
    spdlog::set_level(spdlog::level::err);

    try {
        arcade::Core core("lib/libarcade_menu.so", ac > 1 ? av[1] : "lib/libarcade_display_sdl2.so");
        core.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
