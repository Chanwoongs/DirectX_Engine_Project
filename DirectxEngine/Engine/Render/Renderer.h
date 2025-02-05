#pragma once

// DirectX11 헤더.
#include <d3d11.h>
#include <dxgi.h>

#include "../Core/Type.h"

namespace DirectxEngine
{
    // 그래픽 카드에서 처리하는 일 / 리소스를 관리하는 클래스.
    // RHI - Render Hardware Interface.
    class Renderer
    {
    public:
        Renderer(uint32 width, uint32 height, HWND window);
        ~Renderer();

        // 그리기 함수.
        void Draw();

    private:
        // 리소스.
        // 장치류.
        ID3D11Device* device = nullptr;             // 장치 담당.
        ID3D11DeviceContext* context = nullptr;     // 바인드, 드로우 콜 담당.
        IDXGISwapChain* swapChain = nullptr;        // 백 버퍼 관리 주체.

        // 버퍼.
        ID3D11RenderTargetView* renderTargetView = nullptr;

        // 뷰포트.
        D3D11_VIEWPORT viewport;
    };
}