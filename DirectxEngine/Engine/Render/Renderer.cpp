#include "Renderer.h"

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

        // 스왑 체인 정보 구조체
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
        swapChainDesc.BufferCount = 1;          // 백퍼버 개수
        swapChainDesc.SampleDesc.Count = 1;     // 멀티 샘플링 개수
        swapChainDesc.SampleDesc.Quality = 0;   // 멀티 샘플링 수준
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

        // 결과 확인
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to create devices.", "Error", MB_OK);
        }
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::Draw()
    {
    }
}