#include <Windows.h>
#include "Core/Window.h"

using namespace DirectxEngine;

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
    //  창 생성.
    Window window(1280, 800, TEXT("Directx Engine Demo"), hInstance, WindowProc);

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
        }
    }

    return 0;
}