#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>

#include <iostream>
#include <array>
#include <set>
#include <format>

#include <Graphics/Shader.hpp>
#include <Graphics/openGLThings.hpp>

namespace Sprites
{
	enum SpriteSheetFace
	{
		FRONT = 0,
		BACK,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	class SpriteSheet
	{
	public:
		SpriteSheet() = default;
		/*
		 * faceCoords must be a array in the following order: FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM
		 */
		SpriteSheet(const char *path, const glm::ivec2 &imageSize = {512, 512});
		SpriteSheet(const SpriteSheet &other) = delete;
		~SpriteSheet();
		SpriteSheet &operator=(const SpriteSheet &other) = delete;
		SpriteSheet(SpriteSheet&& other) noexcept
		{
			*this = std::move(other);
		}

		SpriteSheet& operator=(SpriteSheet&& other) noexcept {
			if (this != &other) {
				_data = other._data;
				size = other.size;
				pixels = other.pixels;
				other._data = nullptr;
			}
			return *this;
		}

		glm::vec2 GetImageCoords(SpriteSheetFace face) const;

		const glm::vec2 GetSpriteSize() const;

		const unsigned char *getData() const { return _data; }

		glm::vec2 size;
		glm::ivec2 pixels;
	private:
		unsigned char* _data;
	};
}

inline std::ostream &operator<<(std::ostream &os, const Sprites::SpriteSheetFace &face)
{
	switch (face)
	{
		case Sprites::FRONT: os << "FRONT"; break;
		case Sprites::BACK: os << "BACK"; break;
		case Sprites::LEFT: os << "LEFT"; break;
		case Sprites::RIGHT: os << "RIGHT"; break;
		case Sprites::TOP: os << "TOP"; break;
		case Sprites::BOTTOM: os << "BOTTOM"; break;
		default :os << "UNKNOWN"; break;
	}
	return os;
}

#endif //SPRITESHEET_HPP
