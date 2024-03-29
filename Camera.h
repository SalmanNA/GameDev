// In Camera.h

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaderClass.h"
#include <vector>

class Camera {
public:
    // Constructor
    Camera(int width, int height, glm::vec3 position);

    // Methods
    void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
    void Move(const glm::vec3& direction);
    void ProcessKeyboardInput(GLFWwindow* window, float deltaTime);
    void Inputs(GLFWwindow* window, std::vector<GLfloat> vertices);
    void Jump();
    void ApplyGravity(float gravity, float deltaTime, std::vector<GLfloat> vertices);
    void Update(float deltaTime, std::vector<GLfloat> vertices);
    void ResetVelocity();
    void ProcessMouseInput(GLFWwindow* window, float deltaTime);
    float CheckCollision(const glm::vec3& cameraPosition, const std::vector<GLfloat>& faceVertices);

    // Members
    glm::vec3 Position;
    glm::vec3 Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    int width;
    int height;
    bool firstClick = true;;
    float coll;
    float collSide;
    float collFront;
    bool side;
    bool top;

private:
    // Movement parameters
    float yaw = -90.0f;
    float pitch = 0.0f;
    float mouseSensitivity = 0.1f;
    double lastMouseX = 0.0;
    double lastMouseY = 0.0;
    float movementSpeed = 3.0f; // Adjust as needed
    float jumpSpeed = 4.0f;     // Adjust jump strength
    bool isJumping = false;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float floor = 1.6f;
};

#endif // CAMERA_H
