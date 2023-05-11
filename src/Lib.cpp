/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Lib.cpp
*/

#include "Lib.hpp"

namespace arcade {
    Lib::Lib(const std::string &path)
    {
        this->loadLib(path);
    }

    void Lib::loadLib(const std::string &path)
    {
        spdlog::info("Loading lib: {}", path);
        this->lib_ = dlopen(path.c_str(), RTLD_LAZY);
        if (!this->lib_) {
            throw std::runtime_error("Error: " + std::string(dlerror()));
        }
        this->path_ = path;
        spdlog::debug("\t==> Done !");
    }

    void Lib::closeLib()
    {
        spdlog::info("Closing lib {}", this->path_);
        if (!this->lib_) {
            spdlog::warn("\t==> no lib loaded! (ignoring)");
            return;
        }
        dlclose(this->lib_);
        spdlog::debug("\t==> Done !");
        this->lib_ = nullptr;
    }

    Lib::~Lib()
    {
        this->closeLib();
    }

    std::string Lib::getPath() const
    {
        return this->path_;
    }
}// namespace arcade
