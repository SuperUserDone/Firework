#include "Mesh.hpp"

Mesh::Mesh() {}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint> &indicies)
    : m_vertices(vertices), m_indicies(indicies)
{
}

Mesh::~Mesh() {}
