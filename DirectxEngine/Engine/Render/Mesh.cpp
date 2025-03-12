#include "Mesh.h"

#include "../Core/Engine.h"
#include "../Shader/Shader.h"

namespace DirectxEngine
{
    MeshData::MeshData()
    {
    }

    MeshData::MeshData(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices)
    {
        // 파라미터 복사.
        this->vertices.assign(vertices.begin(), vertices.end());
        stride = Vertex::Stride();
        this->indices.assign(indices.begin(), indices.end());

        // 리소스 생성.
        // 버퍼(Buffer) - 메모리 덩어리.
        D3D11_BUFFER_DESC vertexBufferDesc = { };
        vertexBufferDesc.ByteWidth = stride * (uint32)vertices.size();
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        // 정점 데이터.
        D3D11_SUBRESOURCE_DATA vertexData = { };
        vertexData.pSysMem = vertices.data();

        // 장치 얻어오기
        auto& device = Engine::Get().Device();

        // 버퍼 생성.
        HRESULT result = device.CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to create vertex buffer.", "Error", MB_OK);
            __debugbreak();
        }

        D3D11_BUFFER_DESC indexBufferDesc = { };
        indexBufferDesc.ByteWidth = sizeof(int) * (uint32)indices.size();
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        // 정점 데이터.
        D3D11_SUBRESOURCE_DATA indexData = { };
        indexData.pSysMem = indices.data();

        // 인덱스 버퍼 생성.
        result = device.CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to create index buffer.", "Error", MB_OK);
            __debugbreak();
        }
    }

    MeshData::~MeshData()
    {
        // 리소스 해제.
        if (vertexBuffer)
        {
            vertexBuffer->Release();
        }

        if (indexBuffer)
        {
            indexBuffer->Release();
        }
    }

    void MeshData::Bind()
    {
        // 컨텍스트 얻어오기.
        static auto& context = Engine::Get().Context();

        // 정점/인덱스 버퍼 바인딩.
        static uint32 offset = 0;
        context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    }

    void MeshData::UpdateVertexBuffer(const std::vector<Vertex>& vertices)
    {
        // 파라미터 복사.
        this->vertices.assign(vertices.begin(), vertices.end());

        // 정점 버퍼가 있으면, 해제 후 재생성.
        if (vertexBuffer)
        {
            vertexBuffer->Release();
            vertexBuffer = nullptr;
        }

        // 리소스 생성.
        // 버퍼(Buffer) - 메모리 덩어리.
        D3D11_BUFFER_DESC vertexBufferDesc = { };
        vertexBufferDesc.ByteWidth = stride * (uint32)vertices.size();
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        // 정점 데이터.
        D3D11_SUBRESOURCE_DATA vertexData = { };
        vertexData.pSysMem = vertices.data();

        // 장치 얻어오기
        auto& device = Engine::Get().Device();

        // 버퍼 생성.
        HRESULT result = device.CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
        if (FAILED(result))
        {
            MessageBoxA(nullptr, "Failed to create vertex buffer.", "Error", MB_OK);
            __debugbreak();
        }

    }

    Mesh::Mesh()
    {
    }

    void Mesh::Draw()
    {
        // 컨텍스트 얻어오기.
        static auto& context = Engine::Get().Context();

        // 트랜스폼 바인딩.
        transfrom.Bind();

        // 루프 순회하면서 바인딩 & 드로우.
        for (int i = 0; i < (int32)meshes.size(); i++)
        {
            auto shader = shaders[i].lock();
            if (!shader)
            {
                continue;
            }
            meshes[i]->Bind();
            shader->Bind();
            context.DrawIndexed(meshes[i]->IndexCount(), 0, 0);
        }
    }
}