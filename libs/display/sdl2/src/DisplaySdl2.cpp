/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** DisplaySdl2.cpp
*/

#include "DisplaySdl2.hpp"

namespace arcade::sdl2 {

    DisplaySdl2::DisplaySdl2() : DisplaySdl2({ 0, 0 }) {}

    DisplaySdl2::DisplaySdl2(arcade::Size size)
        : windowSize_(size), window_(InitWindow()), renderer_(InitRenderer()), surface_(InitSurface()),
          texture_(InitTexture())
    {
        this->init();
    }

    void DisplaySdl2::init()
    {
        for (int i = 0; i < 10; i++) {
            this->sprite_[i].x = i * 20;
            this->sprite_[i].y = 20;
            this->sprite_[i].w = 20;
            this->sprite_[i].h = 20;
        }
        for (int i = 0; i < 26; i++) {
            this->sprite_[i + 10].x = i * 20;
            this->sprite_[i + 10].y = 0;
            this->sprite_[i + 10].w = 20;
            this->sprite_[i + 10].h = 20;
        }
        for (int i = 0; i < 27; i++) {
            this->sprite_[i + 36].x = i * 20;
            this->sprite_[i + 36].y = 40;
            this->sprite_[i + 36].w = 20;
            this->sprite_[i + 36].h = 20;
        }
        for (int i = 0; i < 26; i++) {
            this->sprite_[i + 63].x = i * 20;
            this->sprite_[i + 63].y = 60;
            this->sprite_[i + 63].w = 20;
            this->sprite_[i + 63].h = 20;
        }
        for (int i = 0; i < 26; i++) {
            this->sprite_[i + 89].x = i * 20;
            this->sprite_[i + 89].y = 80;
            this->sprite_[i + 89].w = 20;
            this->sprite_[i + 89].h = 20;
        }
    }

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> DisplaySdl2::InitWindow()
    {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_Window *window = SDL_CreateWindow("Arcade",
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED,
                                              this->windowSize_.width * 20,
                                              this->windowSize_.height * 20,
                                              0);
        return { window, SDL_DestroyWindow };
    }

    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> DisplaySdl2::InitSurface()
    {
        SDL_Surface *surface = SDL_LoadBMP("assets/spriteSheet.bmp");

        if (surface == nullptr)
            throw std::runtime_error("Error: SDL_LoadBMP() failed");
        return { surface, SDL_FreeSurface };
    }

    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> DisplaySdl2::InitTexture()
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer_.get(), this->surface_.get());

        if (texture == nullptr)
            throw std::runtime_error("Error: SDL_CreateTextureFromSurface() failed");
        return { texture, SDL_DestroyTexture };
    }

    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> DisplaySdl2::InitRenderer()
    {
        SDL_Renderer *renderer = SDL_CreateRenderer(this->window_.get(), -1, 0);

        if (renderer == nullptr)
            throw std::runtime_error("Error: SDL_CreateRenderer() failed");
        return { renderer, SDL_DestroyRenderer };
    }

    arcade::Size DisplaySdl2::getSize() const
    {
        return this->windowSize_;
    }

    void DisplaySdl2::setSize(arcade::Size size)
    {
        if (this->windowSize_.height == size.height && this->windowSize_.width == size.width)
            DisplaySdl2::getSize();
        this->windowSize_ = { size.width, size.height };
        SDL_SetWindowSize(this->window_.get(), size.width * 20, size.height * 20);
    }

    void DisplaySdl2::draw(arcade::FrameBuffer &frameBuffer)
    {
        SDL_Rect *sprite = nullptr;
        arcade::Pixel *pixel = nullptr;
        SDL_Rect bg = { 0, 0, 20, 20 };
        SDL_Rect dstrect;

        for (size_t y = 0; y < frameBuffer.size.height; y++) {
            for (size_t x = 0; x < frameBuffer.size.width; x++) {
                pixel = &frameBuffer.pixels.at(x + (y * frameBuffer.size.width));
                if (!pixel->up)
                    continue;
                sprite = &(this->sprite_[pixel->c]);
                bg.x = static_cast<int>(x * 20);
                bg.y = static_cast<int>(y * 20);
                SDL_SetRenderDrawColor(
                    this->renderer_.get(), pixel->bg[0] * 2, pixel->bg[1] * 2, pixel->bg[2] * 2, 255);
                SDL_RenderFillRect(this->renderer_.get(), &bg);
                SDL_RenderDrawRect(this->renderer_.get(), &bg);
                SDL_SetTextureColorMod(this->texture_.get(), pixel->fg[0] * 2, pixel->fg[1] * 2, pixel->fg[2] * 2);
                dstrect = { static_cast<int>(x * 20), static_cast<int>(y * 20), 20, 20 };
                SDL_RenderCopy(this->renderer_.get(), this->texture_.get(), sprite, &dstrect);
            }
        }
    }

    void DisplaySdl2::clear()
    {
        SDL_RenderClear(this->renderer_.get());
    }

    void DisplaySdl2::display()
    {
        SDL_RenderPresent(this->renderer_.get());

        if (1000 / 60 > (SDL_GetTicks() - this->start_))
            SDL_Delay(1000 / 60 - (SDL_GetTicks() - this->start_));
        this->start_ = SDL_GetTicks();
    }

    std::list<arcade::EVENT> DisplaySdl2::pollEvents(std::list<arcade::EVENT> &events)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                auto key = this->events_.find(event.key.keysym.sym);
                if (key != this->events_.end())
                    events.push_back(key->second);
            } else if (event.type == SDL_QUIT)
                events.push_back(arcade::EVENT::ARCADE_WIN_CLOSE);
        }
        return events;
    }

    DisplaySdl2::~DisplaySdl2()
    {
        //        SDL_Quit();
    }

}// namespace arcade::sdl2

extern "C" const arcade::LibType getType()
{
    return arcade::LibType::GRAPHICAL;
}

extern "C" std::unique_ptr<arcade::IDisplay> createLibrary(arcade::Size size)
{
    return std::make_unique<arcade::sdl2::DisplaySdl2>(size);
}
