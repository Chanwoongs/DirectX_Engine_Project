#include <Windows.h>

#include "Core/Window.h"
#include "Core/Engine.h"

#include "Render/Renderer.h"

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

int WINAPI WinMain( 
    _In_ HINSTANCE hInstance,         
    _In_opt_ HINSTANCE hPrevInstance, 
    _In_ LPSTR lpCmdLine,             
    _In_ int nShowCmd                 
)
{
    Engine engine(1280, 800, TEXT("Directx Engine Demo"), hInstance);

    engine.Run();

    return 0;
}