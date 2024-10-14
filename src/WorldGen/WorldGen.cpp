#include <WorldGen/WorldGen.hpp>

#include <Camera.hpp>

#include "WorldGen/Block.hpp"

namespace WorldGen
{
	CubeData CreateCubeDataNew(const glm::vec3 &position, const Sprites::BlockType &blockType, const std::vector<GLuint> &indices)
	{
		const unsigned int baseIndex = indices.empty() ? 0: indices.back() + 4;
		constexpr float backTexCoordsX = 1.0f / 6;
		constexpr float leftTexCoordsX = 2.0f / 6;
		constexpr float rightTexCoordsX = 3.0f / 6;
		constexpr float topTexCoordsX = 4.0f / 6;
		constexpr float bottomTexCoordsX = 5.0f / 6;
		constexpr float faceWidth = 1.0f / 6;

		const auto blockTypeFloat = static_cast<float>(blockType);

		return {
			.vertices = {
		        // Positions                // Texture Coords                    // Block Type
		        // Front face
		        position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,   0,		  0,		    blockTypeFloat,
		        position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,   faceWidth, 0,			blockTypeFloat,
		        position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,   faceWidth, 1,   blockTypeFloat,
		        position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,   0,		  1,   blockTypeFloat,

		        // Back face
		        position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,   backTexCoordsX + faceWidth, 0,   blockTypeFloat,
		        position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,   backTexCoordsX + faceWidth, 1,   blockTypeFloat,
		        position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,   backTexCoordsX, 1,   blockTypeFloat,
		        position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,   backTexCoordsX, 0,   blockTypeFloat,

		        // Left face
		        position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,   leftTexCoordsX, 0,   blockTypeFloat,
		        position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,   leftTexCoordsX + faceWidth, 0,   blockTypeFloat,
		        position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,   leftTexCoordsX + faceWidth, 1,   blockTypeFloat,
		        position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,   leftTexCoordsX, 1,   blockTypeFloat,

		        // Right face
		        position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,   rightTexCoordsX + faceWidth, 0,   blockTypeFloat,
		        position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,   rightTexCoordsX + faceWidth, 1,   blockTypeFloat,
		        position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,   rightTexCoordsX, 1,   blockTypeFloat,
		        position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,   rightTexCoordsX, 0,   blockTypeFloat,

		        // Top face
		        position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,   topTexCoordsX, 1,   blockTypeFloat,
		        position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,   topTexCoordsX, 0,   blockTypeFloat,
		        position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,   topTexCoordsX + faceWidth, 0,   blockTypeFloat,
		        position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,   topTexCoordsX + faceWidth, 1,   blockTypeFloat,

		        // Bottom face
		        position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,   bottomTexCoordsX + faceWidth, 1,   blockTypeFloat,
		        position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,   bottomTexCoordsX, 1,   blockTypeFloat,
		        position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,   bottomTexCoordsX, 0,   blockTypeFloat,
		        position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,   bottomTexCoordsX + faceWidth, 0,   blockTypeFloat,
		    },
			.indices = {
				0 + baseIndex, 1 + baseIndex, 2 + baseIndex, 2 + baseIndex, 3 + baseIndex, 0 + baseIndex,         // Front face
				4 + baseIndex, 5 + baseIndex, 6 + baseIndex, 6 + baseIndex, 7 + baseIndex, 4 + baseIndex,         // Back face
				8 + baseIndex, 9 + baseIndex, 10 + baseIndex, 10 + baseIndex, 11 + baseIndex, 8 + baseIndex,      // Left face
				12 + baseIndex, 13 + baseIndex, 14 + baseIndex, 14 + baseIndex, 15 + baseIndex, 12 + baseIndex,   // Right face
				16 + baseIndex, 17 + baseIndex, 18 + baseIndex, 18 + baseIndex, 19 + baseIndex, 16 + baseIndex,   // Top face
				20 + baseIndex, 21 + baseIndex, 22 + baseIndex, 22 + baseIndex, 23 + baseIndex, 20 + baseIndex    // Bottom face
			},
			.blockType = blockType
		};
	}
	void CreateCubeData(const glm::vec3 &position, const Sprites::BlockType &face, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, unsigned int indicesOffset)
	{
	    // Get texture coordinates for each face from the sprite sheet
	    /*constexpr glm::vec2 frontTexCoords = {0.0f / 6, 0.0f};
	    constexpr glm::vec2 backTexCoords = {1.0f / 6, 0.0f};
	    constexpr glm::vec2 leftTexCoords = {2.0f / 6, 0.0f};
	    constexpr glm::vec2 rightTexCoords = {3.0f / 6, 0.0f};
	    constexpr glm::vec2 topTexCoords = {4.0f / 6, 0.0f};
	    constexpr glm::vec2 bottomTexCoords = {5.0f / 6, 0.0f};*/

		/*constexpr float frontTexCoordsX = 0.0f / 6;*/
		constexpr float backTexCoordsX = 1.0f / 6;
		constexpr float leftTexCoordsX = 2.0f / 6;
		constexpr float rightTexCoordsX = 3.0f / 6;
		constexpr float topTexCoordsX = 4.0f / 6;
		constexpr float bottomTexCoordsX = 5.0f / 6;

	    const auto blockType = static_cast<float>(face);
	    constexpr float faceWidth = 1.0f / 6;

		/*double time = glfwGetTime();*/

	    float cubeVertices[] = {
	        // Positions                // Texture Coords                    // Block Type
	        // Front face
	        position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,   0,		  0,		    blockType,
	        position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,   faceWidth, 0,			blockType,
	        position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,   faceWidth, 1,   blockType,
	        position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,   0,		  1,   blockType,

	        // Back face
	        position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,   backTexCoordsX + faceWidth, 0,   blockType,
	        position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,   backTexCoordsX + faceWidth, 1,   blockType,
	        position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,   backTexCoordsX, 1,   blockType,
	        position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,   backTexCoordsX, 0,   blockType,

	        // Left face
	        position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,   leftTexCoordsX, 0,   blockType,
	        position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,   leftTexCoordsX + faceWidth, 0,   blockType,
	        position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,   leftTexCoordsX + faceWidth, 1,   blockType,
	        position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,   leftTexCoordsX, 1,   blockType,

	        // Right face
	        position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,   rightTexCoordsX + faceWidth, 0,   blockType,
	        position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,   rightTexCoordsX + faceWidth, 1,   blockType,
	        position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,   rightTexCoordsX, 1,   blockType,
	        position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,   rightTexCoordsX, 0,   blockType,

	        // Top face
	        position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,   topTexCoordsX, 1,   blockType,
	        position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,   topTexCoordsX, 0,   blockType,
	        position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,   topTexCoordsX + faceWidth, 0,   blockType,
	        position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,   topTexCoordsX + faceWidth, 1,   blockType,

	        // Bottom face
	        position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,   bottomTexCoordsX + faceWidth, 1,   blockType,
	        position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,   bottomTexCoordsX, 1,   blockType,
	        position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,   bottomTexCoordsX, 0,   blockType,
	        position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,   bottomTexCoordsX + faceWidth, 0,   blockType,
	    };

		//vertices.reserve(vertices.size() + 144);
	    // Append vertices to the vector
	    vertices.insert(vertices.end(), std::begin(cubeVertices), std::end(cubeVertices));
		//vertices.assign(cubeVertices, cubeVertices + Block::numVertices);

	    // Define the indices for the cube (as before)
	    unsigned int baseIndex;
		if (indicesOffset == 0)
			baseIndex = vertices.size() / 6 - 24;
		else
			baseIndex = indicesOffset;


	    unsigned int faceIndices[] = {
	        0 + baseIndex, 1 + baseIndex, 2 + baseIndex, 2 + baseIndex, 3 + baseIndex, 0 + baseIndex,         // Front face
	        4 + baseIndex, 5 + baseIndex, 6 + baseIndex, 6 + baseIndex, 7 + baseIndex, 4 + baseIndex,         // Back face
	        8 + baseIndex, 9 + baseIndex, 10 + baseIndex, 10 + baseIndex, 11 + baseIndex, 8 + baseIndex,      // Left face
	        12 + baseIndex, 13 + baseIndex, 14 + baseIndex, 14 + baseIndex, 15 + baseIndex, 12 + baseIndex,   // Right face
	        16 + baseIndex, 17 + baseIndex, 18 + baseIndex, 18 + baseIndex, 19 + baseIndex, 16 + baseIndex,   // Top face
	        20 + baseIndex, 21 + baseIndex, 22 + baseIndex, 22 + baseIndex, 23 + baseIndex, 20 + baseIndex    // Bottom face
	    };

	    // Append indices to the vector
		//indices.reserve(indices.size() + 36);
		//indices.assign(faceIndices, faceIndices + Block::numIndices);
		indices.insert(indices.end(), std::begin(faceIndices), std::end(faceIndices));


		/*double time2 = glfwGetTime();
		std::cout << "Time to create cube data: " << (time2 - time) * 1000 << " ms" << std::endl;*/
	}

