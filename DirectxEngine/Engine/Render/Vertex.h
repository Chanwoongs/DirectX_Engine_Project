#pragma once

#include "Math/Vector3.h"
#include "Math/Vector2.h"

namespace DirectxEngine
{

    class Vertex
    {
    public:
        Vertex(const Vector3& position, const Vector3& color, const Vector2& texCoord)
            : position(position), color(color), texCoord(texCoord)
        {

        }
        ~Vertex() = default;
        static unsigned int Stride() { return sizeof(Vertex); }

    public:
        // 정점의 위치.
        Vector3 position;
        // 정점의 색상.
        Vector3 color;
        
        // 정점 기준 텍스쳐 좌표.
        Vector2 texCoord;
    };
}