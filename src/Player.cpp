#include "Player.hpp"


Player::Player(GLFWwindow *window, int width, int height)
	: camera(window, width, height), vertices(WorldGen::Block::numVerticesLine), indices(WorldGen::Block::numIndicesLine)
{
	/*WorldGen::CubeData cubeData = WorldGen::CreateCubeData(camera.cameraPos, Sprites::STONE);*/
	WorldGen::CubeData cubeData = WorldGen::CreateCubeDataNew(camera.cameraPos, Sprites::STONE, indices);
	vertices.insert(vertices.end(), cubeData.vertices.begin(), cubeData.vertices.end());
	indices.insert(indices.end(), cubeData.indices.begin(), cubeData.indices.end());

	vao = new VAO(vertices, indices, { 3 });
	if (vao == nullptr)
		throw std::runtime_error("Failed to create VAO");
}

Player::~Player()
{
	delete vao;
}

void Player::Update()
{
	glm::vec3 direction;
	// Convert angles from degrees to radians
	const float yawRad = glm::radians(Camera::yaw);
	const float pitchRad = glm::radians(Camera::pitch);

	direction.x = cos(pitchRad) * cos(yawRad);
	direction.y = sin(pitchRad);
	direction.z = cos(pitchRad) * sin(yawRad);

	const auto dir = normalize(direction); // Normalize the vector
	glm::ivec3 newPos = camera.cameraPos + (dir * 3.0f);
	if (newPos != selectedBlockPos)
	{
		//std::cout << "New block selected: " << newPos.x << " " << newPos.y << " " << newPos.z << std::endl;
		selectedBlockPos = newPos;
		vertices.clear();indices.clear();
		WorldGen::CreateCubeLineData(newPos, vertices, indices);
		vao->UpdateBuffers(vertices, indices);
	}
}

void Player::Draw()
{
	vao->Bind();
	glDrawElements(GL_LINES, vao->verticesNum, GL_UNSIGNED_INT, nullptr);
	vao->Unbind();
}


