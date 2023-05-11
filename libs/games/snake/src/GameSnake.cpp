/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** displaySfml.cpp
*/

#include "GameSnake.hpp"
#include <memory>

namespace arcade::snake {

    void GameSnake::flushFrameBuffer(FrameBuffer &frameBuffer, const Size &size)
    {
        frameBuffer.size = size;
        frameBuffer.pixels.clear();
        frameBuffer.pixels.reserve(size.width * size.height);
        for (size_t i = 0; i < frameBuffer.size.width * frameBuffer.size.height; i++)
            frameBuffer.pixels.push_back({ false, { 0, 0, 0 }, { 0, 0, 0 }, arcade::Characters::NULL_CHR });
    }

    void GameSnake::flushFrameBuffer(FrameBuffer &frameBuffer)
    {
        for (size_t i = 0; i < frameBuffer.size.width * frameBuffer.size.height; i++)
            frameBuffer.pixels[i] = { false, { 0, 0, 0 }, { 0, 0, 0 }, arcade::Characters::NULL_CHR };
    }

    arcade::Size GameSnake::getSize() const
    {
        return { 50, 50 };
    }

    arcade::STATUS GameSnake::run(std::list<arcade::EVENT> &events)
    {
        this->handleEvent(events);
        if (this->tick_++ >= 10) {
            this->tick_ = 0;
            if (!this->moveSnake())
                return arcade::STATUS::OPTION;
            this->flushFrameBuffer(this->frameBuffer_);
            this->drawFood();
            this->drawSnake();
        }
        return RUNNING;
    }

    arcade::FrameBuffer &GameSnake::getFrameBuffer()
    {
        return this->frameBuffer_;
    }

    std::pair<arcade::OPTIONS, std::string> GameSnake::option()
    {
        return { arcade::OPTIONS::RESTART, "" };
    }

    GameSnake::GameSnake() : randomEngine_(r_()), randPos_(0, 49)
    {
        this->flushFrameBuffer(this->frameBuffer_, this->getSize());
        this->moveFood();
    }

    void GameSnake::handleEvent(std::list<arcade::EVENT> &events)
    {
        for (auto &event : events) {
            switch (event) {
            case arcade::EVENT::ARCADE_KEY_LEFT:
                if (this->direction_ <= arcade::snake::Direction::RIGHT)
                    this->direction_ = arcade::snake::Direction::UP;
                else
                    this->direction_--;
                break;
            case arcade::EVENT::ARCADE_KEY_RIGHT:
                if (this->direction_ >= arcade::snake::Direction::UP)
                    this->direction_ = arcade::snake::Direction::RIGHT;
                else
                    this->direction_++;
                break;
            default:
                break;
            }
        }
        events.clear();
    }

    void GameSnake::drawSnake()
    {
        for (auto &pos : this->snake_) {
            this->frameBuffer_.pixels[pos.x + (pos.y * this->frameBuffer_.size.width)] = {
                false, { 0, 127, 0 }, { 0, 0, 0 }, arcade::Characters::O
            };
        }
    }

    void GameSnake::drawFood()
    {
        this->frameBuffer_.pixels[this->food_.x + (this->food_.y * this->frameBuffer_.size.width)] = {
            false, { 127, 0, 0 }, { 0, 0, 0 }, arcade::Characters::X
        };
    }

    bool GameSnake::moveSnake()
    {
        arcade::snake::Pos pos = this->snake_.front();

        switch (this->direction_) {
        case arcade::snake::Direction::UP:
            pos.y--;
            break;
        case arcade::snake::Direction::DOWN:
            pos.y++;
            break;
        case arcade::snake::Direction::LEFT:
            pos.x--;
            break;
        case arcade::snake::Direction::RIGHT:
            pos.x++;
        }
        this->snake_.push_front(pos);
        if (pos.x == this->food_.x && pos.y == this->food_.y)
            this->moveFood();
        else if (pos.x < 0 || pos.x >= 50
                 || this->frameBuffer_.pixels[pos.x + (pos.y * this->frameBuffer_.size.width)].c != NULL_CHR) {
            std::cout << "GAME OVER" << std::endl;
            return false;
        } else
            this->snake_.pop_back();
        return true;
    }

    void GameSnake::moveFood()
    {
        this->food_.x = this->randPos_(this->r_);
        this->food_.y = this->randPos_(this->r_);
    }
}// namespace arcade::snake

extern "C" std::unique_ptr<arcade::IGame> createGame()
{
    return std::make_unique<arcade::snake::GameSnake>();
}

extern "C" const arcade::LibType getType()
{
    return arcade::LibType::GAME;
}
