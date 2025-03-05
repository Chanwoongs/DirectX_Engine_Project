#pragma once

#include <d3d11.h>

#include "Vector3.h"
#include "Matrix4.h"

namespace DirectxEngine
{
    class Transform
    {
    public:
        Transform();
        ~Transform();

        void Bind();

    private:
        // 트랜스폼(변환) 요소(TRS).
        Vector3 position = Vector3::Zero;
        Vector3 rotation = Vector3::Zero;
        Vector3 scale = Vector3::One;

    private:
        // 트랜스폼 행렬.
        Matrix4 transformMatrix;

        // 상수 버퍼.
        ID3D11Buffer* constantBuffer = nullptr;
    };
}