#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Graphics/Texture.hpp"

class Block
{
public:
	Block(const char *block_side, const char *block_top, const char *block_bottom);
	Block(const char *block);
	~Block();

	Texture &texture;
};

#endif //BLOCK_HPP
