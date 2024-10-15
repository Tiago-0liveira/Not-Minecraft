#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <iostream>
#include <random>
#include <ctime>

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
#include <Graphics/ImguiDebugUi.hpp>
#include <WorldGen/WorldGen.hpp>

#include "Player.hpp"
#include "WorldGen/Chunk.hpp"
#include "WorldGen/World.hpp"


void glfwErrorCallback(int error, const char* description) {
	std::cerr << "Erro GLFW [" << error << "]: " << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Adjust the viewport to match the new window dimensions
	glViewport(0, 0, width, height);
}

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

int main()
{
	srand(std::time(nullptr));
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

	// Register the framebuffer size callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// Define a viewport (área de renderização)
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_CULL_FACE);


	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");

	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << version << std::endl;


	Sprites::SpriteManager sm;
	Shader ShaderBlockTextures("shaders/BlockTexture/default.vert", "shaders/BlockTexture/default.frag");
	Shader ShaderBlockSelected("shaders/BlockSelected/default.vert", "shaders/BlockSelected/default.frag");

	//Camera cam(window, WIN_WIDTH, WIN_HEIGHT);
	Player player(window, WIN_WIDTH, WIN_HEIGHT);

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	const auto world = std::make_unique<WorldGen::World>();

	bool hasToRegen = false;

	sm.texUnit(ShaderBlockTextures, "textureArray");

	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {
		// Fps and frameTime
		float currentTime = glfwGetTime();
		float delta = currentTime - lastTime;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Limpa o buffer de cores com uma cor de fundo (preto)
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player.getCamera().update(window, delta);

		if (hasToRegen) {
			//vao.UpdateBuffers(vertices, indices);
			hasToRegen = false;
		}
#ifdef TIME_GEN_CHUNKS
		world->checkGenFinnished();
#endif
		world->Update();
		player.Update();

		ShaderBlockSelected.Activate();
		player.getCamera().VAOBind(ShaderBlockSelected.ID);
		player.Draw();
		ShaderBlockTextures.Activate();
		player.getCamera().VAOBind(ShaderBlockTextures.ID);
		sm.useTextures();

		world->Draw();

		Sprites::SpriteManager::unuseTextures();
		VAO::Unbind();

		// Imgui
		ImguiTelemetry(delta, player, indices.size() / 3);
		// Not being used atm
		//ImguiWorldGen(vertices, indices, player.getCamera(), hasToRegen);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwPollEvents();
		glfwSwapBuffers(window);

		lastTime = currentTime;
	}


	// Limpa os recursos do ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Limpa os recursos do GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}