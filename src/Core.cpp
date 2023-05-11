/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Core.cpp
*/

#include "Core.hpp"

namespace fs = std::filesystem;

namespace arcade {

    Core::Core(const std::string &menuPath, const std::string &graphPath) : menuPath_(menuPath)
    {
        spdlog::info("Starting Core");
        try {
            spdlog::info("\t==> Loading menu: {}", menuPath);
            this->loadLib(menuPath, arcade::LibType::GAME);
            if (!this->game_)
                throw std::runtime_error("Menu not loaded !");
            spdlog::info("\t==> Loading display: {}", graphPath);
            this->loadLib(graphPath, arcade::LibType::GRAPHICAL);

        } catch (std::exception &e) {
            spdlog::error("Error: {}", e.what());
            throw e;
        }
        this->getLibPaths("lib/");
    }

    void Core::run()
    {
        std::list<arcade::EVENT> events;
        bool running = true;

        spdlog::info("Arcade running !");
        while (running) {
            if (!this->game_) {
                spdlog::warn("No game loaded, loading menu...");
                try {
                    this->loadLib(this->menuPath_, arcade::LibType::GAME);
                } catch (std::exception &e) {
                    spdlog::error("Error loading menu: {}", e.what());
                    throw e;
                }
                spdlog::info("Menu loaded !");
            }
            this->updateFrameBuffer(this->game_->getFrameBuffer());
            if (!this->display_)
                throw std::runtime_error("No display loaded !");
            this->display_->draw(this->displayBuffer_);
            this->display_->display();
            events = this->display_->pollEvents(events);
            if (!this->eventHandler(events))
                break;
            switch (this->game_->run(events)) {
            case arcade::STATUS::EXIT:
                running = false;
                break;
            case arcade::STATUS::FAILURE:
                spdlog::error("Game failed");
                return;
            case arcade::STATUS::RUNNING:
                break;
            case arcade::STATUS::OPTION:
                spdlog::info("Loading game options");
                running = this->options();
                break;
            }
        }
        spdlog::info("Arcade closed !");
    }

    bool Core::eventHandler(std::list<arcade::EVENT> &events)
    {
        size_t i = 0;

        spdlog::trace("Handling system events:");
        for (auto event = events.begin(); event != events.end(); event++) {
            switch (*event) {
            case arcade::EVENT::ARCADE_WIN_CLOSE:
                spdlog::info("\t==> Window closed");
            case arcade::EVENT::ARCADE_SYS_EXIT:
                spdlog::info("\t==> Exiting arcade");
                events.erase(event--);
                return false;
            case arcade::EVENT::ARCADE_SYS_RESTART:
                this->restart();
                events.erase(event--);
                break;
            case arcade::EVENT::ARCADE_SYS_MENU:
                spdlog::info("\t==> Loading menu");
                this->loadLib(this->menuPath_, arcade::LibType::GAME);
                events.erase(event--);
                break;
            case arcade::EVENT::ARCADE_SYS_NEXT_DISPLAY:
                this->nextDisplay();
                events.erase(event--);
                break;
            case arcade::EVENT::ARCADE_SYS_PREV_DISPLAY:
                this->prevDisplay();
                events.erase(event--);
                break;
            case arcade::EVENT::ARCADE_SYS_NEXT_GAME:
                this->nextGame();
                events.erase(event--);
                break;
            case arcade::EVENT::ARCADE_SYS_PREV_GAME:
                this->prevGame();
                events.erase(event--);
            default:
                break;
            }
            i++;
        }
        return true;
    }

    void Core::loadLib(std::pair<arcade::LibType, std::unique_ptr<arcade::Lib>> &lib)
    {
        try {
            switch (lib.first) {
            case arcade::LibType::GRAPHICAL:
                this->loadDisplay(std::move(lib.second));
                break;
            case arcade::LibType::GAME:
                this->loadGame(std::move(lib.second));
                break;
            default:
                throw std::runtime_error("Error: " + lib.second->getPath() + " is not a valid library");
            }
        } catch (std::exception &e) {
            spdlog::error("Error: {}", e.what());
            throw e;
        }
    }

    void Core::loadLib(const std::string &path)
    {
        try {
            auto lib = this->getLib(path);
            this->loadLib(lib);
        } catch (std::exception &e) {
            spdlog::error("Error: {}", e.what());
        }
    }

