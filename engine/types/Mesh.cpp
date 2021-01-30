#include "Mesh.hpp"

#include "Loggger.hpp"

#include "tracy/Tracy.hpp"

Mesh::Mesh() {}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint> &indicies)
    : m_vertices(vertices), m_indicies(indicies)
{
}

Mesh::~Mesh()
{
    if (m_load_future.valid())
        m_load_future.wait();
}

void Mesh::load_from_file(const std::string &file)
{
    m_load_future = std::async(std::launch::async, &Mesh::load_file_worker, this, file);
}

void Mesh::load_file_worker(std::string file)
{
    ZoneScopedN("Load Mesh");

    auto data = load_obj_model(file);

    std::lock_guard<std::mutex> lock(m_load_mutex);

    m_vertices = data.first;
    m_indicies = data.second;

    if (m_vertices.size())
        LOG_DF("Loaded mesh [{}]", file);
}
