#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Graphics/Shader.hpp>

#include <Camera.hpp>
#include <Graphics/EBO.hpp>
#include <Graphics/VAO.hpp>
#include <Graphics/VBO.hpp>
#include <Graphics/SpriteSheet.hpp>
#include <Graphics/SpriteManager.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


float setOneDecimal(const float f)
{
	return std::floor(f * 10) / 10;
}

void CreateCubeData(const glm::vec3 position, const Sprites::SpriteSheetName &face, std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    // Get texture coordinates for each face from the sprite sheet
	glm::vec2 frontTexCoords = {0.0f / 6, 0.0f};
    glm::vec2 backTexCoords = {1.0f / 6, 0.0f};
    glm::vec2 leftTexCoords = {2.0f / 6, 0.0f};
    glm::vec2 rightTexCoords = {3.0f / 6, 0.0f};
    glm::vec2 topTexCoords = {4.0f / 6, 0.0f};
    glm::vec2 bottomTexCoords = {5.0f / 6, 0.0f};

	float blockType = static_cast<float>(face);
    // Calculate the width and height of each individual face texture
    float faceWidth = 1.0f / 6; // Assuming size is glm::ivec2 holding the number of sprites in x and y
    float faceHeight = 1.0f / 1;

    float cubeVertices[] = {
        // Positions                // Texture Coords                    // Block Type
        // Front face
        position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,   frontTexCoords.x, frontTexCoords.y,   blockType,
        position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,   frontTexCoords.x + faceWidth, frontTexCoords.y,   blockType,
        position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,   frontTexCoords.x + faceWidth, frontTexCoords.y + faceHeight,   blockType,
        position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,   frontTexCoords.x, frontTexCoords.y + faceHeight,   blockType,

        // Back face
        position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,   backTexCoords.x + faceWidth, backTexCoords.y,   blockType,
        position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,   backTexCoords.x + faceWidth, backTexCoords.y + faceHeight,   blockType,
        position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,   backTexCoords.x, backTexCoords.y + faceHeight,   blockType,
        position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,   backTexCoords.x, backTexCoords.y,   blockType,

        // Left face
        position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,   leftTexCoords.x, leftTexCoords.y,   blockType,
        position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,   leftTexCoords.x + faceWidth, leftTexCoords.y,   blockType,
        position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,   leftTexCoords.x + faceWidth, leftTexCoords.y + faceHeight,   blockType,
        position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,   leftTexCoords.x, leftTexCoords.y + faceHeight,   blockType,

        // Right face
        position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,   rightTexCoords.x + faceWidth, rightTexCoords.y,   blockType,
        position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,   rightTexCoords.x + faceWidth, rightTexCoords.y + faceHeight,   blockType,
        position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,   rightTexCoords.x, rightTexCoords.y + faceHeight,   blockType,
        position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,   rightTexCoords.x, rightTexCoords.y,   blockType,

        // Top face
        position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,   topTexCoords.x, topTexCoords.y + faceHeight,   blockType,
        position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,   topTexCoords.x, topTexCoords.y,   blockType,
        position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,   topTexCoords.x + faceWidth, topTexCoords.y,   blockType,
        position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,   topTexCoords.x + faceWidth, topTexCoords.y + faceHeight,   blockType,

        // Bottom face
        position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,   bottomTexCoords.x + faceWidth, bottomTexCoords.y + faceHeight,   blockType,
        position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,   bottomTexCoords.x, bottomTexCoords.y + faceHeight,   blockType,
        position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,   bottomTexCoords.x, bottomTexCoords.y,   blockType,
        position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,   bottomTexCoords.x + faceWidth, bottomTexCoords.y,   blockType,
    };

    // Append vertices to the vector
    vertices.insert(vertices.end(), std::begin(cubeVertices), std::end(cubeVertices));

    // Define the indices for the cube (as before)
    const auto baseIndex = static_cast<unsigned int>(vertices.size() / 6 - 24);
    unsigned int faceIndices[] = {
        0, 1, 2, 2, 3, 0,         // Front face
        4, 5, 6, 6, 7, 4,         // Back face
        8, 9, 10, 10, 11, 8,      // Left face
        12, 13, 14, 14, 15, 12,   // Right face
        16, 17, 18, 18, 19, 16,   // Top face
        20, 21, 22, 22, 23, 20    // Bottom face
    };

    // Append indices to the vector
    for (const unsigned int faceIndice : faceIndices) {
        indices.push_back(baseIndex + faceIndice);
    }
}


