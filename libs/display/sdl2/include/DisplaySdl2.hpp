/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** DisplaySdl2.hpp
*/

#pragma once

#include "IDisplay.hpp"
#include <SDL.h>
#include <array>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

namespace arcade::sdl2 {

    class DisplaySdl2 : public arcade::IDisplay
    {
        public:
        DisplaySdl2();
        DisplaySdl2(arcade::Size size);
        DisplaySdl2(const DisplaySdl2 &) = delete;
        DisplaySdl2(DisplaySdl2 &&) = delete;
        DisplaySdl2 &operator=(const DisplaySdl2 &) = delete;
        DisplaySdl2 &operator=(DisplaySdl2 &&) = delete;
        ~DisplaySdl2();

        void init();

        arcade::Size getSize() const override;
        void setSize(arcade::Size size);

        std::list<arcade::EVENT> pollEvents(std::list<arcade::EVENT> &events) override;

        void draw(arcade::FrameBuffer &frameBuffer) override;
        void clear() override;
        void display() override;

        private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> InitWindow();
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> InitSurface();
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> InitTexture();
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> InitRenderer();

        arcade::Size windowSize_;

        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_;
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface_;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture_;

        std::array<SDL_Rect, 128> sprite_;
        Uint32 start_ = SDL_GetTicks();

        const std::unordered_map<size_t, arcade::EVENT> events_{
            { SDLK_a, arcade::EVENT::ARCADE_KEY_A },
            { SDLK_b, arcade::EVENT::ARCADE_KEY_B },
            { SDLK_c, arcade::EVENT::ARCADE_KEY_C },
            { SDLK_d, arcade::EVENT::ARCADE_KEY_D },
            { SDLK_e, arcade::EVENT::ARCADE_KEY_E },
            { SDLK_f, arcade::EVENT::ARCADE_KEY_F },
            { SDLK_g, arcade::EVENT::ARCADE_KEY_G },
            { SDLK_h, arcade::EVENT::ARCADE_KEY_H },
            { SDLK_i, arcade::EVENT::ARCADE_KEY_I },
            { SDLK_j, arcade::EVENT::ARCADE_KEY_J },
            { SDLK_k, arcade::EVENT::ARCADE_KEY_K },
            { SDLK_l, arcade::EVENT::ARCADE_KEY_L },
            { SDLK_m, arcade::EVENT::ARCADE_KEY_M },
            { SDLK_n, arcade::EVENT::ARCADE_KEY_N },
            { SDLK_o, arcade::EVENT::ARCADE_KEY_O },
            { SDLK_p, arcade::EVENT::ARCADE_KEY_P },
            { SDLK_q, arcade::EVENT::ARCADE_KEY_Q },
            { SDLK_r, arcade::EVENT::ARCADE_KEY_R },
            { SDLK_s, arcade::EVENT::ARCADE_KEY_S },
            { SDLK_t, arcade::EVENT::ARCADE_KEY_T },
            { SDLK_u, arcade::EVENT::ARCADE_KEY_U },
            { SDLK_v, arcade::EVENT::ARCADE_KEY_V },
            { SDLK_w, arcade::EVENT::ARCADE_KEY_W },
            { SDLK_x, arcade::EVENT::ARCADE_KEY_X },
            { SDLK_y, arcade::EVENT::ARCADE_KEY_Y },
            { SDLK_z, arcade::EVENT::ARCADE_KEY_Z },
            { SDLK_1, arcade::EVENT::ARCADE_KEY_1 },
            { SDLK_2, arcade::EVENT::ARCADE_KEY_2 },
            { SDLK_3, arcade::EVENT::ARCADE_KEY_3 },
            { SDLK_4, arcade::EVENT::ARCADE_KEY_4 },
            { SDLK_5, arcade::EVENT::ARCADE_KEY_5 },
            { SDLK_6, arcade::EVENT::ARCADE_KEY_6 },
            { SDLK_7, arcade::EVENT::ARCADE_KEY_7 },
            { SDLK_8, arcade::EVENT::ARCADE_KEY_8 },
            { SDLK_9, arcade::EVENT::ARCADE_KEY_9 },
            { SDLK_0, arcade::EVENT::ARCADE_KEY_0 },
            { SDLK_RIGHT, arcade::EVENT::ARCADE_KEY_RIGHT },
            { SDLK_LEFT, arcade::EVENT::ARCADE_KEY_LEFT },
            { SDLK_UP, arcade::EVENT::ARCADE_KEY_UP },
            { SDLK_DOWN, arcade::EVENT::ARCADE_KEY_DOWN },
            { SDLK_SPACE, arcade::EVENT::ARCADE_KEY_SPACE },
            { SDLK_KP_ENTER, arcade::EVENT::ARCADE_KEY_ENTER },
            { SDLK_ESCAPE, arcade::EVENT::ARCADE_KEY_ESC },
            { SDLK_TAB, arcade::EVENT::ARCADE_KEY_TAB },
            { SDLK_LSHIFT, arcade::EVENT::ARCADE_KEY_SHIFT },
            { SDLK_LCTRL, arcade::EVENT::ARCADE_KEY_CTRL },
            { SDLK_LALT, arcade::EVENT::ARCADE_KEY_ALT },
            { SDLK_F1, arcade::EVENT::ARCADE_SYS_MENU },
            { SDLK_F2, arcade::EVENT::ARCADE_SYS_NEXT_DISPLAY },
            { SDLK_F3, arcade::EVENT::ARCADE_SYS_PREV_DISPLAY },
            { SDLK_F4, arcade::EVENT::ARCADE_SYS_NEXT_GAME },
            { SDLK_F5, arcade::EVENT::ARCADE_SYS_PREV_GAME },
            { SDLK_F9, arcade::EVENT::ARCADE_SYS_EXIT },
            { SDLK_F6, arcade::EVENT::ARCADE_SYS_RESTART },
            { SDLK_F7, arcade::EVENT::ARCADE_WIN_CLOSE },
        };
    };
}// namespace arcade::sdl2
