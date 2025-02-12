#include <Windows.h>

#include <iostream>

#include "Core/Engine.h"

using namespace DirectxEngine;

int main()
{
    std::cout << "테스트\n";

    Engine engine(1280, 800, TEXT("Engine Demo"), GetModuleHandle(nullptr));
    engine.Run();
}