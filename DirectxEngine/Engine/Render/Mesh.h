﻿#pragma once

#include <vector>
#include <d3d11.h>

#include "../Core/Type.h"
#include "Vertex.h"

namespace DirectxEngine
{
    // 메쉬 데이터 구조체.
    struct MeshData
    {
        MeshData();
        MeshData(
            const std::vector<Vertex>& vertices,
            const std::vector<uint32>& indices
        );
        ~MeshData();

        void Bind();
        uint32 IndexCount() const { return (uint32)indices.size(); }

        // 정점 데이터.
        std::vector<Vertex> vertices;
        uint32 stride = 0;
        ID3D11Buffer* vertexBuffer = nullptr;

        // 인덱스 데이터.
        std::vector<uint32> indices;
        ID3D11Buffer* indexBuffer = nullptr;
    };

    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

    private:

    };
}