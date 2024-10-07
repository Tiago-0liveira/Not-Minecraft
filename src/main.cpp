#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Graphics/Shader.hpp>

#include <Camera.hpp>
#include <Graphics/EBO.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/VAO.hpp>
#include <Graphics/VBO.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <array>

float setOneDecimal(const float f)
{
	return std::floor(f * 10) / 10;
}

void addBlockVerticesAndIndices(std::vector<GLfloat> &Outvertices, std::vector<GLuint> &Outindices, const glm::vec3 &pos)
{
	std::array<GLfloat, 6 * 6 * 4> vertices = {
		pos.x + -1.0f, pos.y + -1.0f, pos.z + -1.0f,   1.0f, 0.0f, 0.0f,  // 0: Left-bottom-back
		pos.x +  1.0f, pos.y + -1.0f, pos.z + -1.0f,   0.0f, 0.0f, 0.0f,  // 1: Right-bottom-back
		pos.x +  1.0f, pos.y +  1.0f, pos.z + -1.0f,   0.0f, 1.0f, 0.0f,  // 2: Right-top-back
		pos.x + -1.0f, pos.y +  1.0f, pos.z + -1.0f,   1.0f, 1.0f, 0.0f,  // 3: Left-top-back
		pos.x + -1.0f, pos.y + -1.0f, pos.z +  1.0f,   0.0f, 0.0f, 0.0f,  // 4: Left-bottom-front
		pos.x +  1.0f, pos.y + -1.0f, pos.z +  1.0f,   1.0f, 0.0f, 0.0f,  // 5: Right-bottom-front
		pos.x +  1.0f, pos.y +  1.0f, pos.z +  1.0f,   1.0f, 1.0f, 0.0f,  // 6: Right-top-front
		pos.x + -1.0f, pos.y +  1.0f, pos.z +  1.0f,   0.0f, 1.0f, 0.0f,  // 7: Left-top-front
		pos.x + -1.0f, pos.y + -1.0f, pos.z +  1.0f,   1.0f, 0.0f, 0.0f,  // 8: Left-bottom-front
		pos.x + -1.0f, pos.y + -1.0f, pos.z + -1.0f,   0.0f, 0.0f, 0.0f,  // 9: Left-bottom-back
		pos.x + -1.0f, pos.y +  1.0f, pos.z + -1.0f,   0.0f, 1.0f, 0.0f,  // 10: Left-top-back
		pos.x + -1.0f, pos.y +  1.0f, pos.z +  1.0f,   1.0f, 1.0f, 0.0f,  // 11: Left-top-front
		pos.x +  1.0f, pos.y + -1.0f, pos.z +  1.0f,   0.0f, 0.0f, 0.0f,  // 12: Right-bottom-front
		pos.x +  1.0f, pos.y + -1.0f, pos.z + -1.0f,   1.0f, 0.0f, 0.0f,  // 13: Right-bottom-back
		pos.x +  1.0f, pos.y +  1.0f, pos.z + -1.0f,   1.0f, 1.0f, 0.0f,  // 14: Right-top-back
		pos.x +  1.0f, pos.y +  1.0f, pos.z +  1.0f,   0.0f, 1.0f, 0.0f,  // 15: Right-top-front
		pos.x + -1.0f, pos.y + -1.0f, pos.z +  1.0f,   0.0f, 1.0f, 0.0f,  // 16: Left-bottom-front
		pos.x +  1.0f, pos.y + -1.0f, pos.z +  1.0f,   1.0f, 1.0f, 0.0f,  // 17: Right-bottom-front
		pos.x +  1.0f, pos.y + -1.0f, pos.z + -1.0f,   1.0f, 0.0f, 0.0f,  // 18: Right-bottom-back
		pos.x + -1.0f, pos.y + -1.0f, pos.z + -1.0f,   0.0f, 0.0f, 0.0f,  // 19: Left-bottom-back
		pos.x + -1.0f, pos.y +  1.0f, pos.z +  1.0f,   0.0f, 0.0f, 0.0f,  // 20: Left-top-front
		pos.x +  1.0f, pos.y +  1.0f, pos.z +  1.0f,   1.0f, 0.0f, 0.0f,  // 21: Right-top-front
		pos.x +  1.0f, pos.y +  1.0f, pos.z + -1.0f,   1.0f, 1.0f, 0.0f,  // 22: Right-top-back
		pos.x + -1.0f, pos.y +  1.0f, pos.z + -1.0f,   0.0f, 1.0f, 0.0f   // 23: Left-top-back
	};

	const GLuint offset = Outindices.size();
	//std::cout << "Offset: " << offset << std::endl;
	//std::cout << "Block position: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
	std::array<GLuint, 6 * 6> indices = {
		// Front face (CCW)
		4 + offset, 5 + offset, 6 + offset, 4 + offset, 6 + offset, 7 + offset,
		// Right face (CCW)
		12 + offset, 13 + offset, 14 + offset, 12 + offset, 14 + offset, 15 + offset,
		// Back face (CW)
		0 + offset, 3 + offset, 2 + offset, 0 + offset, 2 + offset, 1 + offset,
		// Left face (CW)
		8 + offset, 11 + offset, 10 + offset, 8 + offset, 10 + offset, 9 + offset,
		// Bottom face (CW)
		16 + offset, 19 + offset, 18 + offset, 16 + offset, 18 + offset, 17 + offset,
		// Top face (CCW)
		20 + offset, 21 + offset, 22 + offset, 20 + offset, 22 + offset, 23 + offset,
	};


	Outvertices.insert(Outvertices.end(), vertices.begin(), vertices.end());
	Outindices.insert(Outindices.end(), indices.begin(), indices.end());
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
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_FRONT);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");

	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << version << std::endl;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	/*auto blockpos = glm::vec3(1.0f, 1.0f, 1.0f);
	addBlockVerticesAndIndices(vertices, indices, blockpos);
	addBlockVerticesAndIndices(vertices, indices, blockpos + glm::vec3(2.0f, 0.0f, 0.0f));
	addBlockVerticesAndIndices(vertices, indices, blockpos + glm::vec3(4.0f, 0.0f, 0.0f));*/

	int s = 9;
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < s; j++)
		{
			for (int w = 0; w < s; w++)
			{
				auto blockpos = glm::vec3(i * 2.0f, w * 2.0f, j * 2.0f);
				addBlockVerticesAndIndices(vertices, indices, blockpos);

			}
		}
	}

	auto blockpos = glm::vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 5; i++)
	{
		addBlockVerticesAndIndices(vertices, indices, blockpos);
		blockpos += glm::vec3(-3.0f, 0.0f, 0.0f);
	}

	/*int i = 0;
	for (GLfloat vertex : vertices)
	{
		if (i % 6 == 0) {
			std::cout << std::endl;
		}
		if (i == 6 * 6 * 4)
		{
			std::cout << "Cube Vertices end" << std::endl;
			i = 0;
		}
		std::cout << vertex << ", ";
		i++;
	}

	std::cout << std::endl << "Indices" << std::endl;
	i = 0;
	for (GLuint index : indices)
	{
		if (i % 6 == 0) {
			std::cout << std::endl;
		}
		if (i == 36)
		{
			std::cout << "Cube Indices end" << std::endl;
			i = 0;
		}
		std::cout << index << ", ";
		i++;
	}*/

	Shader shader("shaders/BlockTexture/default.vert", "shaders/BlockTexture/default.frag");

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices.data(), vertices.size() * sizeof(GLfloat));
	EBO EBO1(indices.data(), indices.size() * sizeof(GLuint));
	GLsizeiptr stride = 6 * sizeof(GLfloat);
	VAO1.LinkVBO(VBO1, 0, 3, GL_FLOAT, stride, nullptr);
	VAO1.LinkVBO(VBO1, 1, 2, GL_FLOAT, stride, reinterpret_cast<void *>(3 * sizeof(GLfloat)));
	VAO1.LinkVBO(VBO1, 2, 1, GL_FLOAT, stride, reinterpret_cast<void *>(5 * sizeof(GLfloat)));
	VAO1.Unbind();
	EBO1.Unbind();

	//Texture Dirt("sprites/direction_test.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
	Texture Dirt("sprites/blocks/dirt-side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
	Dirt.texUnit(shader, "tex", 0);

	Camera cam(window, WIN_WIDTH, WIN_HEIGHT);

	float fps = 0;
	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {

		// Fps and frameTime
		float currentTime = glfwGetTime();
		float delta = currentTime - lastTime;
		fps = 1.0f / delta;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Limpa o buffer de cores com uma cor de fundo (preto)
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.update(window, delta);

		shader.Activate();
		cam.VAOBind(shader.ID);

		Dirt.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);


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
	shader.Delete();

	// Limpa os recursos do GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}