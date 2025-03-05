#pragma once

#include "Mesh.h"

namespace DirectxEngine
{
    // 삼각형 메시 클래스.
    class QuadMesh : public Mesh
    {
    public:
        QuadMesh();

        void Update(float deltaTime);

    private:
        void Rotate(float angle);
    };
}