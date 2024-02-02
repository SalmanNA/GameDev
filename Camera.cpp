// In Camera.cpp

#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
    Camera::width = width;
    Camera::height = height;
    Position = position;
    Orientation = glm::vec3(0.0f, 0.0f, 0.0f);
    Up = glm::vec3(0.0f, 1.0f, 0.0f);
    
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Move(const glm::vec3& direction)
{
    Position += direction;
}

void Camera::Jump()
{
    if (!isJumping && coll != 999) { // Only allow jumping if the camera is at or below the ground level
        Velocity.y = jumpSpeed;
        
        isJumping = true;
    }
}

void Camera::ApplyGravity(float gravity, float deltaTime, std::vector<GLfloat> vertices)
{
    
    // Apply gravity only if the camera is above or at the ground level
    if (coll == 999)
        Velocity.y += gravity * deltaTime;
    else {
        //Velocity.y = 0.0f; // Stop gravity when at the ground
        Position.y = coll; // Ensure the camera stays at the ground level
    }
}

void Camera::Update(float deltaTime, std::vector<GLfloat> vertices)
{
    Position += Velocity * deltaTime;
    CheckCollision(Position, vertices);
    if (coll != 999) {
        Position.y = coll;
        Velocity.y = 0.0f;
        isJumping = false;
    }
}

void Camera::ResetVelocity()
{
    Velocity = glm::vec3(0.0f);
}

void Camera::ProcessKeyboardInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        Jump();

    glm::vec3 forward = glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
    glm::vec3 right = glm::normalize(glm::cross(forward, Up));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Move(forward * movementSpeed * deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Move(-forward * movementSpeed * deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Move(-right * movementSpeed * deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Move(right * movementSpeed * deltaTime);
}
void Camera::ProcessMouseInput(GLFWwindow* window, float deltaTime)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    float xoffset = static_cast<float>(xpos - lastMouseX);
    float yoffset = static_cast<float>(lastMouseY - ypos); // Reversed since y-coordinates range from bottom to top

    lastMouseX = xpos;
    lastMouseY = ypos;

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Limit the pitch to avoid camera flipping
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Update the orientation based on yaw and pitch
    Orientation.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    Orientation.y = sin(glm::radians(pitch));
    Orientation.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Orientation = glm::normalize(Orientation);
}

void Camera::Inputs(GLFWwindow* window, std::vector<GLfloat> vertices)
{
    //std::cout << Velocity.x << std::endl;
    //std::cout << Velocity.y << std::endl;
    //std::cout << Velocity.z << std::endl;
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Update(deltaTime, vertices);
    ProcessKeyboardInput(window, deltaTime);
    ProcessMouseInput(window, deltaTime);
    ApplyGravity(-9.8f, deltaTime, vertices);
}
float Camera::CheckCollision(const glm::vec3& cameraPosition, const std::vector<GLfloat>& faceVertices)
{
    // Assuming the camera has a bounding box (or bounding sphere)
    glm::vec3 cameraMin = cameraPosition - glm::vec3(0.0f, 1.6f, 0.0f);
    glm::vec3 cameraMax = cameraPosition + glm::vec3(0.0f, 1.6f, 0.0f);

    // Check for collision with each face's bounding box
    for (int i = 0; i < faceVertices.size(); i += 24) {
        // Extract the vertices of the face
        glm::vec3 faceVertex1(faceVertices[i], faceVertices[i + 1], faceVertices[i + 2]);
        glm::vec3 faceVertex2(faceVertices[i + 8], faceVertices[i + 9], faceVertices[i + 10]);
        glm::vec3 faceVertex3(faceVertices[i + 16], faceVertices[i + 17], faceVertices[i + 18]);

        // Calculate the bounding box of the face
        glm::vec3 faceMin = glm::min(glm::min(faceVertex1, faceVertex2), faceVertex3);
        glm::vec3 faceMax = glm::max(glm::max(faceVertex1, faceVertex2), faceVertex3);

        // Check for collision between camera and face bounding boxes
        if (cameraMax.x >= faceMin.x && cameraMin.x <= faceMax.x &&
            cameraMax.y >= faceMin.y && cameraMin.y <= faceMax.y &&
            cameraMax.z >= faceMin.z && cameraMin.z <= faceMax.z) {
            // Collision detected
            coll = cameraPosition.y;
            return cameraPosition.y;
        }
    }

    // No collision detected
    coll = 999;
    return 999;
}
