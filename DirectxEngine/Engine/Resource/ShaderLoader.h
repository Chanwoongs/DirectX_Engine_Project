#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <typeinfo>

namespace DirectxEngine
{
    class Shader;

    class ShaderLoader
    {
    public:
        ShaderLoader();
        ~ShaderLoader() = default;

        template<typename T, typename... Args, typename std::enable_if<std::is_base_of<Shader, T>::value>::type* = nullptr>
        bool Load(std::weak_ptr<T>& outShader, Args... args);

        static ShaderLoader& Get();

    private:
        static ShaderLoader* Instance;

        std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    };
}

#include "ShaderLoader.inl"