// cubeRenderer.h
#ifndef CUBE_RENDERER_H
#define CUBE_RENDERER_H

#include <glad/glad.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "shaderClass.h"

class CubeRenderer {
public:
    CubeRenderer();
    ~CubeRenderer();

    void Initialize(Shader& shaderProgra);
    void Render(Shader shader);
	GLfloat vertices[192] = {
		// Bottom face
		-0.5f, -0.5f,  0.5f,   0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.83f, 0.70f, 0.44f,	0.0f, 1.0f,

		// Top face
		-0.5f,  0.5f,  0.5f,   0.92f, 0.86f, 0.76f,	0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.92f, 0.86f, 0.76f,	1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   0.92f, 0.86f, 0.76f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.92f, 0.86f, 0.76f,	0.0f, 1.0f,

		// Left face
		-0.5f, -0.5f, -0.5f,   0.92f, 0.86f, 0.76f,	0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   0.92f, 0.86f, 0.76f,	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   0.92f, 0.86f, 0.76f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.92f, 0.86f, 0.76f,	0.0f, 1.0f,

		// Right face
		 0.5f, -0.5f, -0.5f,   0.92f, 0.86f, 0.76f,	0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.92f, 0.86f, 0.76f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.92f, 0.86f, 0.76f,	1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.92f, 0.86f, 0.76f,	0.0f, 1.0f,

		 // Front face
		 -0.5f, -0.5f,  0.5f,   0.92f, 0.86f, 0.76f,	0.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,   0.92f, 0.86f, 0.76f,	1.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,   0.92f, 0.86f, 0.76f,	1.0f, 1.0f,
		 -0.5f,  0.5f,  0.5f,   0.92f, 0.86f, 0.76f,	0.0f, 1.0f,

		 // Back face
		 -0.5f, -0.5f, -0.5f,   0.92f, 0.86f, 0.76f,	0.0f, 0.0f,
		  0.5f, -0.5f, -0.5f,   0.92f, 0.86f, 0.76f,	1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,   0.92f, 0.86f, 0.76f,	1.0f, 1.0f,
		 -0.5f,  0.5f, -0.5f,   0.92f, 0.86f, 0.76f,	0.0f, 1.0f,



	};


	GLuint indices[36] = {
		// Bottom face
		0, 1, 2,
		2, 3, 0,

		// Top face
		4, 5, 6,
		6, 7, 4,

		// Left face
		8, 9, 10,
		10, 11, 8,

		// Right face
		12, 13, 14,
		14, 15, 12,

		// Front face
		16, 17, 18,
		18, 19, 16,

		// Back face
		20, 21, 22,
		22, 23, 20,


	};
	VAO cubeVAO = VAO();
	VBO cubeVBO = VBO(vertices, sizeof(vertices));
	EBO cubeEBO = EBO(indices, sizeof(indices));
	Texture cubeTexture = Texture("cob.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
};

#endif // CUBE_RENDERER_H
