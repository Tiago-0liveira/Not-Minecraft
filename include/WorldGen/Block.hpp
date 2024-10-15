#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <glm/glm.hpp>
#include "Graphics/SpriteManager.hpp"

namespace WorldGen::Block
{
	static constexpr unsigned int numVertices = 144;
	static constexpr unsigned int numIndices = 36;
	static constexpr unsigned int numVerticesLine = 24;
	static constexpr unsigned int numIndicesLine = 32;

	struct BlockData
	{
		glm::vec3 pos = {0, 0, 0};
		Sprites::BlockType type = Sprites::BlockType::AIR;
		// Eventually add a pointer to metaData
	};
} // namespace WorldGen::Block

#endif //BLOCK_HPP
