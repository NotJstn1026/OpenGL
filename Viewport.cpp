#include "Viewport.h"


void HandleFrambufferSize(GLFWwindow* a_window, int a_width, int a_height)
{
	int xOffset = 0;
	int yOffset = 0;
	glViewport(xOffset, yOffset, a_width, a_height);
}

const int Viewport::Initialize(void)
{
	if (!glfwInit())return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_versionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!m_window)m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_title.c_str(), nullptr, nullptr);

	if (!m_window)
	{
		glfwTerminate();
		return 404;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, HandleFrambufferSize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return 69;


	Vertex vertices[6] =
	{
		glm::vec3{-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f},
		glm::vec3{0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f},
		glm::vec3{0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f},
		glm::vec3{-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f},
		glm::vec3{0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f},
		glm::vec3{0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f},
	};

	GLint indices[9] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Upper triangle
		5, 4, 1 // Lower right triangle
	};

	//Generate shader project
	m_shaderProgramm = new Shader("default.vert", "default.frag");

	// Generates vertex array object and binds it
	m_vao = new VAO();
	m_vao->Bind();

	// Generate vertex buffer object
	m_vbo = new VBO(vertices, sizeof(vertices));
	m_vbo->Bind();

	m_ebo = new EBO(indices, sizeof(indices));

	m_vao->LinkVBO(*m_vbo, 0);

	m_vao->Unbind();
	m_vbo->Unbind();
	m_ebo->Unbind();

	return 0;
}

const int Viewport::Update(void)
{
	while (!glfwWindowShouldClose(m_window))
	{
		Draw();
	}
	return 0;
}

const int Viewport::Draw(void)
{
	glClearColor(.25f, .4f, .69f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_shaderProgramm->Activate();
	m_vao->Bind();
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(m_window);
	glfwPollEvents();

	return 0;
}

const int Viewport::Finalize(void)
{
	m_vao->Delete();
	m_vbo->Delete();
	m_ebo->Delete();
	m_shaderProgramm->Delete();
	glfwDestroyWindow(m_window);
	glfwTerminate();
	return 0;
}