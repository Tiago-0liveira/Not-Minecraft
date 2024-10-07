#include <Camera.hpp>

float Camera::speed = 4.50f;
const float Camera::sensitivity = 0.1f;
const float Camera::nearest = 0.1f;
const float Camera::farthest = 100.0f;
float Camera::yaw = -50.0f;
float Camera::pitch = 0.0f;
const glm::vec3 Camera::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//const glm::vec3 cameraPosDefault = glm::vec3(0.5f, 2.0f, 7.0f);
const glm::vec3 cameraPosDefault = glm::vec3(-18.0f, 5.5f, 31.0f);

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (firstMouse) { // this is true initially
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	xoffset *= Camera::sensitivity;
	yoffset *= Camera::sensitivity;

	Camera::yaw += xoffset;
	Camera::pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (Camera::pitch > 89.0f)
		Camera::pitch = 89.0f;
	if (Camera::pitch < -89.0f)
		Camera::pitch = -89.0f;
}

void mouse_callbackImgui(GLFWwindow *window, double xpos, double ypos)
{
	ImGuiIO& io = ImGui::GetIO();

	io.MousePos = ImVec2(static_cast<float>(xpos), static_cast<float>(ypos));

	// Update mouse button states
	io.MouseDown[0] = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
	io.MouseDown[1] = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
	io.MouseDown[2] = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
}

Camera::Camera(GLFWwindow* window, int width, int height)
{
	view = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(fov), static_cast<float>(width) / static_cast<float>(height), nearest, farthest);
	cameraPos = cameraPosDefault;

	trapMouse(window);
}

void Camera::trapMouse(GLFWwindow *window)
{
	glfwSetCursorPos(window, lastX, lastY);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	isMouseTrapped = true;
}

void Camera::freeMouse(GLFWwindow *window)
{
	/* Actually bind it to imgui mouse Callback so we can use it */
	glfwSetCursorPosCallback(window, mouse_callbackImgui);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	isMouseTrapped = false;
}

Camera::~Camera() {}

void Camera::update(GLFWwindow* window, float delta)
{
	static float Gpressed = glfwGetTime();
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if ((glfwGetTime() - Gpressed >= KEY_PRESS_DELAY) && glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		Gpressed = glfwGetTime();
		if (isMouseTrapped)
			freeMouse(window);
		else
			trapMouse(window);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		/* Reset to begining */
		cameraPos = cameraPosDefault;
		yaw = -90.0f;
		pitch = 0.0f;
	}
	if (isMouseTrapped)
		keyboardMovement(window, delta);
}

void Camera::keyboardMovement(GLFWwindow* window, float delta)
{
	float velocity = speed * delta;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		velocity *= 2.0f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += velocity * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= velocity * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPos += cameraUp * velocity;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraPos -= cameraUp * velocity;
}

void Camera::VAOBind(GLuint ID)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}
