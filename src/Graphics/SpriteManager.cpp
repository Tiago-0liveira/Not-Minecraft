#include <Graphics/SpriteManager.hpp>

namespace Sprites
{
	const char *SpriteManager::textureNames[NUM_SPRITESHEETS] = {
		"DIRT",
		"GRASS",
		"COBBLESTONE",
		"STONE"
	};

	SpriteManager::SpriteManager(const glm::ivec2 &imageSize)
	: imageSize(imageSize)
	{
		_sprites.resize(NUM_SPRITESHEETS);
		_sprites[DIRT] = std::move(SpriteSheet("dirt.png"));
		_sprites[GRASS] = std::move(SpriteSheet("grass.png"));
		_sprites[COBBLESTONE] = std::move(SpriteSheet("cobblestone.png"));
		_sprites[STONE] = std::move(SpriteSheet("stone.png"));

		glGenTextures(1, &textureArrayID);
		glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayID);

		glm::ivec2 si = {imageSize.x * 6, imageSize.y};

		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, si.x, si.y, static_cast<int>(NUM_SPRITESHEETS), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		checkOpenGLErrors("SpriteManager::SpriteManager glTexImage3D");

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		checkOpenGLErrors("SpriteManager::SpriteManager glGenerateMipmap");
		// Upload each sprite sheet to the texture array
		for (GLint i = 0; i < _sprites.size(); ++i)
		{
			glm::ivec2 si2 = _sprites[i].pixels;
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, si2.x, si2.y, 1, GL_RGBA, GL_UNSIGNED_BYTE, _sprites[i].getData());
			checkOpenGLErrors("SpriteManager::SpriteManager glTexSubImage3D");
		}
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

	void SpriteManager::texUnit(Shader &shader, const char *uniform) const
	{
		glUniform1i(shader.GetUniformLocation(uniform), 0);
	}

	void SpriteManager::useTextures() const
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayID);
	}
	void SpriteManager::unuseTextures()
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

	SpriteManager::~SpriteManager() = default;

	const SpriteSheet &SpriteManager::GetSpriteSheet(BlockType name) const
	{
		auto n = static_cast<short>(name);
		if (n < 0 || n >= _sprites.size()) {
			throw std::runtime_error(std::format("SpriteSheet not found\n"));
		}
		return _sprites[n];
	}
}
