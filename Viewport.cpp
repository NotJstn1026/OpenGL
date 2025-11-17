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

	SetVertexData();

	// Make this window's OpenGL context the current one
	glfwMakeContextCurrent(m_window);
	// Set our resize callback function
	glfwSetFramebufferSizeCallback(m_window, HandleFrambufferSize);

	// Try to initialize GLAD (load OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return 69; // Return error on failure

	m_camera = new Camera(m_windowWidth, m_windowHeight, glm::vec3(0.f, 0.f, 2.f));

	m_skybox = new Skybox
	(
		m_camera,
		std::vector<std::string>
		{
			"Textures/Skybox/right.jpg",
			"Textures/Skybox/left.jpg",
			"Textures/Skybox/top.jpg",
			"Textures/Skybox/bottom.jpg",
			"Textures/Skybox/front.jpg",
			"Textures/Skybox/back.jpg"
		}
	);

	m_skybox->Initialize();

	m_lightShader = new Shader("ShaderCode/light.vert", "ShaderCode/light.frag");

	// Create the light object															
	m_lightObject = new LightObject
	(
		m_lightVertices, 
		m_lightIndices, 
		m_camera, 
		m_lightShader, 
		LightType::LT_Point, // Here you can change the art of light
		glm::vec3(1.5f, 0.5f, 0.0f), 
		glm::vec3(0.0f, -1.0f, 0.0f)
	);

	m_lightObject->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	m_lightObject->SetAttenuation(3.0f, 0.7f);
	m_lightObject->Initialize();


	m_pyramid = new BaseObject(m_pyramidVertices, m_pyramidIndices, m_camera, "ShaderCode/default.vert", "ShaderCode/default.frag", "brick.png", m_lightObject);
	m_plank = new BaseObject(m_floorVertices, m_floorIndices, m_camera, "ShaderCode/default.vert", "ShaderCode/default.frag", "planks.png", "planksSpec.png", m_lightObject);


	// Before drawing scene objects each frame:
	m_lightObject->UploadToLightingShader(*m_pyramid->GetShaderProgramm());
	m_lightObject->UploadToLightingShader(*m_plank->GetShaderProgramm());

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

	m_skybox->Draw();

	m_pyramid->Draw();
	m_plank->Draw();
	m_lightShader->Activate();


	m_camera->Matrix(*m_lightShader, "cameraMatrix");
	m_lightObject->Draw();


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
	m_skybox->Finalize();

	delete m_pyramid;
	delete m_plank;
	delete m_skybox;
	m_pyramid = nullptr;
	m_plank = nullptr;
	m_skybox = nullptr;

	delete m_pyramidVertices;
	delete m_pyramidIndices;
	delete m_floorVertices;
	delete m_floorIndices;
	delete m_lightVertices;
	delete m_lightIndices;
	delete m_skyboxVertices;
	delete m_skyboxIndices;

	m_pyramidVertices = nullptr;
	m_pyramidIndices = nullptr;
	m_floorVertices = nullptr;
	m_floorIndices = nullptr;
	m_lightVertices = nullptr;
	m_lightIndices = nullptr;
	m_skyboxVertices = nullptr;
	m_skyboxIndices = nullptr;

	glfwDestroyWindow(m_window);
	glfwTerminate();
	return 0;
}

