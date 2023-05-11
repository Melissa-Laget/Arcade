/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Core.hpp
*/

#pragma once

#include "IDisplay.hpp"
#include "IGame.hpp"
#include "Lib.hpp"
#include "arcade.hpp"
#include <filesystem>

namespace arcade {

    class Core
    {
        public:
        Core(const std::string &menuPath, const std::string &graphPath);
        Core(const Core &) = delete;
        Core(Core &&) = delete;
        Core &operator=(const Core &) = delete;
        Core &operator=(Core &&) = delete;
        ~Core() = default;

        void run();

        private:
        std::pair<arcade::LibType, std::unique_ptr<arcade::Lib>> getLib(const std::string &path);
        void getLibPaths(const std::string &path);

        void loadLib(const std::string &path);
        void loadLib(const std::string &path, arcade::LibType type);
        void loadLib(std::pair<arcade::LibType, std::unique_ptr<arcade::Lib>> &lib);
        void loadGame(std::unique_ptr<arcade::Lib> lib);
        void loadDisplay(std::unique_ptr<arcade::Lib> lib);

        void nextDisplay();
        void nextGame();
        void prevDisplay();
        void prevGame();

        bool options();

        static void copyFrameBuffer(const arcade::FrameBuffer &src, arcade::FrameBuffer &dest);
        static void flushFrameBuffer(arcade::FrameBuffer &frameBuffer, const arcade::Size &size);

        bool eventHandler(std::list<arcade::EVENT> &events);
        void updateFrameBuffer(const arcade::FrameBuffer &frameBuffer, bool flush = false);
        void clearDisplayBuffer();
        void restart();

        std::unique_ptr<arcade::Lib> displayLib_;
        std::unique_ptr<arcade::Lib> gameLib_;

        std::vector<std::string> gamePaths_;
        std::vector<std::string> displayPaths_;
        std::string menuPath_;

        std::unique_ptr<IDisplay> display_;
        std::unique_ptr<IGame> game_;

        arcade::Size size_ = { 0, 0 };

        arcade::FrameBuffer frameBuffer_;
        arcade::FrameBuffer displayBuffer_;
    };

}// namespace arcade
