#include <Windows.h>

#include <iostream>
#include <typeinfo>

#include "Core/Engine.h"
#include "Core/Common.h"
#include "Render/Texture.h"
#include "Shader/Shader.h"
#include "Shader/TextureMappingShader.h"

using namespace DirectxEngine;

template<typename T, typename std::enable_if<std::is_base_of<Shader, T>::value>::type* = nullptr>
void TestClass()
{
    std::boolalpha(std::cout); // true, false가 0, 1로.
    std::cout << typeid(T).name() << '\n';
    // 자손인지 확인.
    std::cout << std::is_base_of<Shader, T>::value << '\n';
}

int main()
{
    TestClass<TextureMappingShader>();
    
    Engine engine(1280, 800, TEXT("Engine Demo"), GetModuleHandle(nullptr));
    engine.Run();
}