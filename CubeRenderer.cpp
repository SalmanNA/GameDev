// cubeRenderer.cpp
#include "cubeRenderer.h"

CubeRenderer::CubeRenderer() {}

CubeRenderer::~CubeRenderer() {}

void CubeRenderer::Initialize(Shader &shaderProgram) {
    cubeVAO;
    cubeVAO.Bind();
    cubeVBO = VBO(vertices, vertices.size() * sizeof(float));
    cubeEBO = EBO(indices, indices.size() * sizeof(int));

    cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    cubeVAO.LinkAttrib(cubeVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    cubeVAO.LinkAttrib(cubeVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    cubeVAO.Unbind();
    cubeVBO.Unbind();
    cubeEBO.Unbind();

    cubeTexture.texUnit(shaderProgram, "tex0", 0);
}

void CubeRenderer::Render(Shader shader) {
    shader.Activate();

    cubeTexture.Bind();
    cubeVAO.Bind();

    glDrawElements(GL_TRIANGLES, (indices.size() * sizeof(int)) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    cubeVAO.Unbind();
    cubeTexture.Unbind();
}
void CubeRenderer::addBlock(float x, float y, float z) {
    // Calculate the index offset for the new block
    GLuint vertexOffset = vertices.size() / 8;

    // Add vertices for the new block
    for (int i = 0; i < 8; i++) {
        vertices.push_back((i % 2 == 0) ? x - 0.5f : x + 0.5f);
        vertices.push_back((i / 4 == 0 || (i / 2) % 2 == 0) ? y - 0.5f : y + 0.5f);
        vertices.push_back((i / 4 == 0 || i / 2 == 1) ? z - 0.5f : z + 0.5f);
        vertices.push_back(0.92f); // Color values (adjust as needed)
        vertices.push_back(0.86f);
        vertices.push_back(0.76f);
        vertices.push_back((i % 2 == 0) ? 0.0f : 1.0f); // Texture coordinates
        vertices.push_back((i / 2 == 0) ? 0.0f : 1.0f);
    }

    // Add indices for the new block
    GLuint cubeIndices[] = {
        0, 1, 2, 2, 3, 0, // Front face
        1, 5, 6, 6, 2, 1, // Right face
        4, 7, 6, 6, 5, 4, // Back face
        0, 3, 7, 7, 4, 0, // Left face
        3, 2, 6, 6, 7, 3, // Top face
        0, 4, 5, 5, 1, 0  // Bottom face
    };

    for (int i = 0; i < 36; i++) {
        indices.push_back(vertexOffset + cubeIndices[i]);
    }
}

