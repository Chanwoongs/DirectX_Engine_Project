#include "ShaderLoader.h"
#include "Shader/Shader.h"

namespace DirectxEngine
{
    ShaderLoader* ShaderLoader::Instance = nullptr;

    ShaderLoader::ShaderLoader()
    {
        Instance = this;
    }
    ShaderLoader& ShaderLoader::Get()
    {
        return *Instance;
    }
}