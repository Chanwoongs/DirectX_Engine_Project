﻿#include <Windows.h>

// 창 모드로 할 때 메인 함수 (Entry Point).
// system의 함수와 만든 함수의 스택 쌓이는 구조가 다르다.
// system 함수이기 때문에 WINAPI를 설정 __stdcall.
/*
WinMain(
    _In_ HINSTANCE hInstance,           // HINSTANCE: 핸들 값, 구조체 선언, 프로그램에 대한 포인터 값 관리.
    _In_opt_ HINSTANCE hPrevInstance,   // 안 쓴다.
    _In_ LPSTR lpCmdLine,               // LPSTR <- char*, 프로그램 실행할 때 파라미터. 안 쓴다.
    _In_ int nShowCmd                   // 창 모드 실행할 때 옵션. 안쓴다.
);
*/

LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
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

int WINAPI WinMain( 
    _In_ HINSTANCE hInstance,         
    _In_opt_ HINSTANCE hPrevInstance, 
    _In_ LPSTR lpCmdLine,             
    _In_ int nShowCmd                 
)
{
    // 창 생성.
    // 창에 사용할 클래스 이름
    const wchar_t* className = TEXT("Sample Window Class");    // TEXT <- L, 유니코드를 위해.

    // 창 생성에 필요한 설정 구조체.
    // 설정 안한 변수엔 Debug모드에선 쓰레기 값, Release에선 모르는 값이 들어간다.
    // { } 를 통해 0값으로 다 초기화한다.
    WNDCLASS wc = { };

    // 메세지 처리를 위한 콜백 전달.
    wc.lpfnWndProc = WindowProc;        // 윈도우 메세지에 대한 콜백 전달.
    // 프로그램 주소 전달.
    wc.hInstance = hInstance;
    // 창 생성에 사용할 클래스 이름 전달.
    wc.lpszClassName = className;

    // 클래스 등록.
    if (!RegisterClass(&wc))
    {
        // 오류 메세지 확인.
        auto error = GetLastError();

        // 메세지 출력.
        // #1. 출력창 이용 (Output).
        OutputDebugStringA("Failed to register a window class\n");
        
        // #2. 메세지 박스 이용
        MessageBoxA(nullptr, "Failed to register a window class", "Error", MB_OK);

        __debugbreak();
    }

    // 창 크기 설정
    unsigned int width = 1280;
    unsigned int height = 800;
    unsigned int positionX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    unsigned int positionY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

    // 창 생성.
    // HWND 창의 핸들 포인터 변수
    HWND hwnd = CreateWindow(
        className,                          // Window class
        TEXT("DirectX Engine Demo"),        // Window text
        WS_OVERLAPPEDWINDOW,                // Window style

        // Size and position (x, y, w, h)
        positionX, positionY, width, height,

        nullptr,        // Parent window    
        nullptr,        // Menu
        hInstance,      // Instance handle
        nullptr         // Additional application data
    );

    if (hwnd == nullptr)
    {
        // 메세지 출력.
        // #1. 출력창 이용 (Output).
        OutputDebugStringA("Failed to create a window\n");

        // #2. 메세지 박스 이용.
        MessageBoxA(nullptr, "Failed to create a window", "Error", MB_OK);

        __debugbreak();
    }

    // 창 보이기.
    ShowWindow(hwnd, SW_SHOW);

    // 창 메세지 업데이트.
    UpdateWindow(hwnd);

    MSG msg = { };
    while (msg.message != WM_QUIT) 
    {
        // 창에 메세지가 들어올 때 실행.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // GetMessage는 메세지가 들어올 때 까지 대기한다.
        {
            // 메세지 번역
            TranslateMessage(&msg);

            // 메세지 전달.
            DispatchMessage(&msg);
        }

        // 창에 메세지가 없을 때 다른 작업 처리.
        else
        {
            // 엔진 루프.
        }
    }

    return 0;
}