	void CreateCubeLineData(const glm::vec3 &position, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
	{
		GLfloat cubeVertices[] = {
			// Front face
			position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,  // 0: Bottom-left-front
			position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,  // 1: Bottom-right-front
			position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,  // 2: Top-right-front
			position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,  // 3: Top-left-front
			// Back face
			position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,  // 4: Bottom-left-back
			position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,  // 5: Bottom-right-back
			position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,  // 6: Top-right-back
			position.x - 0.5f, position.y + 0.5f, position.z - 0.5f   // 7: Top-left-back
		};

		// Populate vertices vector
		vertices.assign(cubeVertices, cubeVertices + Block::numVerticesLine); // 8 vertices * 3 components per vertex

		// Define the edges of the cube using line segments
		GLuint cubeIndices[] = {
			// Front face
			0, 1, 1, 2, 2, 3, 3, 0,
			// Back face
			4, 5, 5, 6, 6, 7, 7, 4,
			// Connecting edges
			0, 4, 1, 5, 2, 6, 3, 7,
			5, 4, 7, 6, 1, 0, 2, 3
		};

		// Populate indices vector
		indices.assign(cubeIndices, cubeIndices + Block::numIndicesLine); // 12 lines * 2 endpoints per line
	}

	void generateChunk(const glm::vec3 & pos, const glm::vec3 & dir, const glm::vec3 & size, Sprites::BlockType name, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
	{
		//this sould create a size.x * size.y * size.z chunk of cubes
		glm::vec3 curr_pos = pos + dir;
		glm::ivec3 bounds = size;

		for (int i = 0; i < bounds.x; i++)
		{
			for (int j = 0; j < bounds.y; j++)
			{
				for (int k = 0; k < bounds.z; k++)
				{
					CreateCubeData(curr_pos + glm::vec3(i,j,k), name, vertices, indices);
				}
			}
		}
	}
	void generateChunk(const glm::mat3x3 &mat, Sprites::BlockType name, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
	{
		generateChunk(mat[0], mat[1], mat[2], name, vertices, indices);
	}
	void generateFloor(const glm::vec3 &pos, const glm::ivec2 &size, Sprites::BlockType name, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
	{
		glm::vec3 start_pos = pos - glm::vec3(size.x / 2, 0, size.y / 2);
		glm::ivec2 isize = size;
		for (int i = 0; i < isize.x; i++)
		{
			for (int j = 0; j < isize.y; j++)
			{
				CreateCubeData(start_pos + glm::vec3(i, 0, j), name, vertices, indices);
			}
		}
	}
}

