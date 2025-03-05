﻿#pragma once

#include <vector>
#include <d3d11.h>
#include <memory>

#include "../Core/Type.h"
#include "../Shader/Shader.h"
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
        virtual ~Mesh() = default;

        virtual void Draw();

    protected:
        std::vector<std::shared_ptr<MeshData>> meshes;
        //std::vector<std::shared_ptr<Shader>> shaders;
        std::vector<std::weak_ptr<Shader>> shaders;
    };
}