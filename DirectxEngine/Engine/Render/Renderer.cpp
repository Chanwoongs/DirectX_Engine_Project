#include "Renderer.h"

#include <vector>
#include <d3dcompiler.h>

#include "../Math/Vector3.h"
#include "../Shader/Shader.h"

namespace DirectxEngine
{
    Renderer::Renderer(uint32 width, uint32 height, HWND window)
    {
        // 장치 생성에 사용하는 옵션.
        uint32 flag = 0;

#if _DEBUG
        flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0
        };

        // 스왑 체인 정보 구조체.
        //DXGI_MODE_DESC BufferDesc;
        //DXGI_SAMPLE_DESC SampleDesc;
        //DXGI_USAGE BufferUsage;
        //UINT BufferCount;
        //HWND OutputWindow;
        //BOOL Windowed;
        //DXGI_SWAP_EFFECT SwapEffect;
        //UINT Flags;

        DXGI_SWAP_CHAIN_DESC swapChainDesc = { };
        swapChainDesc.Windowed = true;
        swapChainDesc.OutputWindow = window;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 1;          // 백퍼버 개수.
        swapChainDesc.SampleDesc.Count = 1;     // 멀티 샘플링 개수.
        swapChainDesc.SampleDesc.Quality = 0;   // 멀티 샘플링 수준.
        swapChainDesc.BufferDesc.Width = width;
        swapChainDesc.BufferDesc.Height = height;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        // 장치 생성.
        HRESULT result = D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            flag,
            featureLevels,
            _countof(featureLevels),
            D3D11_SDK_VERSION,
            &swapChainDesc,
            &swapChain,
            &device,
            nullptr,
            &context
        );

        // 결과 확인.
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to create devices.", "Error", MB_OK);
            __debugbreak();
        }

        // 렌더 타겟 뷰 생성.
        // I 가 붙은건 그래픽 카드와 실제 소통하는 객체들
        ID3D11Texture2D* backBuffer = nullptr;
        //swapChain->GetBuffer(0, __uuidof(backBuffer), reinterpret_cast<void**>(&backBuffer));
        result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to get back buffer.", "Error", MB_OK);
            __debugbreak();
        }

        result = device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to create render target view.", "Error", MB_OK);
            __debugbreak();
        }

        // 렌더 타켓 뷰 바인딩 (연결). OM -> output merger, IA -> input assembler.
        context->OMSetRenderTargets(1, &renderTargetView, nullptr);

        // 뷰 포트 (화면).
        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;
        viewport.Width = (float)width;
        viewport.Height = (float)height;
        viewport.MaxDepth = 1.0f;
        viewport.MinDepth = 0.0f;

        // 뷰포트 설정.
        context->RSSetViewports(1, &viewport);

        // 정점 데이터 생성
        Vector3 vertices[] =
        {
            Vector3(0.0f, 0.5f, 0.5f),
            Vector3(0.5f, -0.5f, 0.5f),
            Vector3(-0.5f, -0.5f, 0.5f),
        };
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::Draw()
    {
        if (shader == nullptr)
        {
            shader = std::make_unique<Shader>();
        }

        // 그리기 전 작업 (BeginScene).
        // 지우기.
        float color[] = { 0.5f, 0.2f, 0.1f, 1.0f };
        context->ClearRenderTargetView(renderTargetView, color);

        // 드로우 (Draw, Render).
        // 리소스 바인딩.
        // 정점 버퍼 전달.
        static unsigned int stride = Vector3::Stride();
        static unsigned int offset = 0;
        context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

        shader->Bind();

        // 인덱스 버퍼 전달.
        context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

        // 드로우콜.
        context->DrawIndexed(3, 0, 0);

        // 버퍼 교환 (EndScene, Present).
        swapChain->Present(1u, 0u);     // SyncInterval: 모니터 V-sync에 주사율 맞출 건지.
    }
}