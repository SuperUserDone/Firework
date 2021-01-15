#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include <glm/glm.hpp>

// TODO

class Renderer;

struct MeshRenderInfo
{
    uint32_t buffer;
    uint32_t vao;
    uint32_t index_buffer;
};

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec2 uv;
};

class Mesh
{
public:
    Mesh();
    Mesh(const std::vector<Vertex> &vertices, const std::vector<uint> &indicies);

    ~Mesh();

private:
    std::optional<MeshRenderInfo> m_renderinfo;

    std::vector<Vertex> m_vertices;
    std::vector<uint> m_indicies;

    friend class Renderer;
};
