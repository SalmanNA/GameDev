#ifndef CHUCNK_LOADER_H
#define CHUCNK_LOADER_H

#include "cubeRenderer.h"

class chunkLoader
{
public:
	chunkLoader(Shader shaderProgram);
	~chunkLoader();
	CubeRenderer cubeRenderer;

};




#endif
