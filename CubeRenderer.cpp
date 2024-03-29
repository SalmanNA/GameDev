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
void CubeRenderer::addBlock(float x, float y, float z, int topTexRow, int topTexCol, int botTexRow, int botTexCol, int rightTexRow, int rightTexCol, int leftTexRow, int leftTexCol, int frontTexRow, int frontTexCol, int backTexRow, int backTexCol) {
    int atlasWidth = 256;
    int atlasHeight = 256;
    float texX = 16.0f / atlasWidth;  // Width of one cell divided by atlas width
    float texY = 16.0f / atlasHeight; // Height of one cell divided by atlas height
    // Calculate the index offset for the new block
    GLuint vertexOffset = vertices.size() / 8;

    float length = 1.0f; // Assuming the side length of the cube is 1
    // Front face
    // Bottom left
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * frontTexCol);
    vertices.push_back(texY * frontTexRow);

    // Bottom right
    vertices.push_back(x + length);
    vertices.push_back(y);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * frontTexCol)+ texX);
    vertices.push_back(texY * frontTexRow);

    // Top right
    vertices.push_back(x + length);
    vertices.push_back(y + length);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * frontTexCol)+ texX);
    vertices.push_back((texY * frontTexRow) + texY);

    // Top left
    vertices.push_back(x);
    vertices.push_back(y + length);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * frontTexCol);
    vertices.push_back((texY * frontTexRow) + texY);

    // Back face
    // Bottom left
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * backTexCol);
    vertices.push_back(texY * backTexRow);

    // Bottom right
    vertices.push_back(x + length);
    vertices.push_back(y);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * backTexCol)+ texX);
    vertices.push_back(texY * backTexRow);

    // Top right
    vertices.push_back(x + length);
    vertices.push_back(y + length);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * backTexCol)+ texX);
    vertices.push_back((texY * backTexRow) + texY);

    // Top left
    vertices.push_back(x);
    vertices.push_back(y + length);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * backTexCol);
    vertices.push_back((texY * backTexRow) + texY);

    // Top face
    // Bottom left
    vertices.push_back(x);
    vertices.push_back(y + length);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * topTexCol);
    vertices.push_back(texY * topTexRow);

    // Bottom right
    vertices.push_back(x + length);
    vertices.push_back(y + length);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * topTexCol)+ texX);
    vertices.push_back(texY * topTexRow);

    // Top right
    vertices.push_back(x + length);
    vertices.push_back(y + length);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * topTexCol)+ texX);
    vertices.push_back((texY * topTexRow) + texY);

    // Top left
    vertices.push_back(x);
    vertices.push_back(y + length);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * topTexCol);
    vertices.push_back((texY * topTexRow) + texY);

    // Bottom face
    // Bottom left
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * botTexCol);
    vertices.push_back(texY * botTexRow);

    // Bottom right
    vertices.push_back(x + length);
    vertices.push_back(y);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * botTexCol)+ texX);
    vertices.push_back(texY * botTexRow);

    // Top right
    vertices.push_back(x + length);
    vertices.push_back(y);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * botTexCol)+ texX);
    vertices.push_back((texY * botTexRow) + texY);

    // Top left
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * botTexCol);
    vertices.push_back((texY * botTexRow) + texY);

    // Left face
    // Bottom left
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * leftTexCol);
    vertices.push_back(texY * leftTexRow);

    // Bottom right
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * leftTexCol)+ texX);
    vertices.push_back(texY * leftTexRow);

    // Top right
    vertices.push_back(x);
    vertices.push_back(y + length);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * leftTexCol)+ texX);
    vertices.push_back((texY * leftTexRow) + texY);

    // Top left
    vertices.push_back(x);
    vertices.push_back(y + length);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * leftTexCol);
    vertices.push_back((texY * leftTexRow) + texY);

    // Right face
    // Bottom left
    vertices.push_back(x + length);
    vertices.push_back(y);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * rightTexCol);
    vertices.push_back(texY * rightTexRow);

    // Bottom right
    vertices.push_back(x + length);
    vertices.push_back(y);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * rightTexCol)+ texX);
    vertices.push_back(texY * rightTexRow);

    // Top right
    vertices.push_back(x + length);
    vertices.push_back(y + length);
    vertices.push_back(z + length);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back((texX * rightTexCol)+ texX);
    vertices.push_back((texY * rightTexRow) + texY);

    // Top left
    vertices.push_back(x + length);
    vertices.push_back(y + length);
    vertices.push_back(z);
    vertices.push_back(0.92f);
    vertices.push_back(0.86f);
    vertices.push_back(0.76f);
    vertices.push_back(texX * rightTexCol);
    vertices.push_back((texY * rightTexRow) + texY);



    // Add indices for the new block
    GLuint cubeIndices[] = {
    0, 1, 2, 2, 3, 0,    // Front face
    4, 5, 6, 6, 7, 4,    // Back face
    8, 9, 10, 10, 11, 8,  // Top face
    12, 13, 14, 14, 15, 12,  // Bottom face
    16, 17, 18, 18, 19, 16,  // Left face
    20, 21, 22, 22, 23, 20   // Right face

    };

    for (int i = 0; i < 36; i++) {
        indices.push_back(vertexOffset + cubeIndices[i]);
    }
}

