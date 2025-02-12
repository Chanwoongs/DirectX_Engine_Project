#include "Shader.h"

#include <d3dcompiler.h>

#include "../Core/Engine.h"

namespace DirectxEngine 
{
    Shader::Shader(const std::wstring& name)
        : name(name)
    {
        // 경로 추가
        wchar_t path[256] = { };
        swprintf_s(path, 256, L"HLSLShader/%sVertexShader.hlsl", name.c_str());

        // 쉐이더 컴파일.
        HRESULT result = D3DCompileFromFile(
            path,
            nullptr,
            nullptr,
            "main",
            "vs_5_0",
            0, 0,
            &vertexShaderBuffer,
            nullptr
        );
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to compile vertex shader.", "Error", MB_OK);
            __debugbreak();
        }

        // 장치 객체 얻어오기
        auto& device = Engine::Get().Device();

        // 쉐이더 생성.
        result = device.CreateVertexShader(
            vertexShaderBuffer->GetBufferPointer(),
            vertexShaderBuffer->GetBufferSize(),
            nullptr,
            &vertexShader
        );
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to create vertex shader.", "Error", MB_OK);
            __debugbreak();
        }

        // 입력 레이아웃.
        // 정점 쉐이더에 전달할 정점 데이터가 어떻게 생겼는지 알려줌.
        //LPCSTR SemanticName;
        //UINT SemanticIndex;
        //DXGI_FORMAT Format;
        //UINT InputSlot;
        //UINT AlignedByteOffset;
        //D3D11_INPUT_CLASSIFICATION InputSlotClass;
        //UINT InstanceDataStepRate;
        D3D11_INPUT_ELEMENT_DESC inputDesc[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
            D3D11_INPUT_PER_VERTEX_DATA, 0}
        };
        result = device.CreateInputLayout(
            inputDesc,
            1,
            vertexShaderBuffer->GetBufferPointer(),
            vertexShaderBuffer->GetBufferSize(),
            &inputLayout
        );
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to create input layout.", "Error", MB_OK);
            __debugbreak();
        }

        // 픽셀 쉐이더, 컴파일, 생성.
        // 각 리소스 바인딩.
        // 쉐이더 컴파일.
        swprintf_s(path, 256, L"HLSLShader/%sPixelShader.hlsl", name.c_str());

        result = D3DCompileFromFile(
            path,
            nullptr,
            nullptr,
            "main",
            "ps_5_0",
            0, 0,
            &pixelShaderBuffer,
            nullptr
        );
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to compile pixel shader.", "Error", MB_OK);
            __debugbreak();
        }

        // 쉐이더 생성.
        result = device.CreatePixelShader(
            pixelShaderBuffer->GetBufferPointer(),
            pixelShaderBuffer->GetBufferSize(),
            nullptr,
            &pixelShader
        );
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to create pixel shader.", "Error", MB_OK);
            __debugbreak();
        }

    }

    Shader::~Shader()
    {
        // DX 리소스 해제
        if (inputLayout)
        {
            inputLayout->Release();
        }

        if (vertexShader)
        {
            vertexShader->Release();
        }
        
        if (vertexShaderBuffer)
        {
            vertexShaderBuffer->Release();
        }

        if (pixelShader)
        {
            pixelShader->Release();
        }

        if (pixelShaderBuffer)
        {
            pixelShaderBuffer->Release();
        }
    }

    void Shader::Bind()
    {
        // 장치 문맥(DeviceContext) 얻어오기.
        static ID3D11DeviceContext& context = Engine::Get().Context();

        // 입력 레이아웃 전달.
        context.IASetInputLayout(inputLayout);

        // 조립할 모양 설정.
        context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // 쉐이더 설정.
        context.VSSetShader(vertexShader, nullptr, 0);
        context.PSSetShader(pixelShader, nullptr, 0);
    }
}