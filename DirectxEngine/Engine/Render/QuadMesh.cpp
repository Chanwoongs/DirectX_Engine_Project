#include "QuadMesh.h"

namespace DirectxEngine
{
    QuadMesh::QuadMesh()
    {
        // 정점 배열.
        std::vector<Vertex> vertices =
        {
            Vertex(Vector3(-0.5f, -0.5f, 0.5f)),
            Vertex(Vector3(-0.5f, 0.5f, 0.5f)),
            Vertex(Vector3(0.5f, 0.5f, 0.5f)),
            Vertex(Vector3(0.5f, -0.5f, 0.5f))
        };

        // 인덱스 배열.
        std::vector<uint32> indice1 = { 0, 1, 2 };
        std::vector<uint32> indice2 = { 1, 2, 3 };

        meshes.emplace_back(std::make_shared<MeshData>(vertices, indice1));
        meshes.emplace_back(std::make_shared<MeshData>(vertices, indice2));
        shaders.emplace_back(std::make_shared<Shader>());
        shaders.emplace_back(std::make_shared<Shader>());
    }
}