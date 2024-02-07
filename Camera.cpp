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
         // Ensure the camera stays at the ground level
    }
}

void Camera::Update(float deltaTime, std::vector<GLfloat> vertices)
{
    Position += Velocity * deltaTime;
    CheckCollision(Position, vertices);
    if (coll != 999) {
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
    glm::vec3 cameraMin = cameraPosition - glm::vec3(0.2f, 1.6f, 0.2f);
    glm::vec3 cameraMax = cameraPosition + glm::vec3(0.2f, 0.0f, 0.2f);

    // Check for collision with each face's bounding box
    for (int i = 0; i < faceVertices.size(); i += 192) {
        // Extract the vertices of the face
        glm::vec3 faceVertex1(faceVertices[i], faceVertices[i + 1], faceVertices[i + 2]);
        //1 2 3 
        //3 4 1
        // Calculate the bounding box of the face
        glm::vec3 overlap;
        glm::vec3 faceMin = glm::vec3(faceVertex1.x, faceVertex1.y, faceVertex1.z);
        glm::vec3 faceMax = glm::vec3(faceVertex1.x + 1.0f, faceVertex1.y + 1.0f, faceVertex1.z + 1.0f);
        overlap.x = std::max(0.0f, std::min(cameraMax.x, faceMax.x) - std::max(cameraMin.x, faceMin.x));
        overlap.y = std::max(0.0f, std::min(cameraMax.y, faceMax.y) - std::max(cameraMin.y, faceMin.y));
        overlap.z = std::max(0.0f, std::min(cameraMax.z, faceMax.z) - std::max(cameraMin.z, faceMin.z));
        if (overlap.x > 0.0f && overlap.y > 0.0f && overlap.z > 0.0f){
            if (overlap.x <= overlap.y && overlap.x <= overlap.z)
            {
                Move(glm::vec3(overlap.x, 0.0f, 0.0f));
            }
            else if (overlap.y <= overlap.x && overlap.y <= overlap.z)
            {
                Move(glm::vec3(0.0f, overlap.y, 0.0f));
            }
            else
            {
                Move(glm::vec3(0.0f, 0.0f, overlap.z));

            }

            coll = 998;
            return 998;
        }
        //float overlapX = std::min(cameraMax.x, faceMax.x) - std::max(cameraMin.x, faceMin.x);
        //float overlapY = std::min(cameraMax.y, faceMax.y) - std::max(cameraMin.y, faceMin.y);
        //float overlapZ = std::min(cameraMax.z, faceMax.z) - std::max(cameraMin.z, faceMin.z);


        //std::cout << "Overlap along Y-axis: " << overlapY << std::endl;

        //Move(glm::vec3(overlapX, overlapY, overlapZ));

        // If any of the above checks are true, there is no overlap
        // Otherwise, there is an overlap

        // Check for collision between camera and face bounding box
        //if (cameraMax.x >= faceMin.x && cameraMin.x <= faceMax.x &&
        //    cameraMax.y >= faceMin.y && cameraMin.y <= faceMax.y &&
        //    cameraMax.z >= faceMin.z && cameraMin.z <= faceMax.z) {
        //    int faceNumber = (i / 32) % 6;
        //    std::cout << faceMin.y << " " << faceMax.y << " " << Position.y << std::endl;
        //    if ((faceMin.y - cameraMin.y) < (faceMax.y - cameraMax.y)) {
        //        Move(glm::vec3(0.0f, (faceMin.y - cameraMin.y), 0.0f));
        //        coll = Position.y + (faceMin.y - cameraMin.y) + 1.6f;
        //    }
        //    else {
        //        coll = Position.y + (faceMax.y - cameraMax.y) + 1.6f;
        //    }
        //    return cameraPosition.y;
        //    // Collision detected
        //    // Check if the collision is on the top face of the side face
        //                // Check if the collision is on the side face
        //    //if (cameraPosition.y >= faceMin.y + 1.6f && cameraPosition.y <= faceMax.y + 1.6f) {
        //    //    // Collision detected on the side face

        //    //    coll = cameraPosition.y;
        //    //    return cameraPosition.y;
        //    //}


        //}
    }

    // No collision detected
    coll = 999;
    return 999;
}
