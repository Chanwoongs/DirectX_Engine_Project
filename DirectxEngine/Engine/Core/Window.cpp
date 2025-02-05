#include "Window.h"

namespace DirectxEngine
{
    Window::Window(
        uint32 width, 
        uint32 height, 
        const std::wstring& title, 
        HINSTANCE instance, 
        WNDPROC messageProcedure)
        : width(width), height(height), title(title), instance(instance)
    {
        // 창 생성에 필요한 설정 구조체.
        // 설정 안한 변수엔 Debug모드에선 쓰레기 값, Release에선 모르는 값이 들어간다.
        // { } 를 통해 0값으로 다 초기화한다.
        WNDCLASS wc = { };

        // 메세지 처리를 위한 콜백 전달.
        wc.lpfnWndProc = messageProcedure;        // 윈도우 메세지에 대한 콜백 전달.
        // 프로그램 주소 전달.
        wc.hInstance = instance;
        // 창 생성에 사용할 클래스 이름 전달.
        wc.lpszClassName = className.c_str();

        // 클래스 등록.
        if (!RegisterClass(&wc))
        {
            // 오류 메세지 확인.
            auto error = GetLastError();

            // 메세지 출력.
            // #1. 출력창 이용 (Output).
            OutputDebugStringA("Failed to register a window class\n");

            // #2. 메세지 박스 이용.
            MessageBoxA(nullptr, "Failed to register a window class", "Error", MB_OK);

            __debugbreak();
        }

        // 창 크기 설정.
        unsigned int positionX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
        unsigned int positionY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

        // 창 크기 조정.
        RECT rect = { 0, 0, (long)width, (long)height };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

        // 창 크기 재설정
        unsigned int windowWidth = rect.right - rect.left;
        unsigned int windowHeight = rect.bottom - rect.top;

        // 창 생성.
        // HWND 창의 핸들 포인터 변수.
        handle = CreateWindow(
            className.c_str(),                  // Window class
            title.c_str(),                      // Window text
            WS_OVERLAPPEDWINDOW,                // Window style

            // Size and position (x, y, w, h)
            positionX, positionY, windowWidth, windowHeight,

            nullptr,        // Parent window    
            nullptr,        // Menu
            instance,       // Instance handle
            nullptr         // Additional application data
        );

        if (handle == nullptr)
        {
            // 메세지 출력.
            // #1. 출력창 이용 (Output).
            OutputDebugStringA("Failed to create a window\n");

            // #2. 메세지 박스 이용.
            MessageBoxA(nullptr, "Failed to create a window", "Error", MB_OK);

            __debugbreak();
        }

        // 창 보이기.
        ShowWindow(handle, SW_SHOW);

        // 창 메세지 업데이트.
        UpdateWindow(handle);
    }

    Window::~Window()
    {
        // 클래스 등록 해제.
        UnregisterClass(className.c_str(), instance);
    }

    void Window::SetWidthHeight(uint32 width, uint32 height)
    {
        this->width = width;
        this->height = height;
    }
}