#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <glm/glm.hpp>
#include <Graphics/VAO.hpp>
#include "WorldGen/WorldGen.hpp"
#include <random>

#include <thread>
#include "Block.hpp"

namespace WorldGen
{
	#define CHUNKS_BASE_SIZE 16
	#define CHUNKS_HEIGHT 25
	struct ChunkLayer;

	class Chunk
	{
	public:
		Chunk();
		Chunk(const glm::vec3 &position);
		~Chunk();

		void gen(const glm::vec3 &position);
		void saveBounds();
		bool isInside(const glm::vec3 &pos) const;
		void createVAO();
		void Draw();

		constexpr static auto size = glm::ivec3(CHUNKS_BASE_SIZE, CHUNKS_HEIGHT, CHUNKS_BASE_SIZE);
		constexpr static auto baseSize = glm::ivec2(CHUNKS_BASE_SIZE, CHUNKS_BASE_SIZE);
		bool vaoCreated = false;
		std::atomic<bool> genAtom{false};
	private:
		static const std::vector<GLfloat> shaderComponents;

		std::vector<ChunkLayer> chunkLayers;
		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;
		VAO *vao = nullptr;
		glm::vec3 position;
		glm::ivec2 bounds[2];
	};

	struct ChunkLayer
	{
		ChunkLayer(const glm::vec3 &pos, const Sprites::BlockType &type);

		void Update();

		Block::BlockData blocks[Chunk::baseSize.x * Chunk::baseSize.y];
		unsigned int airBlocks = 0;
	};
}

#endif //CHUNK_HPP
