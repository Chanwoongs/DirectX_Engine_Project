﻿#include "QuadMesh.h"

#include "Shader/TextureMappingShader.h"
#include "Resource/ShaderLoader.h"

namespace DirectxEngine
{
    QuadMesh::QuadMesh()
    {
        // 정점 배열.
        std::vector<Vertex> vertices =
        {
            Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
            Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f)),
            Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)),
        };

        // 인덱스 배열.
        std::vector<uint32> indices = { 0, 1, 2, 2, 3, 0 };

        meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));

        std::weak_ptr<TextureMappingShader> shader;
        if (ShaderLoader::Get().Load<TextureMappingShader>(shader, "Jjangu.png"))
        {
            shaders.emplace_back(shader);
        }
    }
}