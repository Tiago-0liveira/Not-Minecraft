#include <Graphics/SpriteSheet.hpp>

namespace Sprites
{
	SpriteSheet::SpriteSheet(const char *path, const glm::ivec2 &imageSize)
	{
		if (imageSize.x != imageSize.y) {
			throw std::runtime_error(std::format("Image size must be square: x:%d y:%d\n", imageSize.x, imageSize.y));
		}
		int nrChannels;
		_data = stbi_load((SPRITE_BASE_PATH + path).c_str(), &pixels.x, &pixels.y, &nrChannels, 4);

		if (!_data)
			throw std::runtime_error(std::format("Failed to load texture: %s\n", path));

		size = {pixels.x / imageSize.x, pixels.y / imageSize.y};
		std::cout << "SpritSheet loaded: " << path << std::endl;
	}
	SpriteSheet::~SpriteSheet()
	{
		stbi_image_free(_data);
	}

	glm::vec2 SpriteSheet::GetImageCoords(SpriteSheetFace face) const
	{
		float u = (float) face / (float)size.x;
		float v = 0.0f;

		return glm::vec2(u, v);
	}


	const glm::vec2 SpriteSheet::GetSpriteSize() const
	{
		return size;
	}
}