void glfwErrorCallback(int error, const char* description) {
	std::cerr << "Erro GLFW [" << error << "]: " << description << std::endl;
}

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

int main() {
	stbi_set_flip_vertically_on_load(true);
	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit()) {
		std::cerr << "Falha ao inicializar o GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Criação da janela (800x600 pixels)
	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Basic GLFW Window", nullptr, nullptr);
	if (!window) {
		std::cerr << "Falha ao criar a janela GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Faz da janela o contexto atual
	glfwMakeContextCurrent(window);

	// Inicializa o GLEW para gerenciar extensões OpenGL
	glewExperimental = GL_TRUE; // GLEW precisa disso para core profile
	if (glewInit() != GLEW_OK) {
		std::cerr << "Falha ao inicializar o GLEW" << std::endl;
		return -1;
	}

	// Define a viewport (área de renderização)
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);


	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");

	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << version << std::endl;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	auto blockpos = glm::vec3(-2.0f);

	CreateCubeData(blockpos, Sprites::GRASS, vertices, indices);
	CreateCubeData(blockpos + glm::vec3(2.0f, 0.0f, 0.0f), Sprites::DIRT, vertices, indices);
	CreateCubeData(blockpos + glm::vec3(4.0f, 0.0f, 0.0f), Sprites::COBBLESTONE, vertices, indices);

	Sprites::SpriteManager sm;
	Shader shader("shaders/BlockTexture/default.vert", "shaders/BlockTexture/default.frag");

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices.data(), vertices.size() * sizeof(GLfloat));
	EBO EBO1(indices.data(), indices.size() * sizeof(GLuint));
	GLsizeiptr stride = 6 * sizeof(GLfloat);
	VAO1.LinkVBO(VBO1, 0, 3, GL_FLOAT, stride, nullptr);
	VAO1.LinkVBO(VBO1, 1, 3, GL_FLOAT, stride, reinterpret_cast<void *>(3 * sizeof(GLfloat)));
	VAO1.Unbind();
	EBO1.Unbind();

	// bind to the shader
	sm.texUnit(shader, "textureArray");

	Camera cam(window, WIN_WIDTH, WIN_HEIGHT);

	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {

		// Fps and frameTime
		float currentTime = glfwGetTime();
		float delta = currentTime - lastTime;
		float fps = 1.0f / delta;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Limpa o buffer de cores com uma cor de fundo (preto)
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.update(window, delta);

		shader.Activate();
		cam.VAOBind(shader.ID);


		sm.useTextures();

		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
		Sprites::SpriteManager::unuseTextures();

		ImGui::Begin("Telemetry");

		ImGui::Text("Fps: %.1f", setOneDecimal(fps));
		ImGui::Text("frame time: %.1f ms", setOneDecimal(delta * 1000));
		ImGui::Text("Triangles: %d", indices.size() / 3);
		//ImGui::Text("Mouse trapped: %s", cam.isMouseTrapped ? "true" : "false");
		ImGui::Text("Camera position: (%.1f, %.1f, %.1f)", cam.cameraPos.x, cam.cameraPos.y, cam.cameraPos.z);
		ImGui::Text("Camera pitch: %.1f yaw: %.1f", Camera::pitch, Camera::yaw);
		ImGui::SliderFloat("Speed", &Camera::speed, 4.5f, 50.0f);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwPollEvents();
		glfwSwapBuffers(window);

		// Atualiza lastTime
		lastTime = currentTime;
	}


	// Limpa os recursos do ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Limpa os recursos do OpenGL
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	// Limpa os recursos do GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}