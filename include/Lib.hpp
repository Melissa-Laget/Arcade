/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Lib.hpp
*/

#pragma once

#include <dlfcn.h>
#include <functional>
#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>
#include <string>

namespace arcade {

    class Lib
    {
        public:
        Lib() = default;
        Lib(const std::string &path);
        Lib(const Lib &) = delete;
        Lib(Lib &&) = delete;
        Lib &operator=(const Lib &) = delete;
        Lib &operator=(Lib &&) = delete;
        virtual ~Lib();

        std::string getPath() const;

        void loadLib(const std::string &path);
        void closeLib();

        template<typename T> T *loadFunc(const std::string &funcName)
        {
            spdlog::debug("Loading function: {} from {}", funcName, this->path_);
            if (!this->lib_) {
                spdlog::error("\t==> no lib loaded !");
                throw std::runtime_error("Error: no lib loaded");
            }
            T *func = reinterpret_cast<T *>(dlsym(this->lib_, funcName.c_str()));
            if (!func) {
                spdlog::error("\t==> Error: {}", dlerror());
                throw std::runtime_error("Error: " + std::string(dlerror()));
            }
            spdlog::debug("\t==> Done !");
            return func;
        }

        template<class C> std::unique_ptr<C> loadClass(const std::string &classLoaderName)
        {
            spdlog::info("Loading class generator: {} from {}", classLoaderName, this->path_);
            if (!this->lib_) {
                spdlog::error("\t==> no lib loaded !");
                throw std::runtime_error("Error: no lib loaded");
            }
            auto create = this->loadFunc<std::unique_ptr<C>()>(classLoaderName);
            if (!create) {
                spdlog::error("\t==> Error: {}", dlerror());
                throw std::runtime_error("Error: " + std::string(dlerror()));
            }
            spdlog::debug("\t==> Done, generating class");
            return create();
        }

        template<class C, typename A> std::unique_ptr<C> loadClass(const std::string &classLoaderName, A arg)
        {
            spdlog::info("Loading class generator: {} from {}", classLoaderName, this->path_);
            if (!this->lib_) {
                spdlog::error("\t==> no lib loaded !");
                throw std::runtime_error("Error: no lib loaded");
            }
            auto create = this->loadFunc<std::unique_ptr<C>(A)>(classLoaderName);
            if (!create) {
                spdlog::error("\t==> Error: {}", dlerror());
                throw std::runtime_error("Error: " + std::string(dlerror()));
            }
            spdlog::info("\t==> Done, generating class");
            return create(arg);
        }

        private:
        void *lib_ = nullptr;
        std::string path_;
    };
}// namespace arcade
