// cubeRenderer.cpp
#include "cubeRenderer.h"

CubeRenderer::CubeRenderer() {}

CubeRenderer::~CubeRenderer() {}

void CubeRenderer::Initialize(Shader &shaderProgram) {
    cubeVAO;
    cubeVAO.Bind();
    cubeVBO = VBO(vertices, sizeof(vertices));
    cubeEBO = EBO(indices, sizeof(indices));

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

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    cubeVAO.Unbind();
    cubeTexture.Unbind();
}
