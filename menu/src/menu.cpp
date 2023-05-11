/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** menu.cpp
*/

#include "menu.hpp"
#include <algorithm>
#include <dlfcn.h>
#include <iostream>
#include <memory>

namespace fs = std::filesystem;

namespace arcade::menu {

    Menu::Menu()
    {
        for (size_t i = 0; i < this->size_.width * this->size_.height; i++)
            this->frameBuffer_.pixels.push_back({ false, { 0, 0, 0 }, { 0, 0, 0 }, arcade::Characters::NULL_CHR });
        this->drawStr(1, 1, "arcade :", { 127, 127, 127 }, { 0, 0, 0 });
        this->getLibs();
        this->frameBuffer_.size = this->size_;
        this->addText({ "refresh", 13, 0, arcade::STATUS::RUNNING, arcade::menu::TextAction::REFRESH });
        this->addText({ "quit", 25, 0, arcade::STATUS::EXIT, arcade::menu::TextAction::RETURN });
    }

    void Menu::drawStr(size_t x, size_t y, const std::string &str, std::array<char, 3> fg, std::array<char, 3> bg)
    {
        const size_t pos = this->frameBuffer_.size.width * y + x;

        for (size_t i = 0; i < str.size(); i++) {
            auto it = this->chars_.find(str[i]);
            this->frameBuffer_.pixels[pos + i].fg[0] = fg[0];
            this->frameBuffer_.pixels[pos + i].fg[1] = fg[1];
            this->frameBuffer_.pixels[pos + i].fg[2] = fg[2];
            this->frameBuffer_.pixels[pos + i].bg[0] = bg[0];
            this->frameBuffer_.pixels[pos + i].bg[1] = bg[1];
            this->frameBuffer_.pixels[pos + i].bg[2] = bg[2];
            if (it == this->chars_.end()) {
                std::cerr << "Character not found: " << str[i] << std::endl;
                this->frameBuffer_.pixels[pos + i].c = arcade::Characters::QUESTION_MARK;
                continue;
            }
            this->frameBuffer_.pixels[pos + i].c = it->second;
        }
    }

    arcade::STATUS Menu::run(std::list<arcade::EVENT> &events)
    {
        arcade::STATUS status = arcade::STATUS::RUNNING;

        for (auto &event : events) {
            if (event == arcade::EVENT::ARCADE_KEY_UP || event == arcade::EVENT::ARCADE_KEY_LEFT) {
                if (this->selected_ > 0)
                    this->selected_--;
            } else if (event == arcade::EVENT::ARCADE_KEY_DOWN || event == arcade::EVENT::ARCADE_KEY_RIGHT) {
                if (this->selected_ < this->texts_.size() - 1)
                    this->selected_++;
            } else if (event == arcade::EVENT::ARCADE_KEY_SPACE || event == arcade::EVENT::ARCADE_KEY_ENTER) {
                status = this->loadOptions();
                break;
            }
        }
        events.clear();
        this->drawText();
        return status;
    }

    arcade::FrameBuffer &Menu::getFrameBuffer()
    {
        return this->frameBuffer_;
    }

    std::pair<arcade::OPTIONS, std::string> Menu::option()
    {
        return this->option_;
    }

    arcade::Size Menu::getSize() const
    {
        return this->size_;
    }

    void Menu::getLibs()
    {
        size_t startY = 2;
        size_t maxSize = 10;

        this->texts_.erase(std::remove_if(this->texts_.begin(),
                                          this->texts_.end(),
                                          [](const arcade::menu::Text &txt) {
                                              return (txt.action == arcade::menu::TextAction::LIBGAME
                                                      || txt.action == arcade::menu::TextAction::LIBGRAPH);
                                          }),
                           this->texts_.end());
        for (const auto &entry : fs::directory_iterator("lib/")) {
            void *lib = nullptr;
            void *func = nullptr;

            if (entry.path().extension() != ".so")
                continue;
            if (entry.path().string().length() > maxSize)
                maxSize = entry.path().string().length();
            lib = dlopen(entry.path().c_str(), RTLD_LAZY);
            if (!lib)
                throw std::runtime_error("Error: " + std::string(dlerror()));
            func = dlsym(lib, "getType");
            if (!func)
                throw std::runtime_error("Error: " + std::string(dlerror()));
            auto getType = reinterpret_cast<arcade::LibType (*)()>(func);
            this->addText({ entry.path().filename().string(),
                            2,
                            startY++,
                            arcade::STATUS::RUNNING,
                            getType() == arcade::LibType::GRAPHICAL ? arcade::menu::TextAction::LIBGRAPH
                                                                    : arcade::menu::TextAction::LIBGAME });
            dlclose(lib);
        }
        this->size_.width = maxSize + 4;
        this->selected_ = this->texts_.size() > 2 ? 2 : 0;
    }

    void Menu::drawText()
    {
        const std::array<char, 3> fg = { 127, 127, 127 };
        const std::array<char, 3> bg = { 0, 0, 0 };

        for (size_t i = 0; i < this->texts_.size(); i++) {
            this->drawStr(this->texts_[i].x,
                          this->texts_[i].y,
                          (i == this->selected_ ? "*" : " ") + this->texts_[i].text,
                          (i == this->selected_ ? bg : fg),
                          (i == this->selected_ ? fg : bg));
        }
    }

    arcade::STATUS Menu::loadOptions()
    {
        auto &text = this->texts_[this->selected_];
        switch (text.action) {
        case arcade::menu::TextAction::RETURN:
            return text.status;
        case arcade::menu::TextAction::REFRESH:
            this->option_.first = arcade::OPTIONS::RESTART;
            break;
        case arcade::menu::TextAction::LIBGAME:
            this->option_.first = arcade::OPTIONS::LOAD_GAME;
            this->option_.second = "lib/" + text.text;
            break;
        case arcade::menu::TextAction::LIBGRAPH:
            this->option_.first = arcade::OPTIONS::LOAD_GRAPH;
            this->option_.second = "lib/" + text.text;
            break;
        }
        return arcade::STATUS::OPTION;
    }

    void Menu::addText(arcade::menu::Text text)
    {
        this->texts_.push_back(text);
        std::sort(this->texts_.begin(), this->texts_.end(), [](const auto &lhs, const auto &rhs) {
            return (lhs.y != rhs.y ? lhs.y < rhs.y : lhs.x < rhs.x);
        });
    }

};// namespace arcade::menu

extern "C" const arcade::LibType getType()
{
    return arcade::LibType::GAME;
}

extern "C" std::unique_ptr<arcade::IGame> createGame()
{
    return std::make_unique<arcade::menu::Menu>();
}
