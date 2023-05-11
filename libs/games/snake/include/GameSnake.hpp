/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-arcade-melissa.laget
** File description:
** IGame.hpp
*/

#pragma once

#include "Enum.hpp"
#include "FrameBuffer.hpp"
#include "IGame.hpp"
#include <random>

namespace arcade::snake {

    struct Pos
    {
        size_t x;
        size_t y;
    };

    enum Direction { RIGHT, DOWN, LEFT, UP };

    class GameSnake : public arcade::IGame
    {
        public:
        GameSnake();
        GameSnake(const GameSnake &) = delete;
        GameSnake(GameSnake &&) = delete;
        GameSnake &operator=(const GameSnake &) = delete;
        GameSnake &operator=(GameSnake &&) = delete;
        ~GameSnake() override = default;

        arcade::Size getSize() const override;
        arcade::FrameBuffer &getFrameBuffer() override;

        arcade::STATUS run(std::list<arcade::EVENT> &events) override;

        std::pair<arcade::OPTIONS, std::string> option() override;

        private:
        void flushFrameBuffer(FrameBuffer &frameBuffer, const Size &size);
        static void flushFrameBuffer(FrameBuffer &frameBuffer);

        void drawSnake();
        void drawFood();

        bool moveSnake();
        void moveFood();

        void handleEvent(std::list<arcade::EVENT> &events);

        short tick_ = 0;

        std::list<arcade::snake::Pos> snake_ = { { 25, 25 } };
        arcade::snake::Pos food_ = { 0, 0 };

        arcade::FrameBuffer frameBuffer_;
        char direction_ = arcade::snake::Direction::RIGHT;

        std::random_device r_;
        std::default_random_engine randomEngine_;
        std::uniform_int_distribution<int> randPos_;
    };
};// namespace arcade::snake
