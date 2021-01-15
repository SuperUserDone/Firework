#include "Loggger.hpp"
#include "Renderer.hpp"

#include <glad/glad.h>

#include <tracy/Tracy.hpp>

Renderer::Renderer()
{
    init_window();
    init_opengl();
}

Renderer::~Renderer()
{
    cleanup_opengl();
    cleanup_window();
}

bool Renderer::check_close() { return m_close; }

void Renderer::begin_frame()
{
    FrameMarkStart("Render");

    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // TODO
}

void Renderer::end_frame()
{
    FrameMarkEnd("Render");

    SDL_GL_SwapWindow(m_window);
    window_events();

    // TODO
}

void Renderer::push_camera(const Camera &cam)
{
    // TODO
}

void Renderer::pop_camera()
{
    // TODO
}

void Renderer::draw_cube(Material *material, glm::mat4 transform)
{
    // TODO
}

void Renderer::draw_plane(Material *material, glm::mat4 transform)
{
    // TODO
}

void Renderer::draw_mesh(Mesh *mesh, Material *material, glm::mat4 transform)
{
    if (!material->m_renderinfo.has_value())
        load_material(material);

    if (!mesh->m_renderinfo.has_value())
        load_mesh(mesh);

    // ! TODO Temp

    glUseProgram(material->m_renderinfo->shader);

    glBindVertexArray(mesh->m_renderinfo->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // !

    // TODO
}

void Renderer::free_resource(Material *mat)
{
    // TODO
}

void Renderer::free_resource(Mesh *mesh)
{
    // TODO
}

void Renderer::free_resources()
{
    // TODO
}

void Renderer::window_events()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        m_close = true;
        break;
    }
}

void Renderer::load_mesh(Mesh *mesh)
{
    MeshRenderInfo info;

    glGenBuffers(1, &info.buffer);
    glGenBuffers(1, &info.index_buffer);
    glGenVertexArrays(1, &info.vao);

    glBindVertexArray(info.vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(uint) * mesh->m_indicies.size(),
                 &mesh->m_indicies[0],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, info.buffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vertex) * mesh->m_vertices.size(),
                 &mesh->m_vertices[0],
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    mesh->m_renderinfo = info;
}

void Renderer::load_material(Material *mat)
{
    // ! TODO temp
    MaterialRenderInfo info;

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOG_EF("ERROR::SHADER::VERTEX::COMPILATION_FAILED{}", infoLog);
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG_EF("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED{}", infoLog);
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LOG_EF("ERROR::SHADER::PROGRAM::LINKING_FAILED{}", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    info.shader = shaderProgram;
    mat->m_renderinfo = info;
    // !
}

void Renderer::init_window()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        LOG_RUNTIME_ERROR("Failed to init sdl!");

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // TODO load settings file
    m_window = SDL_CreateWindow(
        "ABC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

    if (m_window == nullptr)
        LOG_RUNTIME_ERROR("Failed to create window!");
}

void Renderer::init_opengl()
{
    m_GLContext = SDL_GL_CreateContext(m_window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        LOG_RUNTIME_ERROR("Failed to create GL context");

    LOG_D("Created Window and GL context sucessfully.");
}

void Renderer::cleanup_opengl() { SDL_GL_DeleteContext(m_GLContext); }

void Renderer::cleanup_window()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}