#pragma once

#include <algorithm>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "Loggger.hpp"
#include "types/Vertex.hpp"

inline std::pair<std::vector<Vertex>, std::vector<uint>> load_obj_model(const std::string &path)
{
    std::vector<glm::vec3> tmp_pos;
    std::vector<glm::vec3> tmp_norm;
    std::vector<glm::vec2> tmp_uv;

    std::vector<uint> vert_indicies;
    std::vector<uint> norm_indicies;
    std::vector<uint> uv_indicies;

    FILE *file = fopen(path.c_str(), "r");
    if (file == nullptr)
    {
        LOG_EF("Could not open file {}!", path);
        return std::pair<std::vector<Vertex>, std::vector<uint>>();
    }

    while (true)
    {
        char line_header[16];

        int res = fscanf(file, "%16s", line_header);
        if (res == EOF)
            break;

        if (strcmp(line_header, "v") == 0)
        {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

            tmp_pos.push_back(vertex);
        }
        else if (strcmp(line_header, "vt") == 0)
        {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);

            tmp_uv.push_back(uv);
        }
        else if (strcmp(line_header, "vn") == 0)
        {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);

            tmp_norm.push_back(normal);
        }
        else if (strcmp(line_header, "f") == 0)
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file,
                                 "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 &vertexIndex[0],
                                 &uvIndex[0],
                                 &normalIndex[0],
                                 &vertexIndex[1],
                                 &uvIndex[1],
                                 &normalIndex[1],
                                 &vertexIndex[2],
                                 &uvIndex[2],
                                 &normalIndex[2]);
            if (matches != 9)
            {
                LOG_EF("Unsupported obj file {}!", path);
                return std::pair<std::vector<Vertex>, std::vector<uint>>();
            }

            for (int i = 0; i < 3; i++)
            {
                vert_indicies.push_back(vertexIndex[i]);
                norm_indicies.push_back(normalIndex[i]);
                uv_indicies.push_back(uvIndex[i]);
            }
        }
    }

    std::vector<Vertex> verticies;
    std::vector<uint> indicies;

    for (auto &&index : vert_indicies)
    {
        Vertex vert;
        vert.pos = tmp_pos[index - 1];
        verticies.push_back(vert);
    }

    int index = 0;

    for (auto &&ind : norm_indicies)
    {
        verticies[index].normal = tmp_norm[ind - 1];
        index++;
    }

    index = 0;

    for (auto &&ind : norm_indicies)
    {
        verticies[index].uv = tmp_uv[ind - 1];
        index++;
    }

    for (int i = 0; i < verticies.size(); i++)
    {
        indicies.push_back(i);
    }

    return std::make_pair(verticies, indicies);
}