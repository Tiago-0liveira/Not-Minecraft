#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <glm/glm.hpp>
#include <Graphics/VAO.hpp>
#include "WorldGen/WorldGen.hpp"

#include <thread>
#include "Block.hpp"

namespace WorldGen
{
	#define CHUNKS_BASE_SIZE 16
	#define CHUNKS_HEIGHT 25

	class Chunk
	{
	public:
		Chunk();
		Chunk(const glm::vec3 &position);
		~Chunk();

		void gen(const glm::vec3 &position);
		void createVAO();
		void Draw();

		constexpr static auto size = glm::ivec3(CHUNKS_BASE_SIZE, CHUNKS_HEIGHT, CHUNKS_BASE_SIZE);
		constexpr static auto baseSize = glm::ivec2(CHUNKS_BASE_SIZE, CHUNKS_BASE_SIZE);
		bool vaoCreated = false;
		std::atomic<bool> genAtom{false};
	private:
		static const std::vector<GLfloat> shaderComponents;

		Block::BlockData blocks[baseSize.x * baseSize.y * size.z] = {};
		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;
		VAO *vao = nullptr;
		glm::vec3 position;
	};
}

#endif //CHUNK_HPP
