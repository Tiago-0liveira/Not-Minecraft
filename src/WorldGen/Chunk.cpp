#include <random>
#include <WorldGen/Chunk.hpp>


namespace WorldGen
{
	const std::vector<GLfloat> Chunk::shaderComponents = { 3, 3 };

	Chunk::Chunk() {}
	Chunk::Chunk(const glm::vec3 &position)
			: position(position)
	{
		gen(position);
	}

	void Chunk::gen(const glm::vec3 &pos)
	{
		position = pos;
		vertices.reserve(baseSize.x * baseSize.y * size.z * Block::numVertices);
		indices.reserve(baseSize.x * baseSize.y * size.z * Block::numIndices);
		Sprites::BlockType blockType;

		for (int x = 0; x < size.x; x++)
		{
			for (int y = 0; y < baseSize.y; y++)
			{
				if (y > baseSize.y - 2) blockType = Sprites::BlockType::GRASS;
				else if (y > baseSize.y - 5) blockType = Sprites::BlockType::DIRT;
				else blockType = Sprites::BlockType::COBBLESTONE;
				for (int z = 0; z < size.z; z++)
				{
					const int idx = x + (y * size.x) + (z * size.x * baseSize.y);
					auto &[pos, type] = blocks[idx];
					pos = glm::vec3(x, y, z) + position;
					type = blockType;
					WorldGen::CreateCubeData(pos, blockType, vertices, indices);
				}
			}
		}

		genAtom.store(true);
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

	Chunk::~Chunk()
	{
		delete vao;
	}
}
