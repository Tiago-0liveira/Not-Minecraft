#ifndef SPRITEMANAGER_HPP
#define SPRITEMANAGER_HPP

#include <iostream>
#include <unordered_map>
#include <map>
#include <format>
#include <vector>
#include <string>
#include <array>

#include <Graphics/SpriteSheet.hpp>

namespace Sprites
{
	enum BlockType
	{
		DIRT = 0,
		GRASS,
		COBBLESTONE,
		STONE,

		AIR,
		// Number of SpriteSheets
		NUM_SPRITESHEETS = AIR /* does not exist as a block */
	};
	std::ostream &operator<<(std::ostream &os, const BlockType &name);

	class SpriteManager
	{
	public:
		SpriteManager(const glm::ivec2 &imageSize = {SPRITE_SIZE, SPRITE_SIZE});
		~SpriteManager();

		const SpriteSheet &GetSpriteSheet(BlockType name) const;
		void useTextures() const;
		static void unuseTextures();

		void texUnit(Shader &shader, const char *uniform) const;

		static const char** getTextureNames() { return textureNames; }
		static const char* getTexName(const BlockType &name)
		{
			if (name >= BlockType::NUM_SPRITESHEETS)
				throw std::runtime_error(std::format("SpriteSheetName not found\n"));
			return textureNames[name];
		}
		static unsigned int getTextureCount() { return textureCount; }

	private:
		static const char *textureNames[NUM_SPRITESHEETS];
		static constexpr unsigned int textureCount = NUM_SPRITESHEETS;
		GLuint textureArrayID; // ID for the texture array
		std::vector<SpriteSheet> _sprites;
		glm::ivec2 imageSize; // Size for each sprite sheet
	};
}

inline std::ostream &operator<<(std::ostream &os, const Sprites::BlockType &name)
{
	os << Sprites::SpriteManager::getTexName(name);
	return os;
}

#endif //SPRITEMANAGER_HPP
