#include "Viewport.h"


void HandleFrambufferSize(GLFWwindow* a_window, int a_width, int a_height)
{
	// Set the starting X offset for the viewport
	int xOffset = 0;
	// Set the starting Y offset for the viewport
	int yOffset = 0;
	// Tell OpenGL the new size of the rendering area
	glViewport(xOffset, yOffset, a_width, a_height);
}

const int Viewport::Initialize(void)
{
	// Try to initialize the GLFW library
	if (!glfwInit())return -1; // Return -1 on failure

	// Tell GLFW we want OpenGL version 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_versionMajor);
	// Tell GLFW we want OpenGL version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_versionMinor);
	// Tell GLFW to use the modern "Core" profile (no old functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window if it doesn't exist
	if (!m_window)m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_title.c_str(), nullptr, nullptr);

	// Check if window creation failed
	if (!m_window)
	{
		// Clean up GLFW
		glfwTerminate();
		// Return an error code
		return 404;
	}

	// Make this window's OpenGL context the current one
	glfwMakeContextCurrent(m_window);
	// Set our resize callback function
	glfwSetFramebufferSizeCallback(m_window, HandleFrambufferSize);

	// Try to initialize GLAD (load OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return 69; // Return error on failure


	m_lightShader = new Shader("ShaderCode/light.vert", "ShaderCode/light.frag");

	m_lightVAO = new VAO();
	m_lightVAO->Bind();
	m_lightVBO = new VBO(lightVertices->data(), lightVertices->size() * sizeof(Vertex));
	m_lightEBO = new EBO(lightIndices->data(), lightIndices->size() * sizeof(GLint));

	m_lightVAO->LinkAttribute(*m_lightVBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	m_lightVAO->LinkAttribute(*m_lightVBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	m_lightVAO->LinkAttribute(*m_lightVBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, UV));

	m_lightVAO->Unbind();
	m_lightVBO->Unbind();
	m_lightEBO->Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	m_lightShader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(m_lightShader->GetID(), "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(m_lightShader->GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	m_camera = new Camera(m_windowWidth, m_windowHeight, glm::vec3(0.f, 0.f, 2.f));

	m_pyramid = new BaseObject(m_pyramidVertices, m_pyramidIndices, m_camera, "ShaderCode/default.vert", "ShaderCode/default.frag", "brick.png");
	m_plank = new BaseObject(m_floorVertices, m_floorIndices, m_camera, "ShaderCode/default.vert", "ShaderCode/default.frag", "planks.png", "planksSpec.png");

	// Enable depth testing for 3D rendering
	glEnable(GL_DEPTH_TEST);

	return 0;
}

const int Viewport::Update(void)
{
	// Loop as long as the window shouldn't close
	while (!glfwWindowShouldClose(m_window))
	{
		Draw();
	}
	return 0;
}

const int Viewport::Draw(void)
{
	// Set the background color
	glClearColor(.25f, .4f, .69f, 1.f);
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_camera->Inputs(m_window);

	m_camera->UpdateMatrix();

	m_pyramid->Draw();
	m_plank->Draw();
	m_lightShader->Activate();


	m_camera->Matrix(*m_lightShader, "cameraMatrix");
	m_lightVAO->Bind();
	m_camera->UpdateMatrix();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(lightIndices->size()), GL_UNSIGNED_INT, 0);

	// Swap the front and back buffers (show the rendered frame)
	glfwSwapBuffers(m_window);
	// Check for and process any pending events (like keyboard input)
	glfwPollEvents();

	return 0;
}

const int Viewport::Finalize(void)
{
	m_pyramid->Finalize();
	m_plank->Finalize();

	delete m_pyramid;
	delete m_plank;
	m_pyramid = nullptr;
	m_plank = nullptr;

	glfwDestroyWindow(m_window);
	glfwTerminate();
	return 0;
}