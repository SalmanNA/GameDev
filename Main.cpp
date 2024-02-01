//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include"cubeRenderer.h"
#include <vector>



const unsigned int width = 1920;
const unsigned int height = 1080;


//side(left = -), up. forward(away = -)
// Vertices coordinates
std::vector<GLfloat> vertices = {
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

	 0.0f, 0.0f,  0.0f,     0.92f, 0.86f, 0.76f,	0.0f, 0.0f,
	50.0f, 0.0f,  0.0f,     0.92f, 0.86f, 0.76f,	0.0f, 0.0f,
	 0.0f, 0.0f,  50.0f,     0.92f, 0.86f, 0.76f,	0.0f, 0.0f,
	 0.0f, 0.0f,  -50.0f,     0.92f, 0.86f, 0.76f,	0.0f, 0.0f,
	 -50.0f, 0.0f,  0.0f,     0.92f, 0.86f, 0.76f,	0.0f, 0.0f,


};


std::vector<GLuint> indices = {
	//// Bottom face
	//0, 1, 2,
	//2, 3, 0,

	//// Top face
	//4, 5, 6,
	//6, 7, 4,

	//// Left face
	//8, 9, 10,
	//10, 11, 8,

	//// Right face
	//12, 13, 14,
	//14, 15, 12,

	//// Front face
	//16, 17, 18,
	//18, 19, 16,

	//// Back face
	//20, 21, 22,
	//22, 23, 20,
	
	24, 25, 26,       
	24, 25, 27,
	24,27,28,
	24,26,28


};


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);


	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	CubeRenderer cubeRenderer;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			cubeRenderer.addBlock(static_cast<float>(i), -1.0f, static_cast<float>(j),15,0, 15, 2, 15, 3, 15, 3, 15, 3, 15, 3);
		}
	}
	cubeRenderer.Initialize(shaderProgram);
	// Generates Vertex Array Object and binds it
	VAO VAO;
	VAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices, vertices.size() * sizeof(float));
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices, indices.size() * sizeof(int));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();



	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/

	// Original code from the tutorial
	Texture brickTex("atlas2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);



	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
		Camera camera(width, height, glm::vec3(0.0f, 0.0f, 10.0f));
	// Main while loop
		camera.Position.y = 1.6f;
	while (!glfwWindowShouldClose(window))
	{
		std::cout << vertices.size();
		camera.Inputs(window,cubeRenderer.vertices);
		std::cout << camera.Position.x << " " << camera.Position.y << " " << camera.Position.z << std::endl;
		//if (!camera.CheckCollision(newPosition)) {
		//	// If no collision, update the camera's position
		//	camera.Move(glm::vec3(0.0f, deltaY, 0.0f));
		//}
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Handles camera inputs
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(100.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		/*glDrawElements(GL_TRIANGLES, (indices.size() * sizeof(int)) / sizeof(int), GL_UNSIGNED_INT, 0);*/
		VAO.Unbind();
		cubeRenderer.Render(shaderProgram);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();

	}



	// Delete all the objects we've created
	VAO.Delete();
	VBO.Delete();
	EBO.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}