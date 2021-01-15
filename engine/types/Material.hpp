#pragma once

// TODO

#include <cstdint>

#include <optional>

class Renderer;

struct MaterialRenderInfo
{
    uint32_t texture;
    uint32_t shader;
};

class Material
{
public:
    Material();
    ~Material();

private:
    std::optional<MaterialRenderInfo> m_renderinfo;

    friend class Renderer;
};
