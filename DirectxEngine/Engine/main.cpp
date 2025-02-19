#include <Windows.h>

#include <iostream>

#include "Core/Engine.h"
#include "Render/Texture.h"

using namespace DirectxEngine;

int main()
{
    Engine engine(1280, 800, TEXT("Engine Demo"), GetModuleHandle(nullptr));
    engine.Run();
}