//#include"Camera.h"
//#include <chrono>
//#include <thread>
//
//
//Camera::Camera(int width, int height, glm::vec3 position)
//{
//	Camera::width = width;
//	Camera::height = height;
//	Position = position;
//}
//
//void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
//{
//	// Initializes matrices since otherwise they will be the null matrix
//	glm::mat4 view = glm::mat4(1.0f);
//	glm::mat4 projection = glm::mat4(1.0f);
//
//	// Makes camera look in the right direction from the right position
//	view = glm::lookAt(Position, Position + Orientation, Up);
//	// Adds perspective to the scene
//	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
//
//	// Exports the camera matrix to the Vertex Shader
//	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
//}
//
//
//
//void Camera::Inputs(GLFWwindow* window)
//{
//	// Handles key inputs
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//	{
//		Position += speed * glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
//	}
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//	{
//		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
//	}
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//	{
//		Position += speed * -glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
//	}
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//	{
//		Position += speed * glm::normalize(glm::cross(Orientation, Up));
//	}
//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spaceKeyPressed)
//	{
//		for (int i = 0; i < 10; i++) {
//			Position += (2 * speed * Up) / 10.0f;
//
//		}
//		spaceKeyPressed = true;  // Set the flag to true to indicate the key is pressed
//	}
//	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
//	{
//		spaceKeyPressed = false; // Reset the flag when the key is released
//	}
//	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//	{
//		Position += speed * -Up;
//	}
//	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//	{
//		speed = 0.4f;
//	}
//	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
//	{
//		speed = 0.1f;
//	}
//
//
//	// Handles mouse inputs
//	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
//	{
//		// Hides mouse cursor
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
//
//		// Prevents camera from jumping on the first click
//		if (firstClick)
//		{
//			glfwSetCursorPos(window, (width / 2), (height / 2));
//			firstClick = false;
//		}
//
//		// Stores the coordinates of the cursor
//		double mouseX;
//		double mouseY;
//		// Fetches the coordinates of the cursor
//		glfwGetCursorPos(window, &mouseX, &mouseY);
//
//		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
//		// and then "transforms" them into degrees 
//		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
//		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;
//
//		// Calculates upcoming vertical change in the Orientation
//		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
//
//		// Decides whether or not the next vertical Orientation is legal or not
//		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
//		{
//			Orientation = newOrientation;
//		}
//
//		// Rotates the Orientation left and right
//		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
//
//		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
//		glfwSetCursorPos(window, (width / 2), (height / 2));
//	}
//	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
//	{
//		// Unhides cursor since camera is not looking around anymore
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//		// Makes sure the next time the camera looks around it doesn't jump
//		firstClick = true;
//	}
//}
//void Camera::Move(const glm::vec3& offset)
//{
//	Position += offset * Up;
//}
//
//bool Camera::CheckCollision(const glm::vec3& newPosition) {
//	// Assuming the camera has a bounding box (replace with your own logic)
//	glm::vec3 cameraMin = newPosition - glm::vec3(1.0f, 0.1f, 1.0f); // Adjust with your box dimensions
//	glm::vec3 cameraMax = newPosition + glm::vec3(1.0f, 0.1f, 1.0f);
//
//	// Assuming a ground surface with a bounding box
//	glm::vec3 groundMin = glm::vec3(-1000.0f, 0.0f, -1000.0f); // Adjust with your ground dimensions
//	glm::vec3 groundMax = glm::vec3(1000.0f, 0.0f, 1000.0f);
//
//	// Check for collision
//	if (cameraMax.x > groundMin.x && cameraMin.x < groundMax.x &&
//		cameraMax.y > groundMin.y && cameraMin.y < groundMax.y &&
//		cameraMax.z > groundMin.z && cameraMin.z < groundMax.z) {
//		return true; // Collision detected
//	}
//
//	return false; // No collision
//}
//