void Viewport::SetVertexData()
{
	m_pyramidVertices = new std::vector<Vertex>
	{
		// POSITION                      // COLOR                       // TexCoord            // NORMAL
		{ glm::vec3{-0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, -1.0f, 0.0f} },
		{ glm::vec3{-0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 5.0f}, glm::vec3{0.0f, -1.0f, 0.0f} },
		{ glm::vec3{ 0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 5.0f}, glm::vec3{0.0f, -1.0f, 0.0f} },
		{ glm::vec3{ 0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 0.0f}, glm::vec3{0.0f, -1.0f, 0.0f} },

		// Left Side
		{ glm::vec3{-0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 0.0f}, glm::vec3{-0.8f, 0.5f,  0.0f} },
		{ glm::vec3{-0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 0.0f}, glm::vec3{-0.8f, 0.5f,  0.0f} },
		{ glm::vec3{ 0.0f, 0.8f,  0.0f}, glm::vec3{0.92f, 0.86f, 0.76f}, glm::vec2{2.5f, 5.0f}, glm::vec3{-0.8f, 0.5f,  0.0f} },

		// Non-facing side
		{ glm::vec3{-0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 0.0f}, glm::vec3{ 0.0f, 0.5f, -0.8f} },
		{ glm::vec3{ 0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 0.0f}, glm::vec3{ 0.0f, 0.5f, -0.8f} },
		{ glm::vec3{ 0.0f, 0.8f,  0.0f}, glm::vec3{0.92f, 0.86f, 0.76f}, glm::vec2{2.5f, 5.0f}, glm::vec3{ 0.0f, 0.5f, -0.8f} },

		// Right side
		{ glm::vec3{ 0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 0.0f}, glm::vec3{ 0.8f, 0.5f,  0.0f} },
		{ glm::vec3{ 0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 0.0f}, glm::vec3{ 0.8f, 0.5f,  0.0f} },
		{ glm::vec3{ 0.0f, 0.8f,  0.0f}, glm::vec3{0.92f, 0.86f, 0.76f}, glm::vec2{2.5f, 5.0f}, glm::vec3{ 0.8f, 0.5f,  0.0f} },

		// Facing side
		{ glm::vec3{ 0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 0.0f}, glm::vec3{ 0.0f, 0.5f,  0.8f} },
		{ glm::vec3{-0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 0.0f}, glm::vec3{ 0.0f, 0.5f,  0.8f} },
		{ glm::vec3{ 0.0f, 0.8f,  0.0f}, glm::vec3{0.92f, 0.86f, 0.76f}, glm::vec2{2.5f, 5.0f}, glm::vec3{ 0.0f, 0.5f,  0.8f} }
	};

	m_pyramidIndices = new std::vector<GLint>
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
	};

	m_floorVertices = new std::vector<Vertex>
	{
		{ glm::vec3{ 0.5f, 0.0f,  1.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f} },
		{ glm::vec3{ 0.5f, 0.0f, -1.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 1.0f}, glm::vec3{0.0f, 1.0f, 0.0f} },
		{ glm::vec3{ 2.5f, 0.0f, -1.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{1.0f, 1.0f}, glm::vec3{0.0f, 1.0f, 0.0f} },
		{ glm::vec3{ 2.5f, 0.0f,  1.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{1.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f} }
	};

	m_floorIndices = new std::vector<GLint>
	{
		0, 1, 2,
		0, 2, 3
	};

	m_lightVertices = new std::vector<Vertex>
	{
		{ glm::vec3{ -0.1f, -0.1f,  0.1f,}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{-0.1f, -0.1f, -0.1f,}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{ 0.1f, -0.1f, -0.1f,}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{ 0.1f, -0.1f,  0.1f,}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{-0.1f,  0.1f,  0.1f,}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{-0.1f,  0.1f, -0.1f,}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{ 0.1f,  0.1f, -0.1f,}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{ 0.1f,  0.1f,  0.1f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} }
	};

	m_lightIndices = new std::vector<GLint>
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	m_skyboxVertices = new std::vector<Vertex>
	{
		// POSITION
		{ glm::vec3{-1.0f, -1.0f,  1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} },
		{ glm::vec3{ 1.0f, -1.0f,  1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} },
		{ glm::vec3{ 1.0f, -1.0f, -1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} },
		{ glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} },
		{ glm::vec3{-1.0f,  1.0f,  1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} },
		{ glm::vec3{ 1.0f,  1.0f,  1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} },
		{ glm::vec3{ 1.0f,  1.0f, -1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} },
		{ glm::vec3{-1.0f,  1.0f, -1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} } 
	};

	m_skyboxIndices = new std::vector<GLint>
	{
		// Right
		1, 2, 6,
		6, 5, 1,
		// Left
		0, 4, 7,
		7, 3, 0,
		// Top
		4, 5, 6,
		6, 7, 4,
		// Bottom
		0, 3, 2,
		2, 1, 0,
		// Back
		0, 1, 5,
		5, 4, 0,
		// Front
		3, 7, 6,
		6, 2, 3
	};
}
