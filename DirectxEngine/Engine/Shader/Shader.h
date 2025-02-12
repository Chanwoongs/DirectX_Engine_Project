#pragma once

#include <string>
#include <d3d11.h>

namespace DirectxEngine
{
    class Shader
    {
    public:
        Shader(const std::wstring& name = L"Default");
        virtual ~Shader();

        // GPU에 Shader 객체를 연결(바인딩)
        virtual void Bind();

    protected:
        // 쉐이더 이름.
        std::wstring name;

        // DX 리소스
        ID3D11InputLayout* inputLayout = nullptr;

        ID3D11VertexShader* vertexShader = nullptr;
        ID3DBlob* vertexShaderBuffer = nullptr;

        ID3D11PixelShader* pixelShader = nullptr;
        ID3DBlob* pixelShaderBuffer = nullptr;
    };
}