    void Core::loadLib(const std::string &path, arcade::LibType type)
    {
        try {
            auto lib = this->getLib(path);

            if (lib.first != type) {
                spdlog::error("Error: {} does not match the wanted type: {} != {}",
                              path,
                              arcade::to_string(lib.first),
                              arcade::to_string(type));
                return;
            }
            this->loadLib(lib);
        } catch (std::exception &e) {
            spdlog::error("Error: {}", e.what());
        }
    }

    void Core::loadGame(std::unique_ptr<arcade::Lib> lib)
    {
        spdlog::debug("Loading game");
        try {
            this->game_ = std::move(lib->loadClass<arcade::IGame>("createGame"));
        } catch (std::exception &e) {
            spdlog::error("Error: {}", e.what());
            return;
        }
        spdlog::info("\t==> Replacing current game");
        this->gameLib_ = std::move(lib);
        this->size_ = this->game_->getSize();
        spdlog::debug("\t\t==> New game size: {}x{}", this->size_.width, this->size_.height);
        if (this->display_) {
            this->display_->setSize(this->size_);
            this->display_->clear();
        }
        spdlog::debug("\t\t==> Polling first FrameBuffer");
        this->updateFrameBuffer(this->game_->getFrameBuffer(), true);
        spdlog::info("\t==> Game loaded");
    }

    void Core::loadDisplay(std::unique_ptr<arcade::Lib> lib)
    {
        spdlog::info("Loading display");
        try {
            this->display_ = nullptr;
            this->display_ = std::move(lib->loadClass<arcade::IDisplay, arcade::Size>("createLibrary", this->size_));
        } catch (std::exception &e) {
            spdlog::error("Error: {}", e.what());
            this->display_ =
                std::move(this->displayLib_->loadClass<arcade::IDisplay, arcade::Size>("createLibrary", this->size_));
            return;
        }
        spdlog::info("\t==> Replacing current Display");
        this->displayLib_ = std::move(lib);
        spdlog::debug("\t\t==> Setting new size: {}x{}", this->size_.width, this->size_.height);
        //        this->display_->setSize(this->size_);
        spdlog::debug("\t\t==> Polling first FrameBuffer");
        this->updateFrameBuffer(this->game_->getFrameBuffer(), true);
        spdlog::info("\t==> Display loaded");
    }

    void Core::restart()
    {
        spdlog::info("Restarting game");
        this->loadGame(std::move(this->gameLib_));
        spdlog::info("\t==> Game restarted !");
    }

    void Core::updateFrameBuffer(const arcade::FrameBuffer &frameBuffer, bool flush)
    {
        size_t p = 0;// only used for debug logs

        spdlog::trace("Updating frame buffer");
        if (flush || this->frameBuffer_.size.width != frameBuffer.size.width
            || this->frameBuffer_.size.height != frameBuffer.size.height) {
            spdlog::info("\t==> new FrameBuffer found, flushing old one");
            spdlog::debug("\t\t==> flushing internal FrameBuffer");
            this->flushFrameBuffer(this->frameBuffer_, frameBuffer.size);
            spdlog::debug("\t\t==> flushing display FrameBuffer");
            this->flushFrameBuffer(this->displayBuffer_, frameBuffer.size);
            return;
        }

        spdlog::trace("\t==> updating display FrameBuffer");
        this->clearDisplayBuffer();
        spdlog::trace("\t==> Flushing done");
        for (size_t i = 0; i < frameBuffer.pixels.size(); i++) {
            if (*(uint64_t *)&(frameBuffer.pixels[i]) != *(uint64_t *)&(this->frameBuffer_.pixels.at(i))) {
                p++;
                spdlog::trace("\t\t==> pixel {} changed", i);
                this->displayBuffer_.pixels[i] = frameBuffer.pixels[i];
                this->frameBuffer_.pixels[i] = frameBuffer.pixels[i];
                this->displayBuffer_.pixels[i].up = true;
            }
        }
        if (p > 0) {
            spdlog::debug("\t==> {} pixels changed", p);
        }
    }

    void Core::copyFrameBuffer(const arcade::FrameBuffer &src, arcade::FrameBuffer &dest)
    {
        dest.size.width = src.size.width;
        dest.size.height = src.size.height;

        if (src.pixels.size() != dest.pixels.size()) {
            dest.pixels.clear();
            spdlog::info("\t\t==> resizing pixel vector ({} -> {})", dest.pixels.size(), src.pixels.size());
            dest.pixels.reserve(src.pixels.size());
        }

        for (auto pixel : src.pixels) {
            dest.pixels.push_back(pixel);
        }
    }

    void Core::clearDisplayBuffer()
    {
        for (auto pixel : this->displayBuffer_.pixels) {
            *(uint64_t *)&(pixel) = 0;
        }
    }

