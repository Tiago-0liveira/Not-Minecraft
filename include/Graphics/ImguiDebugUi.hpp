#ifndef IMGUIDEBUGUI_HPP
#define IMGUIDEBUGUI_HPP

#include <imgui.h>
#include <cmath>
#include <vector>
#include <Camera.hpp>
#include <WorldGen/WorldGen.hpp>

#define INT3_TO_VEC3(f) glm::vec3(f[0], f[1], f[2])
#define INT2_TO_IVEC2(f) glm::ivec2(f[0], f[1])

inline float setOneDecimal(const float f) { return std::floor(f * 10) / 10; }

void ImguiTelemetry(float delta, Camera &cam, unsigned int triangles);
void ImguiWorldGen(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, const Camera &cam, bool &hasToRegen);

#endif //IMGUIDEBUGUI_HPP
