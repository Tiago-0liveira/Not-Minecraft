#include <Graphics/ImguiDebugUi.hpp>

void ImguiTelemetry(float delta, Camera &cam, unsigned int triangles)
{
	static float fps = 0.0f, fpsMin = 10000.0f, fpsMax = 0.0f;
	static float fpsLastRead = glfwGetTime();
	static float frameTime = 0.0f;
	static bool vsync = true;

	if (glfwGetTime() - fpsLastRead >= 0.3f) {
		fpsLastRead = glfwGetTime();
		fps = setOneDecimal(1.0f / delta);
		frameTime = setOneDecimal(delta * 1000);
		if (fps < fpsMin) fpsMin = fps;
		if (fps > fpsMax) fpsMax = fps;
	}

	ImGui::Begin("Telemetry");

	ImGui::Text("Fps: %.1f  max: %.1f min: %.1f ", fps, fpsMax, fpsMin);
	if (ImGui::Checkbox("Vsync", &vsync))
	{
		glfwSwapInterval(vsync);
	}
	ImGui::Text("frame time: %.1f ms", frameTime);
	ImGui::Text("Cubes: %u Triangles: %u", triangles / 12,  triangles);
	ImGui::Text("Camera position: (%.1f, %.1f, %.1f)", cam.cameraPos.x, cam.cameraPos.y, cam.cameraPos.z);
	ImGui::Text("Camera pitch: %.1f yaw: %.1f", Camera::pitch, Camera::yaw);
	ImGui::SliderFloat("Speed", &Camera::speed, 4.5f, 50.0f);
	ImGui::SliderFloat("Fov", &cam.fov, 40.0f, 120.0f);

	ImGui::End();
}

void ImguiWorldGen(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, const Camera &cam, bool &hasToRegen)
{
	static float pos[] = {0.0f, 0.0f, 0.0f};
	const char *directions[] = {/*"PlayerEye", */"North", "East", "South", "West"};
	constexpr glm::vec3 directionsVec[] = {
		/*{0.0f, 0.0f, 0.0f},*/ {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}
	};
	static int directionIndex = 0;
	static int blockTypeIndex = 0;

	ImGui::Begin("World Gen");
	ImGui::InputFloat3("Position", pos);
	if (ImGui::Button("Delete All Blocks"))
	{
		vertices.clear();
		indices.clear();
		hasToRegen = true;
	}

	if (ImGui::Combo("Direction", &directionIndex, directions, IM_ARRAYSIZE(directions)))
	{
		// This block will execute when an option is selected
		/*ImGui::Text("You selected: %s", directions[directionIndex]);*/
	}
	if (ImGui::Combo("BlockType", &blockTypeIndex, Sprites::SpriteManager::getTextureNames(), Sprites::SpriteManager::getTextureCount()))
	{
		// This block will execute when an option is selected
		/*ImGui::Text("You selected: %s", Sprites::spriteSheetNames[blockTypeIndex]);*/
	}


	if (ImGui::CollapsingHeader("Chunk Gen"))
	{
		static int chunkSize[] = {1, 1, 1};
		ImGui::InputInt3("Chunk Size", chunkSize);
		if (ImGui::Button("Gen Chunk"))
		{
			WorldGen::generateChunk(glm::mat3x3(INT3_TO_VEC3(pos), directionsVec[directionIndex], INT3_TO_VEC3(chunkSize)), static_cast<Sprites::BlockType>(blockTypeIndex), vertices, indices);
			hasToRegen = true;
		}
	}
	if (ImGui::CollapsingHeader("Floor Gen"))
	{
		static int floorSize[] = {1, 1};
		ImGui::InputInt2("Floor Size", floorSize);
		if (ImGui::Button("Gen Floor"))
		{
			WorldGen::generateFloor(INT3_TO_VEC3(pos), INT2_TO_IVEC2(floorSize), static_cast<Sprites::BlockType>(blockTypeIndex), vertices, indices);
			hasToRegen = true;
		}
	}

	ImGui::End();
}