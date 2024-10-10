#ifndef WORLDGEN_HPP
#define WORLDGEN_HPP

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Graphics/SpriteManager.hpp"

namespace WorldGen
{
	void CreateCubeData(const glm::vec3 &position, const Sprites::BlockType &face, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, int indicesOffset = 0);
	void generateChunk(const glm::vec3 & pos, const glm::vec3 & dir, const glm::vec3 & size, Sprites::BlockType name, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateChunk(const glm::mat3x3 &mat, Sprites::BlockType name, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	void generateFloor(const glm::vec3 &pos, const glm::ivec2 &size, Sprites::BlockType name, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
}

#endif //WORLDGEN_HPP
