#include "TriangleMesh.h"

namespace DirectxEngine
{
    TriangleMesh::TriangleMesh()
    {
        // 정점 배열.
        std::vector<Vertex> vertices =
        {
            Vertex(Vector3(0.0f, 0.5f, 0.5f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f)),
            Vertex(Vector3(-0.5f, -0.5f, 0.5f))
        };

        // 인덱스 배열.
        std::vector<uint32> indices = { 0, 1, 2 };

        meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
        shaders.emplace_back(std::make_shared<Shader>());
    }
}