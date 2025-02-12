﻿#include "Engine.h"
#include "Window.h"
#include "../Render/Renderer.h"

namespace DirectxEngine
{
    // 싱글톤 객체 초기화
    Engine* Engine::Instance = nullptr;

    Engine::Engine(
        uint32 width, uint32 height,
        const std::wstring& title,
        HINSTANCE hInstance
    )
    {
        // 싱글톤 객체 값 설정
        Instance = this;

        // 창 객체 설정
        window = std::make_shared<Window>(width, height, title, hInstance, WindowProc);

        // 렌더러 생성.
        renderer = std::make_shared<Renderer>(width, height, window->Handle());
    }

    Engine::~Engine()
    {
    }

    void Engine::Run()
    {

        MSG msg = { };
        while (msg.message != WM_QUIT)
        {
            // 창에 메세지가 들어올 때 실행.
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // GetMessage는 메세지가 들어올 때 까지 대기한다.
            {
                // 메세지 번역.
                TranslateMessage(&msg);

                // 메세지 전달.
                DispatchMessage(&msg);
            }

            // 창에 메세지가 없을 때 다른 작업 처리.
            else
            {
                // 엔진 루프.
                renderer->Draw();
            }
        }
    }

    LRESULT Engine::WindowProc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
    {    
        // 메세지 처리.
        switch (message)
        {
            // 창이 삭제되면 실행됨.
        case WM_DESTROY:
            // 이때 프로그램 종료 메세지를 발생.
            PostQuitMessage(0);
            return 0;
        }

        // 기본 메세지 처리.
        return DefWindowProc(handle, message, wparam, lparam);
    }

    Engine& Engine::Get()
    {
        return *Instance;
    }
    ID3D11Device& Engine::Device() const
    {
        return *renderer->device;
    }
    ID3D11DeviceContext& Engine::Context() const
    {
        return *renderer->context;
    }
}