#include "chunkLoader.h"
chunkLoader::chunkLoader(Shader shaderProgram) {
	cubeRenderer.addBlock(static_cast<float>(2), 0.0f, static_cast<float>(2), 15, 0, 15, 2, 15, 3, 15, 3, 15, 3, 15, 3);
	cubeRenderer.addBlock(static_cast<float>(2), 1.0f, static_cast<float>(2), 15, 0, 15, 2, 15, 3, 15, 3, 15, 3, 15, 3);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			cubeRenderer.addBlock(static_cast<float>(i), -1.0f, static_cast<float>(j), 15, 0, 15, 2, 15, 3, 15, 3, 15, 3, 15, 3);
		}
	}for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			cubeRenderer.addBlock(static_cast<float>(i), -2.0f, static_cast<float>(j), 15, 2, 15, 2, 15, 2, 15, 2, 15, 2, 15, 2);
		}
	}
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			cubeRenderer.addBlock(static_cast<float>(i), -3.0f, static_cast<float>(j), 15, 2, 15, 2, 15, 2, 15, 2, 15, 2, 15, 2);
		}
	}
	for (float k = -4.0f; k > -16.0f; k--) {
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				cubeRenderer.addBlock(static_cast<float>(i), k, static_cast<float>(j), 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1);
			}
		}
	}


	cubeRenderer.Initialize(shaderProgram);
}

chunkLoader::~chunkLoader() {}
