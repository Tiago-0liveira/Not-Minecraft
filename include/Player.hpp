#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "Camera.hpp"
#include "Graphics/VAO.hpp"
#include "WorldGen/Block.hpp"
#include "WorldGen/WorldGen.hpp"

class Player
{
public:
	Player(GLFWwindow *window, int width, int height);
	~Player();

	void Update();
	void Draw();

	Camera &getCamera() { return camera; }
	glm::ivec3 selectedBlockPos;
	VAO *vao = nullptr;
private:
	Camera camera;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
};

#endif //PLAYER_HPP
