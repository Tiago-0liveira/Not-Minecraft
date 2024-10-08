#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"
#include "Graphics/Texture.hpp"

class ABlock
{
public:
	ABlock(const char *spriteSheet, const glm::vec2 &spriteSize);
	ABlock(const char *block_side, const char *block_top, const char *block_bottom);
	ABlock(const char *block);
	~ABlock();



private:
	const Texture Tex;
};

#endif //BLOCK_HPP
