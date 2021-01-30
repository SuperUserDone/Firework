#pragma once

#include <cstdint>
#include <future>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Vertex.hpp"
#include "loader/obj_loader.hpp"

// TODO

class Renderer;

struct MeshRenderInfo
{
    uint32_t buffer;
    uint32_t vao;
    uint32_t index_buffer;
};

class Mesh
{
public:
    Mesh();
    Mesh(const std::vector<Vertex> &vertices, const std::vector<uint> &indicies);

    void load_from_file(const std::string &file);

    ~Mesh();

private:
    void load_file_worker(std::string file);

    std::optional<MeshRenderInfo> m_renderinfo;

    std::mutex m_load_mutex;
    std::future<void> m_load_future;

    std::vector<Vertex> m_vertices;
    std::vector<uint> m_indicies;

    friend class Renderer;
};
