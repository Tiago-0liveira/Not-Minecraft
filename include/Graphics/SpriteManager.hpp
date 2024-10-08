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
	enum SpriteSheetName
	{
		DIRT = 0,
		GRASS,
		COBBLESTONE,

		// Number of SpriteSheets
		NUM_SPRITESHEETS
	};
	std::ostream &operator<<(std::ostream &os, const SpriteSheetName &name);

	class SpriteManager
	{
	public:
		SpriteManager(const glm::ivec2 &imageSize = {512, 512});
		~SpriteManager();

		const SpriteSheet &GetSpriteSheet(SpriteSheetName name) const;
		void useTextures() const;
		static void unuseTextures();

		void texUnit(Shader &shader, const char *uniform) const;


		/*const SpriteSheet &GetSpriteSheet(SpriteSheetName name) const;*/

	private:
		GLuint textureArrayID; // ID for the texture array
		std::vector<SpriteSheet> _sprites;
		glm::ivec2 imageSize; // Size for each sprite sheet
	};
}

inline std::ostream &operator<<(std::ostream &os, const Sprites::SpriteSheetName &name)
{
	switch (name)
	{
		case Sprites::DIRT: os << "DIRT"; break;
		case Sprites::GRASS: os << "GRASS"; break;
		case Sprites::COBBLESTONE: os << "COBBLESTONE"; break;
		default : os << "UNKNOWN"; break;
	}
	return os;
}

#endif //SPRITEMANAGER_HPP
