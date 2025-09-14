#include <WorldGen/Chunk.hpp>
#include "Utils.hpp"


namespace WorldGen
{
	const std::vector<GLfloat> Chunk::shaderComponents = { 3, 3 };

	Chunk::Chunk() {}
	Chunk::Chunk(const glm::vec3 &position)
			: position(position)
	{
		gen(position);
	}

	void Chunk::gen(const glm::vec3 &position)
	{
		this->position = position;
		Sprites::BlockType blockType;
		saveBounds();

		for (int y = 0; y < baseSize.y; y++)
		{
			if (y > baseSize.y - 2) blockType = Sprites::BlockType::GRASS;
			else if (y > baseSize.y - 5) blockType = Sprites::BlockType::DIRT;
			else blockType = Sprites::BlockType::STONE;
			chunkLayers.emplace_back(glm::vec3(position.x, y, position.z), blockType);
		}
		const unsigned long layers = chunkLayers.size();
		for (int layerI = 0; layerI < layers; layerI++)
		{
			auto &layer = chunkLayers[layerI];
			for (int x = 0; x < baseSize.x; x++)
			{
				for (int z = 0; z < baseSize.y; z++)
				{
					const unsigned int i = baseSize.x * x + z;
					auto &[pos, type] = layer.blocks[i];
					if (type == Sprites::BlockType::AIR)
					{
						layer.airBlocks++;
						continue;
					}
					uint8_t faces = 0;
					if (z + 1 >= baseSize.y || chunkLayers[layerI].blocks[baseSize.x * x + (z + 1)].type == Sprites::BlockType::AIR)
						faces |= Sprites::SpriteSheetFace::FRONT;
					if (z - 1 < 0 || chunkLayers[layerI].blocks[baseSize.x * x + (z - 1)].type == Sprites::BlockType::AIR)
						faces |= Sprites::SpriteSheetFace::BACK;
					if (x - 1 < 0 || chunkLayers[layerI].blocks[baseSize.x * (x - 1) + z].type == Sprites::BlockType::AIR)
						faces |= Sprites::SpriteSheetFace::LEFT;
					if (x + 1 >= baseSize.x || chunkLayers[layerI].blocks[baseSize.x * (x + 1) + z].type == Sprites::BlockType::AIR)
						faces |= Sprites::SpriteSheetFace::RIGHT;
					if (layerI + 1 >= chunkLayers.size() || chunkLayers[layerI + 1].blocks[i].type == Sprites::BlockType::AIR)
						faces |= Sprites::SpriteSheetFace::TOP;
					if (layerI - 1 < 0 || chunkLayers[layerI - 1].blocks[i].type == Sprites::BlockType::AIR)
						faces |= Sprites::SpriteSheetFace::BOTTOM;
					if (faces == 0)
						continue;
					AppendCubeDetailedData(pos, type, vertices, indices, faces);
				}
			}
		}

		genAtom.store(true);
	}

	void Chunk::saveBounds()
	{
		/* From position populate a bounds mat that will have all 4 corners */
		/* It should be calculated from position but it need some math, remember the chunks are baseSize (this is a ivec2 with x and z sizes) */
		/* The bounds should be a 2x4 matrix */

		glm::vec2 origin = glm::vec2(
			fmod(position.x, baseSize.x),
			fmod(position.z, baseSize.y)
		);
		if (origin.x < 0)
			origin.x *= -1;
		if (origin.y < 0)
			origin.y *= -1;

		origin.x = position.x - origin.x;
		origin.y = position.z - origin.y;

		bounds[0] = glm::ivec2(origin.x, origin.y);
		bounds[1] = glm::ivec2(origin.x + baseSize.x, origin.y + baseSize.y);
	}

	bool Chunk::isInside(const glm::vec3 &pos) const
	{
		return pos.x >= bounds[0].x && pos.x <= bounds[1].x &&
				pos.z >= bounds[0].y && pos.z <= bounds[1].y;
	}

	void Chunk::createVAO()
	{
		vao = new VAO(vertices, indices, shaderComponents);
		if (!vao)
			throw std::runtime_error("Failed to create VAO, maybe out of memory?");
		vaoCreated = true;
	}



	void Chunk::Draw()
	{
		if (!genAtom.load() || !vaoCreated)
			return;

		vao->Bind();
		glDrawElements(GL_TRIANGLES, vao->verticesNum, GL_UNSIGNED_INT, nullptr);
		vao->Unbind();
	}

	ChunkLayer::ChunkLayer(const glm::vec3 &pos, const Sprites::BlockType &type)
	{
		for (int x = 0; x < Chunk::baseSize.x; x++)
		{
			for (int z = 0; z < Chunk::baseSize.y; z++)
			{
				blocks[Chunk::baseSize.x * x + z] = {glm::vec3(pos.x + x, pos.y, pos.z + z), type};
			}
		}
	}

	void ChunkLayer::Update()
	{
		for (auto [pos, type] : blocks)
		{
			if (type == Sprites::BlockType::AIR)
				airBlocks++;
		}
	}

	Chunk::~Chunk()
	{
		delete vao;
	}
}