    void Core::flushFrameBuffer(FrameBuffer &frameBuffer, const Size &size)
    {
        frameBuffer.size = size;
        frameBuffer.pixels.clear();
        frameBuffer.pixels.reserve(size.width * size.height);
        for (size_t i = 0; i < size.width * size.height; i++) {
            frameBuffer.pixels.push_back({ false, { 0, 0, 0 }, { 0, 0, 0 }, '\0' });
        }
    }

    std::pair<arcade::LibType, std::unique_ptr<arcade::Lib>> Core::getLib(const std::string &path)
    {
        std::pair<arcade::LibType, std::unique_ptr<arcade::Lib>> lib;

        try {
            lib.second = std::make_unique<arcade::Lib>(path);
            const std::function<arcade::LibType()> getType = lib.second->loadFunc<arcade::LibType()>("getType");
            lib.first = getType();
        } catch (std::exception &e) {
            spdlog::error("Error while loading {}: {}", path, e.what());
            throw e;
        }
        return lib;
    }

    void Core::getLibPaths(const std::string &path)
    {
        spdlog::info("Searching for libraries in {}", path);
        for (const auto &entry : fs::directory_iterator(path)) {
            if (!entry.is_regular_file() || (entry.path().extension() != ".so" && entry.path().extension() != ".dll"))
                continue;
            try {
                auto lib = this->getLib(entry.path().string());
                switch (lib.first) {
                case arcade::LibType::GAME:
                    spdlog::debug("\t==> Found game library: {}", entry.path().string());
                    this->gamePaths_.push_back(entry.path().string());
                    break;
                case arcade::LibType::GRAPHICAL:
                    spdlog::debug("\t==> Found graphical library: {}", entry.path().string());
                    this->displayPaths_.push_back(entry.path().string());
                    break;
                default:
                    throw std::runtime_error("Error: " + entry.path().string() + " is not a valid library");
                }
            } catch (std::exception &e) {
                spdlog::warn("Error: {}", e.what());
            }
        }
    }

    void Core::nextDisplay()
    {
        spdlog::info("\t==> Loading next display");
        auto it = std::find(this->displayPaths_.begin(), this->displayPaths_.end(), this->displayLib_->getPath());
        if (it == this->displayPaths_.end() || it + 1 == this->displayPaths_.end())
            this->loadLib(this->displayPaths_.front(), arcade::LibType::GRAPHICAL);
        else
            this->loadLib(*(it + 1), arcade::LibType::GRAPHICAL);
    }

    void Core::prevDisplay()
    {
        spdlog::info("\t==> Loading previous display");
        auto it = std::find(this->displayPaths_.begin(), this->displayPaths_.end(), this->displayLib_->getPath());
        if (it == this->displayPaths_.end() || it == this->displayPaths_.begin())
            this->loadLib(this->displayPaths_.back(), arcade::LibType::GRAPHICAL);
        else
            this->loadLib(*(it - 1), arcade::LibType::GRAPHICAL);
    }

    void Core::nextGame()
    {
        spdlog::info("\t==> Loading next game");
        auto it = std::find(this->gamePaths_.begin(), this->gamePaths_.end(), this->gameLib_->getPath());
        if (it == this->gamePaths_.end() || it + 1 == this->gamePaths_.end())
            this->loadLib(this->gamePaths_.front(), arcade::LibType::GAME);
        else
            this->loadLib(*(it + 1), arcade::LibType::GAME);
    }

    void Core::prevGame()
    {
        spdlog::info("\t==> Loading previous game");
        auto it = std::find(this->gamePaths_.begin(), this->gamePaths_.end(), this->gameLib_->getPath());
        if (it == this->gamePaths_.end() || it == this->gamePaths_.begin())
            this->loadLib(this->gamePaths_.back(), arcade::LibType::GAME);
        else
            this->loadLib(*(it - 1), arcade::LibType::GAME);
    }

    bool Core::options()
    {
        auto option = this->game_->option();

        switch (option.first) {
        case arcade::OPTIONS::LOAD_GAME:
            this->loadLib(option.second, arcade::LibType::GAME);
            break;
        case arcade::OPTIONS::LOAD_GRAPH:
            this->loadLib(option.second, arcade::LibType::GRAPHICAL);
            break;
        case arcade::OPTIONS::QUIT:
            return false;
        case arcade::OPTIONS::RESTART:
            this->restart();
            break;
        }
        return true;
    }
}// namespace arcade
