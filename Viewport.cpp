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

	// Create a new shader program object
	m_shaderProgramm = new Shader("default.vert", "default.frag");




	// Create a new Vertex Array Object (VAO)
	m_vao = new VAO();
	// Bind the VAO to make it active
	m_vao->Bind();

	// Create a new Vertex Buffer Object (VBO) with our vertex data
	m_vbo = new VBO(m_vertices.data(), sizeof(m_vertices) * m_vertices.size());
	// Bind the VBO to the array buffer target
	m_vbo->Bind();

	// Create a new Element Buffer Object (EBO) with our index data
	m_ebo = new EBO(m_indices.data(), sizeof(m_indices) * m_vertices.size());

	// Configure vertex attribute layout 0 (position)
	m_vao->LinkAttribute(*m_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	// Configure vertex attribute layout 1 (color)
	m_vao->LinkAttribute(*m_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	// Configure vertex attribute layout 2 (texture coordinates)
	m_vao->LinkAttribute(*m_vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, UV));

	// Unbind the VAO (good practice)
	m_vao->Unbind();
	// Unbind the VBO (good practice)
	m_vbo->Unbind();
	// Unbind the EBO (good practice)
	m_ebo->Unbind();

	// Get the location of the "scale" uniform in the shader
	m_uniScaleID = glGetUniformLocation(m_shaderProgramm->GetID(), "scale");

	// Define the path to the texture file
	std::string texturePath = "Textures\\brick.png";

	// Create a new texture object from the file
	m_texture = new Texture((texturePath).c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	// Tell the shader's "tex0" uniform to use texture unit 0
	m_texture->texUnit(*m_shaderProgramm, "tex0", 0);

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

	// Activate our shader program
	m_shaderProgramm->Activate();

	// Create an identity matrix for the model
	glm::mat4 model = glm::mat4(1.f);
	// Create an identity matrix for the view
	glm::mat4 view = glm::mat4(1.f);
	// Create an identity matrix for the projection
	glm::mat4 projection = glm::mat4(1.f);

	// Rotate the model matrix over time around the Y-axis
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.f), glm::vec3(0.f, 1.f, 0.f));

	// Move the view matrix back and down
	view = glm::translate(view, glm::vec3(0.f, -0.5f, -2.f));
	// Create a perspective projection matrix
	projection = glm::perspective(glm::radians(45.f), (float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.f);

	// Get the location of the "model" uniform
	int modelLoc = glGetUniformLocation(m_shaderProgramm->GetID(), "model");
	// Send the model matrix data to the shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	// Get the location of the "view" uniform
	int viewLoc = glGetUniformLocation(m_shaderProgramm->GetID(), "view");
	// Send the view matrix data to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	// Get the location of the "projection" uniform
	int projectionLoc = glGetUniformLocation(m_shaderProgramm->GetID(), "projection");
	// Send the projection matrix data to the shader
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


	// Set the "scale" uniform value
	glUniform1f(m_uniScaleID, 1.f);
	// Bind our texture to be used
	m_texture->Bind();

	// Bind our VAO (which contains all buffer settings)
	m_vao->Bind();
	// Draw the object using the EBO's indices
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

	// Swap the front and back buffers (show the rendered frame)
	glfwSwapBuffers(m_window);
	// Check for and process any pending events (like keyboard input)
	glfwPollEvents();

	return 0;
}

const int Viewport::Finalize(void)
{
	m_vao->Delete();
	m_vbo->Delete();
	m_ebo->Delete();
	m_texture->Delete();
	m_shaderProgramm->Delete();
	glfwDestroyWindow(m_window);
	glfwTerminate();
	return 0;
}