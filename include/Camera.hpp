#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <imgui.h>

#define KEY_PRESS_DELAY 0.4f

inline float lastX = 400, lastY = 500;
inline bool firstMouse = true;


static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void mouse_callbackImgui(GLFWwindow *window, double xpos, double ypos);

class Camera
{
public:
	Camera(GLFWwindow* window, int width, int height);
	~Camera();

	void update(GLFWwindow* window, float delta);
	void VAOBind(GLuint ID);

	void trapMouse(GLFWwindow *window);
	void freeMouse(GLFWwindow *window);

	void keyboardMovement(GLFWwindow* window, float delta);

	static const float sensitivity;
	static float speed;
	static float yaw;
	static float pitch;
private:
	static const float nearest;
	static const float farthest;
	static const glm::vec3 cameraUp;
	glm::mat4 view, projection;
	float fov = 60.0f;

public:
	bool isMouseTrapped = true;
	glm::vec3 cameraPos, cameraFront;
};

#endif //CAMERA_HPP
