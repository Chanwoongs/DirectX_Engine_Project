#pragma once

#include "Shader.h"
#include "memory"

namespace DirectxEngine
{
    class TextureMappingShader : public Shader
    {
    public:
        TextureMappingShader();
        TextureMappingShader(const std::string& textureName);
        ~TextureMappingShader() = default;

        virtual void Bind() override;

    private:
        // 텍스처 리소스.
        std::unique_ptr<class Texture> texture;
    };
}