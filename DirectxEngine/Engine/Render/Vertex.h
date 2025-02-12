#pragma once

#include "../Math/Vector3.h"

namespace DirectxEngine
{
    class Vertex
    {
    public:
        Vertex(const Vector3 position)
            : position(position)
        {

        }
        ~Vertex() = default;
        static unsigned int Stride() { return sizeof(Vertex); }

    public:
        Vector3 position;

    private:

    };
}