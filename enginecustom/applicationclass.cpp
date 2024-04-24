#include "applicationclass.h"

ApplicationClass::ApplicationClass()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Bitmap = 0;
	m_Sprite = 0;
	m_Timer = 0;
	m_MouseStrings = 0;
	m_FontShader = 0;
	m_Font = 0;
	m_Fps = 0;
	m_FpsString = 0;
	m_ShaderManager = 0;
	m_RenderCountString = 0;
	m_ModelList = 0;
	m_Position = 0;
	m_Frustum = 0;
	m_DisplayPlane = 0;
	m_BathModel = 0;
	m_WaterModel = 0;
	m_Light = 0;
	m_RefractionTexture = 0;
	m_ReflectionTexture = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{

	logger.Log("Initializing application class", __FILE__, __LINE__);

	try 
	{
		char mouseString1[32], mouseString2[32], mouseString3[32];
		char modelFilename[128], textureFilename1[128], textureFilename2[128], textureFilename3[128], textureFilename4[128], textureFilename5[128], textureFilename6[128], renderString[32];
		char bitmapFilename[128];
		char spriteFilename[128];
		char fpsString[32];
		bool result;

		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;

		// Create the Direct3D object.
		m_Direct3D = new D3DClass;
		if (!m_Direct3D)
		{
			logger.Log("Could not create the Direct3D object", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
		if (!result)
		{
			logger.Log("Could not initialize Direct3D", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		// Create the camera object.
		m_Camera = new CameraClass;
		if (!m_Camera)
		{
			logger.Log("Could not create the camera object", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		// Set the initial position of the camera.
		m_Camera->SetPosition(0.0f, 0.0f, -12.0f);
		m_Camera->SetRotation(0.0f, 0.0f, 0.0f);
		m_Camera->Render();
		m_Camera->GetViewMatrix(m_baseViewMatrix);

		// Create and initialize the font shader object.
		m_FontShader = new FontShaderClass;

		result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
		if (!result)
		{
			logger.Log("Could not initialize the font shader object", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		// Create and initialize the font object.
		m_Font = new FontClass;

		result = m_Font->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), 0);
		if (!result)
		{
			logger.Log("Could not initialize the font object", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		// Create and initialize the render to texture object.
		m_RenderTexture = new RenderTextureClass;

		result = m_RenderTexture->Initialize(m_Direct3D->GetDevice(), 256, 256, SCREEN_DEPTH, SCREEN_NEAR, 1);
		if (!result)
		{
			logger.Log("Could not initialize the render texture object", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		// Create and initialize the display plane object.
		m_DisplayPlane = new DisplayPlaneClass;

		result = m_DisplayPlane->Initialize(m_Direct3D->GetDevice(), 1.0f, 1.0f);
		if (!result)
		{	
			logger.Log("Could not initialize the display plane object", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}


		// Set the sprite info file we will be using.
		strcpy_s(spriteFilename, "sprite_data_01.txt");

		// Create and initialize the sprite object.
		m_Sprite = new SpriteClass;

		result = m_Sprite->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, spriteFilename, 50, 50);
		if (!result)
		{
			logger.Log("Could not initialize the sprite object", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		// Set the initial mouse strings.
		strcpy_s(mouseString1, "Mouse X: 0");
		strcpy_s(mouseString2, "Mouse Y: 0");
		strcpy_s(mouseString3, "Mouse Button: No");

		// Create and initialize the text objects for the mouse strings.
		m_MouseStrings = new TextClass[3];

		for (int i = 0; i < 3; i++)
		{
			int y = 10 + (i * 25);
			result = m_MouseStrings[i].Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, mouseString1, 10, y, 1.0f, 1.0f, 1.0f);
			if (!result)
			{
				logger.Log("Could not initialize the mouse strings", __FILE__, __LINE__, Logger::LogLevel::Error);
				return false;
			}
		}

		// Set the file name of the bitmap file.
		strcpy_s(bitmapFilename, "stone01.tga");

		// Create and initialize the bitmap object.
		m_Bitmap = new BitmapClass;

		result = m_Bitmap->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, bitmapFilename, 50, 50);
		if (!result)
		{
			logger.Log("Could not initialize the bitmap object", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		// Set the file name of the model.
		strcpy_s(modelFilename, "cube.txt");

		// Set the file name of the textures.
		strcpy_s(textureFilename1, "stone01.tga");
		strcpy_s(textureFilename2, "normal01.tga");
		strcpy_s(textureFilename3, "spec02.tga");
		strcpy_s(textureFilename4, "alpha01.tga");
		strcpy_s(textureFilename5, "light01.tga");
		strcpy_s(textureFilename6, "moss01.tga");

		// Create and initialize the model object.
		m_Model = new ModelClass;

		result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename1, textureFilename2, textureFilename3, textureFilename4,
			textureFilename5, textureFilename6);
		if (!result)
		{
			logger.Log("Could not initialize the model object", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		// Create and initialize the light object.
		m_Light = new LightClass;

		m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetDirection(0.0f, 0.0f, -1.0f);
		m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetSpecularPower(16.0f);

		// Set the number of lights we will use.
		m_numLights = 4;

		// Create and initialize the light objects array.
		m_Lights.resize(m_numLights);

		m_Lights[0] = new LightClass;
		m_Lights[0]->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);  // White
		m_Lights[0]->SetDirection(0.0f, 0.0f, -1.0f);
		m_Lights[0]->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_Lights[0]->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Lights[0]->SetSpecularPower(16.0f);
		m_Lights[0]->SetPosition(10.0f, 7.0f, -5.0f);

		// Manually set the color and position of each light.
		m_Lights[1] = new LightClass;
		m_Lights[1]->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);  // Red
		m_Lights[1]->SetDirection(0.0f, 0.0f, 1.0f);
		m_Lights[1]->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_Lights[1]->SetSpecularColor(1.0f, 0.0f, 0.0f, 1.0f);
		m_Lights[1]->SetSpecularPower(16.0f);
		m_Lights[1]->SetPosition(10.0f, 7.0f, -5.0f);

		m_Lights[2] = new LightClass;
		m_Lights[2]->SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);  // Green
		m_Lights[2]->SetDirection(0.0f, 0.0f, 1.0f);
		m_Lights[2]->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_Lights[2]->SetSpecularColor(0.0f, 1.0f, 0.0f, 1.0f);
		m_Lights[2]->SetSpecularPower(16.0f);
		m_Lights[2]->SetPosition(10.0f, 7.0f, -5.0f);

		m_Lights[3] = new LightClass;
		m_Lights[3]->SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);  // Blue
		m_Lights[3]->SetDirection(0.0f, 0.0f, 1.0f);
		m_Lights[3]->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_Lights[3]->SetSpecularColor(0.0f, 0.0f, 1.0f, 1.0f);
		m_Lights[3]->SetSpecularPower(16.0f);
		m_Lights[3]->SetPosition(10.0f, 7.0f, -5.0f);


		// Create and initialize the normal map shader object.
		m_ShaderManager = new ShaderManagerClass;

		result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd);
		if (!result)
		{
			logger.Log("Could not initialize the shader manager object", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		// Set the initial render count string.
		strcpy_s(renderString, "Render Count: 0");

		// Create and initialize the text object for the render count string.
		m_RenderCountString = new TextClass;

		result = m_RenderCountString->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, renderString, 10, 10, 1.0f, 1.0f, 1.0f);
		if (!result)
		{
			logger.Log("Could not initialize the render count string", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		// Create and initialize the model list object.
		m_ModelList = new ModelListClass;
		m_ModelList->Initialize(25);

		// Set the file names of the wall model.
		strcpy_s(modelFilename, "wall.txt");
		strcpy_s(textureFilename1, "wall01.tga");

		// Create and initialize the wall model object.
		m_WallModel = new ModelClass;

		result = m_WallModel->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename1, textureFilename2, textureFilename3, textureFilename4,
			textureFilename5, textureFilename6);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the wall model object.", L"Error", MB_OK);
			return false;
		}

		// Set the file names of the bath model.
		strcpy_s(modelFilename, "bath.txt");
		strcpy_s(textureFilename1, "marble01.tga");

		// Create and initialize the bath model object.
		m_BathModel = new ModelClass;

		result = m_BathModel->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename1, textureFilename2, textureFilename3, textureFilename4,
			textureFilename5, textureFilename6);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the bath model object.", L"Error", MB_OK);
			return false;
		}

		// Set the file names of the water model.
		strcpy_s(modelFilename, "water.txt");
		strcpy_s(textureFilename1, "water01.tga");

		// Create and initialize the water model object.
		m_WaterModel = new ModelClass;

		result = m_WaterModel->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename1, textureFilename2, textureFilename3, textureFilename4,
			textureFilename5, textureFilename6);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the water model object.", L"Error", MB_OK);
			return false;
		}

		// Create and initialize the refraction render to texture object.
		m_RefractionTexture = new RenderTextureClass;

		result = m_RefractionTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR, 1);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the refraction render texture object.", L"Error", MB_OK);
			return false;
		}

		// Create and initialize the reflection render to texture object.
		m_ReflectionTexture = new RenderTextureClass;

		result = m_ReflectionTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR, 1);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the reflection render texture object.", L"Error", MB_OK);
			return false;
		}

		// Set the height of the water.
		m_waterHeight = -9.25f;

		// Initialize the position of the water.
		m_waterTranslation = 100.0f;

		// Create and initialize the timer object.
		m_Timer = new TimerClass;

		result = m_Timer->Initialize();
		if (!result)
		{
			logger.Log("Could not initialize the timer object", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}

		// Create the position class object.
		m_Position = new PositionClass;

		// Create the frustum class object.
		m_Frustum = new FrustumClass;

		// Create and initialize the fps object.
		m_Fps = new FpsClass();

		m_Fps->Initialize();

		// Set the initial fps and fps string.
		m_previousFps = -1;
		strcpy_s(fpsString, "Fps: 0");

		// Create and initialize the text object for the fps string.
		m_FpsString = new TextClass;

		result = m_FpsString->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, fpsString, 10, 10, 0.0f, 1.0f, 0.0f);
		if (!result)
		{
			logger.Log("Could not initialize the fps string", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}
	}
	catch (const std::exception& e)
	{
		logger.Log(std::string("Exception caught during initialization: ") + e.what(), __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}
	logger.Log("Application class initialized", __FILE__, __LINE__);

	return true;
}


void ApplicationClass::Shutdown()
{
	// Release the shader manager object.
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the reflection render texture object.
	if (m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	// Release the refraction render texture object.
	if (m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}

	// Release the water model object.
	if (m_WaterModel)
	{
		m_WaterModel->Shutdown();
		delete m_WaterModel;
		m_WaterModel = 0;
	}

	// Release the bath model object.
	if (m_BathModel)
	{
		m_BathModel->Shutdown();
		delete m_BathModel;
		m_BathModel = 0;
	}

	// Release the wall model object.
	if (m_WallModel)
	{
		m_WallModel->Shutdown();
		delete m_WallModel;
		m_WallModel = 0;
	}

	// Release the frustum class object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the display plane object.
	if (m_DisplayPlane)
	{
		m_DisplayPlane->Shutdown();
		delete m_DisplayPlane;
		m_DisplayPlane = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the model list object.
	if (m_ModelList)
	{
		m_ModelList->Shutdown();
		delete m_ModelList;
		m_ModelList = 0;
	}

	// Release the text objects for the render count string.
	if (m_RenderCountString)
	{
		m_RenderCountString->Shutdown();
		delete m_RenderCountString;
		m_RenderCountString = 0;
	}

	// Release the text objects for the mouse strings.
	if (m_MouseStrings)
	{
		m_MouseStrings[0].Shutdown();
		m_MouseStrings[1].Shutdown();
		m_MouseStrings[2].Shutdown();

		delete[] m_MouseStrings;
		m_MouseStrings = 0;
	}

	// Release the text object for the fps string.
	if (m_FpsString)
	{
		m_FpsString->Shutdown();
		delete m_FpsString;
		m_FpsString = 0;
	}

	// Release the fps object.
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the font object.
	if (m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}

	// Release the font shader object.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the sprite object.
	if (m_Sprite)
	{
		m_Sprite->Shutdown();
		delete m_Sprite;
		m_Sprite = 0;
	}

	for (auto light : m_Lights)
	{
		if (light)
		{
			delete light;
			light = 0;
		}
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
}


bool ApplicationClass::Frame(InputClass* Input)
{
	int mouseX, mouseY, currentMouseX, currentMouseY;
	bool result, leftMouseDown, rightMouseDown, keyDown, buttonQ, buttonD, buttonZ, buttonS, buttonA, buttonE;
	float rotationY, rotationX, positionX, positionY, positionZ;
	static float textureTranslation = 0.0f;

	float frameTime;

	static int lastMouseX = 0, lastMouseY = 0;

	static float rotation = 360.0f;
	static float x = 0.f;
	static float y = 0.f;
	static float z = -8.f;

	// Update the system stats.
	m_Timer->Frame();

	// Get the current frame time.
	frameTime = m_Timer->GetTime();

	// Check if the user pressed escape and wants to exit the application.
	if (Input->IsEscapePressed())
	{
		return false;
	}

	// Get the location of the mouse from the input object,
	Input->GetMouseLocation(mouseX, mouseY);

	// Check if the mouse has been pressed.
	leftMouseDown = Input->IsLeftMousePressed();
	rightMouseDown = Input->IsRightMousePressed();

	currentMouseX = mouseX;

	int deltaX = currentMouseX - lastMouseX;  // Calculez le d�placement de la souris
	lastMouseX = currentMouseX;  // Mettez � jour la derni�re position de la souris pour la prochaine image

	currentMouseY = mouseY;

	int deltaY = currentMouseY - lastMouseY;  // Calculez le d�placement de la souris
	lastMouseY = currentMouseY;  // Mettez � jour la derni�re position de la souris pour la prochaine image

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(m_Timer->GetTime());

	// Check if the left or right arrow key has been pressed, if so rotate the camera accordingly.
	keyDown = Input->IsLeftArrowPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = Input->IsRightArrowPressed();
	m_Position->TurnRight(keyDown);

	m_Position->TurnMouse(deltaX, deltaY, rightMouseDown);

	// Get the current view point rotation.
	m_Position->GetRotation(rotationY, rotationX);

	// Check if the a(q), d, w(z), s, q(a), e have been pressed, if so move the camera accordingly.
	buttonQ = Input->IsAPressed();
	buttonD = Input->IsDPressed();
	buttonZ = Input->IsWPressed();
	buttonS = Input->IsSPressed();
	buttonA = Input->IsQPressed();
	buttonE = Input->IsEPressed();
	m_Position->MoveCamera(buttonZ, buttonS, buttonQ, buttonD, buttonE, buttonA);
	m_Position->GetPosition(positionX, positionY, positionZ);

	// Set the postion and rotation of the camera.
	m_Camera->SetPosition(positionX, positionY, positionZ);
	m_Camera->SetRotation(rotationX, rotationY, 0.0f);
	m_Camera->Render();

	// Render the graphics scene.
	result = Render(rotation, x, y, z, textureTranslation);
	if (!result)
	{
		logger.Log("Could not render the graphics scene", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Update the frames per second each frame.
	result = UpdateFps();
	if (!result)
	{
		logger.Log("Could not update the frames per second", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Update the rotation variable each frame.
	rotation -= 0.0174532925f * speed;
	if (rotation < 0.0f)
	{
		rotation += 360.0f;
	}

	// Update the position of the water to simulate motion.
	m_waterTranslation += 0.001f;
	if (m_waterTranslation > 1.0f)
	{
		m_waterTranslation -= 1.0f;
	}

	// Render the refraction of the scene to a texture.
	result = RenderRefractionToTexture();
	if (!result)
	{
		return false;
	}

	// Render the reflection of the scene to a texture.
	result = RenderReflectionToTexture();
	if (!result)
	{
		return false;
	}


	//// Update the x position variable each frame.
	//x -= 0.0174532925f * 0.6f;

	//y -= 0.0174532925f * 0.2f;

	//// Update the z position variable each frame.
	//z -= 0.0174532925f * 0.2f;

	// Render the scene to a render texture.
	result = RenderSceneToTexture(rotation);
	if (!result)
	{
		logger.Log("Could not render the scene to the render texture", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Update the mouse strings each frame.
	result = UpdateMouseStrings(mouseX, mouseY, leftMouseDown);
	if (!result)
	{
		logger.Log("Could not update the mouse strings", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Update the sprite object using the frame time.
	m_Sprite->Update(frameTime);

	// Increment the texture translation.
	textureTranslation += 0.01f;
	if (textureTranslation > 1.0f)
	{
		textureTranslation -= 1.0f;
	}

	/////////////////////////////
	// C en commentaire pcl kc //
	/////////////////////////////

	//// Render the graphics scene.
	//result = Render(rotation, x, y, z, textureTranslation);
	//if (!result)
	//{
	//	return false;
	//}

	return true;
}

bool ApplicationClass::RenderRefractionToTexture()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	XMFLOAT4 clipPlane;
	XMFLOAT4 diffuseColor[4], lightPosition[4], getDirection[4], ambientColor[4];
	bool result;

	// Setup a clipping plane based on the height of the water to clip everything above it.
	clipPlane = XMFLOAT4(0.0f, -1.0f, 0.0f, m_waterHeight + 0.1f);

	// Set the render target to be the refraction render to texture and clear it.
	m_RefractionTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());
	m_RefractionTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);


	// Translate to where the wall model will be rendered.
	worldMatrix = XMMatrixTranslation(0.0f, 6.0f, 8.0f);

	// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_WallModel->Render(m_Direct3D->GetDeviceContext());

	// Render the wall model using the light shader.
	result = m_ShaderManager->RenderlightShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0), diffuseColor, lightPosition, ambientColor);
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);


	// Translate to where the bath model will be rendered.
	worldMatrix = XMMatrixTranslation(0.0f, -10.0f, 0.0f);

	// Render the bath model using the refraction shader.
	m_BathModel->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderRefractionShader(m_Direct3D->GetDeviceContext(), m_BathModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		m_BathModel->GetTexture(0), m_Lights[0]->GetDirection(), m_Lights[0]->GetAmbientColor(), m_Lights[0]->GetDiffuseColor(), clipPlane);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.  And reset the viewport back to the original.
	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->ResetViewport();

	return true;
}

bool ApplicationClass::RenderReflectionToTexture()
{
	XMMATRIX worldMatrix, reflectionViewMatrix, projectionMatrix;
	XMFLOAT4 diffuseColor[4], getDirection[4], ambientColor[4];
	bool result;


	// Set the render target to be the reflection render to texture and clear it.
	m_ReflectionTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());
	m_ReflectionTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Use the camera to render the reflection and create a reflection view matrix.
	m_Camera->RenderReflection(m_waterHeight);

	// Get the camera reflection view matrix instead of the normal view matrix.
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the world and projection matrices from the d3d object.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);


	// Reset the render target back to the original back buffer and not the render to texture anymore.  And reset the viewport back to the original.
	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->ResetViewport();

	return true;
}

bool ApplicationClass::RenderSceneToTexture(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	// Set the render target to be the render texture and clear it.
	m_RenderTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());
	m_RenderTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.5f, 1.0f, 1.0f);

	// Set the position of the camera for viewing the cube.
	m_Camera->Render();

	// Get the matrices.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_RenderTexture->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the cube will spin.
	worldMatrix = XMMatrixRotationY(rotation);

	// Render the model using the texture shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(1));
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.  And reset the viewport back to the original.
	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->ResetViewport();

	return true;
}

bool ApplicationClass::Render(float rotation, float x, float y, float z, float textureTranslation)
{
	XMMATRIX worldMatrix, viewMatrix, orthoMatrix, projectionMatrix, rotateMatrix, translateMatrix, scaleMatrix, srMatrix, reflectionMatrix;
	float positionX, positionY, positionZ, radius;
	XMFLOAT4 diffuseColor[4], lightPosition[4], getDirection[4], ambientColor[4];
	int  modelCount, renderCount, i;
	bool result, renderModel;
	float blendAmount;

	// Set the blending amount to 10%.
	blendAmount = 0.1f;

	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();
	

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// Get the light properties.
	for (i = 0; i < m_numLights; i++)
	{
		// Create the diffuse color array from the four light colors.
		diffuseColor[i] = m_Lights[i]->GetDiffuseColor();

		// Create the light position array from the four light positions.
		lightPosition[i] = m_Lights[i]->GetPosition();

		// Create the light position array from the four light positions.
		ambientColor[i] = m_Lights[i]->GetPosition();
	}

	scaleMatrix = XMMatrixScaling(0.5f, 0.5f, 0.5f);  // Build the scaling matrix.
	rotateMatrix = XMMatrixRotationY(rotation);  // Build the rotation matrix.
	translateMatrix = XMMatrixTranslation(x, y, z);  // Build the translation matrix.

	// Multiply the scale, rotation, and translation matrices together to create the final world transformation matrix.
	srMatrix = XMMatrixMultiply(scaleMatrix, rotateMatrix);
	worldMatrix = XMMatrixMultiply(srMatrix, translateMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_ShaderManager->RenderlightShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0), diffuseColor, lightPosition, ambientColor);

	for (auto cube : m_cubes)
	{

		scaleMatrix = cube->GetScaleMatrix();

		if (cube->m_demoSpinning)
			rotateMatrix = XMMatrixRotationY(rotation);
		else
		{
			rotateMatrix = cube->GetRotateMatrix();
		}


		translateMatrix = cube->GetTranslateMatrix();
		srMatrix = XMMatrixMultiply(scaleMatrix, rotateMatrix);
		worldMatrix = XMMatrixMultiply(srMatrix, translateMatrix);

		cube->Render(m_Direct3D->GetDeviceContext());

		result = m_ShaderManager->RenderlightShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0),
			diffuseColor, lightPosition, ambientColor);
		if (!result)
		{
			logger.Log("Could not render the cube model using the light shader", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}
	}

	for (auto object : m_object)
	{
		scaleMatrix = object->GetScaleMatrix();
		if (object->m_demoSpinning)
			rotateMatrix = XMMatrixRotationY(rotation);
		else
		{
			rotateMatrix = object->GetRotateMatrix();
		}
		translateMatrix = object->GetTranslateMatrix();
		srMatrix = XMMatrixMultiply(scaleMatrix, rotateMatrix);
		worldMatrix = XMMatrixMultiply(srMatrix, translateMatrix);

		object->Render(m_Direct3D->GetDeviceContext());

		result = m_ShaderManager->RenderlightShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0),
			diffuseColor, lightPosition, ambientColor);

		if (!result)
		{
			logger.Log("Could not render the object model using the light shader", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}
	}

	// Render terrain
	for (auto chunk : m_terrainChunk)
	{

		scaleMatrix = chunk->GetScaleMatrix();
		rotateMatrix = chunk->GetRotateMatrix();
		translateMatrix = chunk->GetTranslateMatrix();

		srMatrix = XMMatrixMultiply(scaleMatrix, rotateMatrix);
		worldMatrix = XMMatrixMultiply(srMatrix, translateMatrix);

		chunk->Render(m_Direct3D->GetDeviceContext());

		result = m_ShaderManager->RenderlightShader(m_Direct3D->GetDeviceContext(), chunk->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, chunk->GetTexture(5),
			diffuseColor, lightPosition, ambientColor);
			
		if (!result)
		{
			logger.Log("Could not render the terrain model using the light shader", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}
	}

	// Setup matrices - Top display plane.
	worldMatrix = XMMatrixTranslation(0.0f, 1.5f, 0.0f);

	// Render the display plane using the texture shader and the render texture resource.
	m_DisplayPlane->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_DisplayPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_RenderTexture->GetShaderResourceView()); 
	if (!result)
	{
		logger.Log("Could not render the display plane using the texture shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Setup matrices - Bottom left display plane.
	worldMatrix = XMMatrixTranslation(-1.5f, -1.5f, 0.0f);

	// Render the display plane using the texture shader and the render texture resource.
	m_DisplayPlane->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_DisplayPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_RenderTexture->GetShaderResourceView());
	if (!result)
	{
		logger.Log("Could not render the display plane using the texture shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Setup matrices - Bottom right display plane.
	worldMatrix = XMMatrixTranslation(1.5f, -1.5f, 0.0f);

	// Render the display plane using the texture shader and the render texture resource.
	m_DisplayPlane->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_DisplayPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_RenderTexture->GetShaderResourceView());
	if (!result)
	{
		logger.Log("Could not render the display plane using the texture shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Construct the frustum.
	m_Frustum->ConstructFrustum(viewMatrix, projectionMatrix, SCREEN_DEPTH);

	// Get the number of models that will be rendered.
	modelCount = m_ModelList->GetModelCount();

	// Initialize the count of models that have been rendered.
	renderCount = 0;

	// Go through all the models and render them only if they can be seen by the camera view.
	for (i = 0; i < modelCount; i++)
	{
		// Get the position and color of the sphere model at this index.
		m_ModelList->GetData(i, positionX, positionY, positionZ);

		// Set the radius of the sphere to 1.0 since this is already known.
		radius = 1.0f;

		// Check if the sphere model is in the view frustum.
		renderModel = m_Frustum->CheckSphere(positionX, positionY, positionZ, radius);

		// If it can be seen then render it, if not skip this model and check the next sphere.
		if (renderModel)
		{
			// Move the model to the location it should be rendered at.
			worldMatrix = XMMatrixTranslation(positionX, positionY, positionZ);

			// Render the model using the light shader.
			m_Model->Render(m_Direct3D->GetDeviceContext());

			result = m_ShaderManager->RenderlightShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0),
				diffuseColor, lightPosition, ambientColor);
			if (!result)
			{
				logger.Log("Could not render the model using the light shader", __FILE__, __LINE__, Logger::LogLevel::Error);
				return false;
			}

			// Since this model was rendered then increase the count for this frame.
			renderCount++;
		}
	}

	// Update the render count text.
	result = UpdateRenderCountString(renderCount);
	if (!result)
	{
		logger.Log("Could not update the render count string", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Disable the Z buffer and enable alpha blending for 2D rendering.
	m_Direct3D->TurnZBufferOff();
	m_Direct3D->EnableAlphaBlending();

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// Render the render count text string using the font shader.
	m_RenderCountString->Render(m_Direct3D->GetDeviceContext());

	result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_RenderCountString->GetIndexCount(), worldMatrix, m_baseViewMatrix, orthoMatrix,
		m_Font->GetTexture(), m_RenderCountString->GetPixelColor());
	if (!result)
	{
		logger.Log("Could not render the render count text string using the font shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Render the fps text string using the font shader.
	m_FpsString->Render(m_Direct3D->GetDeviceContext());

	result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_FpsString->GetIndexCount(), worldMatrix, m_baseViewMatrix, orthoMatrix,
		m_Font->GetTexture(), m_FpsString->GetPixelColor());
	if (!result)
	{
		logger.Log("Could not render the fps text string using the font shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Render the mouse text strings using the font shader.
	for (i = 0; i < 3; i++)
	{
		m_MouseStrings[i].Render(m_Direct3D->GetDeviceContext());

		result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_MouseStrings[i].GetIndexCount(), worldMatrix, m_baseViewMatrix, orthoMatrix,
			m_Font->GetTexture(), m_MouseStrings[i].GetPixelColor());
		if (!result)
		{
			logger.Log("Could not render the mouse text strings using the font shader", __FILE__, __LINE__, Logger::LogLevel::Error);
			return false;
		}
	}

	// Put the sprite vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Sprite->Render(m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the sprite with the texture shader.
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix,
		m_Sprite->GetTexture());
	if (!result)
	{
		logger.Log("Could not render the sprite using the texture shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	//scaleMatrix = XMMatrixScaling(0.75f, 0.75f, 0.75f);  // Build the scaling matrix.
	//rotateMatrix = XMMatrixRotationY(rotation);  // Build the rotation matrix.
	//translateMatrix = XMMatrixTranslation(x, y, z);  // Build the translation matrix.

	//// Multiply the scale, rotation, and translation matrices together to create the final world transformation matrix.
	//srMatrix = XMMatrixMultiply(scaleMatrix, rotateMatrix);
	//worldMatrix = XMMatrixMultiply(srMatrix, translateMatrix);

	// Render the model using the multitexture shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	scaleMatrix = XMMatrixScaling(2.0f, 2.0f, 2.0f);  // Build the scaling matrix.
	rotateMatrix = XMMatrixRotationY(-rotation);  // Build the rotation matrix.
	translateMatrix = XMMatrixTranslation(-x, -y, -z);  // Build the translation matrix.

	// Multiply the scale, rotation, and translation matrices together to create the final world transformation matrix.
	srMatrix = XMMatrixMultiply(scaleMatrix, rotateMatrix);
	worldMatrix = XMMatrixMultiply(srMatrix, translateMatrix);

	// Get the light properties.
	for (i = 0; i < m_numLights; i++)
	{
		// Create the diffuse color array from the four light colors.
		diffuseColor[i] = m_Lights[i]->GetDiffuseColor();

		// Create the light position array from the four light positions.
		lightPosition[i] = m_Lights[i]->GetPosition();
	}

	// Translate to where the bath model will be rendered.
	worldMatrix = XMMatrixTranslation(0.0f, -10.0f, 0.0f);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BathModel->Render(m_Direct3D->GetDeviceContext());

	// Render the bath model using the light shader.
	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_BathModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_BathModel->GetTexture(0));
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// Get the camera reflection view matrix.
	m_Camera->GetReflectionViewMatrix(reflectionMatrix);

	// Translate to where the water model will be rendered.
	worldMatrix = XMMatrixTranslation(0.0f, m_waterHeight, 0.0f);

	// Put the water model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_WaterModel->Render(m_Direct3D->GetDeviceContext());

	// Render the water model using the water shader.
	result = m_ShaderManager->RenderWaterShader(m_Direct3D->GetDeviceContext(), m_WaterModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix,
		m_ReflectionTexture->GetShaderResourceView(), m_RefractionTexture->GetShaderResourceView(), m_WaterModel->GetTexture(0),
		m_waterTranslation, 0.01f);
	if (!result)
	{
		return false;
	}

	

	// Setup matrices.
	rotateMatrix = XMMatrixRotationY(rotation);
	translateMatrix = XMMatrixTranslation(-5.0f, 1.0f, -20.0f);
	worldMatrix = XMMatrixMultiply(rotateMatrix, translateMatrix);

	// Render the model using the alpha map shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderAlphaMapShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(0), m_Model->GetTexture(5), m_Model->GetTexture(3));
	if (!result)
	{
		logger.Log("Could not render the model using the alpha map shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Setup matrices.
	rotateMatrix = XMMatrixRotationY(rotation);
	translateMatrix = XMMatrixTranslation(-5.0f, -5.0f, -20.0f);
	worldMatrix = XMMatrixMultiply(rotateMatrix, translateMatrix);

	// Render the model using the texture shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(0));
	if (!result)
	{
		logger.Log("Could not render the model using the texture shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Setup matrices.
	rotateMatrix = XMMatrixRotationY(rotation);
	translateMatrix = XMMatrixTranslation(0.0f, 1.0f, -20.0f);
	worldMatrix = XMMatrixMultiply(rotateMatrix, translateMatrix);

	// Render the model using the render map shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderNormalMapShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(0), m_Model->GetTexture(1), m_Lights[0]->GetDirection(), m_Lights[0]->GetDiffuseColor());
	if (!result)
	{
		logger.Log("Could not render the model using the normal map shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}
	

	// Setup matrices.
	rotateMatrix = XMMatrixRotationY(rotation);
	translateMatrix = XMMatrixTranslation(0.0f, -2.0f, -20.0f);
	worldMatrix = XMMatrixMultiply(rotateMatrix, translateMatrix);

	// Render the model using the multitexture shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderMultitextureShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(0), m_Model->GetTexture(5));
	if (!result)
	{
		logger.Log("Could not render the model using the multitexture shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}
	

	// Setup matrices.
	rotateMatrix = XMMatrixRotationY(rotation);
	translateMatrix = XMMatrixTranslation(0.0f, -5.0f, -20.0f);
	worldMatrix = XMMatrixMultiply(rotateMatrix, translateMatrix);

	// Render the model using the translate shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderTranslateShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(0), textureTranslation);
	if (!result)
	{
		logger.Log("Could not render the model using the translate shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Setup matrices.
	rotateMatrix = XMMatrixRotationY(rotation);
	translateMatrix = XMMatrixTranslation(-5.0f, -2.0f, -20.0f);
	worldMatrix = XMMatrixMultiply(rotateMatrix, translateMatrix);

	// Render the model using the specular map shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderSpecMapShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(0), m_Model->GetTexture(1), m_Model->GetTexture(2), m_Lights[0]->GetDirection(), m_Lights[0]->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Lights[0]->GetSpecularColor(), m_Lights[0]->GetSpecularPower());
	if (!result)
	{
		logger.Log("Could not render the model using the specular map shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Setup matrices.
	rotateMatrix = XMMatrixRotationY(rotation);
	translateMatrix = XMMatrixTranslation(-10.0f, -5.0f, -20.0f);
	worldMatrix = XMMatrixMultiply(rotateMatrix, translateMatrix);

	// Render the model using the transparent shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderTransparentShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0), blendAmount);
	if (!result)
	{
		logger.Log("Could not render the model using the transparent shader", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Setup matrices.
	rotateMatrix = XMMatrixRotationY(rotation);
	translateMatrix = XMMatrixTranslation(-10.0f, -2.0f, -20.0f);
	worldMatrix = XMMatrixMultiply(rotateMatrix, translateMatrix);

	// Render the model using the transparent shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderlightShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0), diffuseColor, lightPosition, ambientColor);
	if (!result)
	{
		return false;
	}

	// Setup matrices.
	rotateMatrix = XMMatrixRotationY(rotation);
	translateMatrix = XMMatrixTranslation(-10.0f, 1.0f, -20.0f);
	worldMatrix = XMMatrixMultiply(rotateMatrix, translateMatrix);

	// Render the model using the transparent shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	result = m_ShaderManager->RenderlightMapShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0), m_Model->GetTexture(4));
	if (!result)
	{
		return false;
	}

	
	// Enable the Z buffer and disable alpha blending now that 2D rendering is complete.
	m_Direct3D->TurnZBufferOn();
	m_Direct3D->DisableAlphaBlending();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}

D3DClass* ApplicationClass::GetDirect3D()
{
	return m_Direct3D;
}

int ApplicationClass::GetScreenWidth() const
{
	return GetSystemMetrics(SM_CXSCREEN);
}

int ApplicationClass::GetScreenHeight() const
{
	return GetSystemMetrics(SM_CYSCREEN);
}

void ApplicationClass::GenerateTerrain()
{

	logger.Log("Generating terrain", __FILE__, __LINE__);

	char modelFilename[128];
	char textureFilename1[128];
	char textureFilename2[128];
	char textureFilename3[128];
	char textureFilename4[128];
	char textureFilename5[128];
	char textureFilename6[128];

	XMMATRIX scaleMatrix;
	float scaleX, scaleY, scaleZ;

	scaleX = 10.0f;
	scaleY = 1.0f;
	scaleZ = 10.0f;

	scaleMatrix = XMMatrixScaling(scaleX, scaleY, scaleZ);

	// Set the file name of the model.
	strcpy_s(modelFilename, "plane.txt");
	strcpy_s(textureFilename1, "stone01.tga");
	strcpy_s(textureFilename2, "normal01.tga");
	strcpy_s(textureFilename3, "spec02.tga");
	strcpy_s(textureFilename4, "alpha01.tga");
	strcpy_s(textureFilename5, "light01.tga");
	strcpy_s(textureFilename6, "moss01.tga");

	// for loop to generate terrain chunks for a 10x10 grid
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Object* newTerrain = new Object();
			newTerrain->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename1, textureFilename2, textureFilename3, textureFilename4, textureFilename5, textureFilename6);

			newTerrain->SetScaleMatrix(scaleMatrix);

			newTerrain->SetTranslateMatrix(XMMatrixTranslation(i / 2 * (scaleX * 2), -5.0f, j * (scaleZ * 2)));

			m_terrainChunk.push_back(newTerrain);

		}
	}

}

void ApplicationClass::AddKobject(WCHAR* filepath)
{

	logger.Log("Adding object", __FILE__, __LINE__);

	char modelFilename[128];
	char textureFilename1[128];
	char textureFilename2[128];
	char textureFilename3[128];
	char textureFilename4[128];
	char textureFilename5[128];
	char textureFilename6[128];

	filesystem::path p(filepath);
	string filename = p.stem().string();

	size_t convertedChars = 0;
	wcstombs_s(&convertedChars, modelFilename, sizeof(modelFilename), filepath, _TRUNCATE);


	// Set the name of the texture file that we will be loading.
	strcpy_s(textureFilename1, "stone01.tga");
	strcpy_s(textureFilename2, "normal01.tga");
	strcpy_s(textureFilename3, "spec02.tga");
	strcpy_s(textureFilename4, "alpha01.tga");
	strcpy_s(textureFilename5, "light01.tga");
	strcpy_s(textureFilename6, "moss01.tga");

	Object* newObject = new Object();
	newObject->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename1, textureFilename2, textureFilename3, textureFilename4, textureFilename5, textureFilename6);

	newObject->SetTranslateMatrix(XMMatrixTranslation(0.0f, 0.0f, 0.0f));
	newObject->SetName(filename);

	m_object.push_back(newObject);
}

void ApplicationClass::AddCube()
{

	logger.Log("Adding cube", __FILE__, __LINE__);

	char modelFilename[128];
	char textureFilename1[128];
	char textureFilename2[128];
	char textureFilename3[128];
	char textureFilename4[128];
	char textureFilename5[128];
	char textureFilename6[128];

	// Set the file name of the model.
	strcpy_s(modelFilename, "cube.txt");

	// Set the name of the texture file that we will be loading.
	strcpy_s(textureFilename1, "stone01.tga");
	strcpy_s(textureFilename2, "normal01.tga");
	strcpy_s(textureFilename3, "spec02.tga");
	strcpy_s(textureFilename4, "alpha01.tga");
	strcpy_s(textureFilename5, "light01.tga");
	strcpy_s(textureFilename6, "moss01.tga");
	static int cubeCount = 0;
	float position = cubeCount * 2.0f;
	Object* newCube = new Object();
	newCube->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename1, textureFilename2, textureFilename3, textureFilename4, textureFilename5, textureFilename6);

	newCube->SetTranslateMatrix(XMMatrixTranslation(position, 0.0f, 0.0f));

	m_cubes.push_back(newCube);
}

void ApplicationClass::DeleteKobject(int index)
{
	logger.Log("Deleting object", __FILE__, __LINE__);

	if (index < m_object.size())
	{
		m_object[index]->Shutdown();
		delete m_object[index];
		m_object.erase(m_object.begin() + index);
	}
}

void ApplicationClass::DeleteTerrain()
{
	logger.Log("Deleting terrain", __FILE__, __LINE__);

	for (auto cube : m_terrainChunk)
	{
		cube->Shutdown();
		delete cube;
	}
	m_terrainChunk.clear();
}

bool ApplicationClass::UpdateMouseStrings(int mouseX, int mouseY, bool mouseDown)
{
	char tempString[16], finalString[32];
	bool result;


	// Convert the mouse X integer to string format.
	sprintf_s(tempString, "%d", mouseX);

	// Setup the mouse X string.
	strcpy_s(finalString, "Mouse X: ");
	strcat_s(finalString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = m_MouseStrings[0].UpdateText(m_Direct3D->GetDeviceContext(), m_Font, finalString, 10, 50, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		logger.Log("Could not update the mouse X string", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Convert the mouse Y integer to string format.
	sprintf_s(tempString, "%d", mouseY);

	// Setup the mouse Y string.
	strcpy_s(finalString, "Mouse Y: ");
	strcat_s(finalString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = m_MouseStrings[1].UpdateText(m_Direct3D->GetDeviceContext(), m_Font, finalString, 10, 75, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		logger.Log("Could not update the mouse Y string", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Setup the mouse button string.
	if (mouseDown)
	{
		strcpy_s(finalString, "Mouse Button: Yes");
	}
	else
	{
		strcpy_s(finalString, "Mouse Button: No");
	}

	// Update the sentence vertex buffer with the new string information.
	result = m_MouseStrings[2].UpdateText(m_Direct3D->GetDeviceContext(), m_Font, finalString, 10, 100, 1.0f, 1.0f, 1.0f);

	if (!result)
	{
		logger.Log("Could not update the mouse button string", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	return true;
}

bool ApplicationClass::UpdateFps()
{
	int fps;
	char tempString[16], finalString[16];
	float red, green, blue;
	bool result;


	// Update the fps each frame.
	m_Fps->Frame();

	// Get the current fps.
	fps = m_Fps->GetFps();

	// Check if the fps from the previous frame was the same, if so don't need to update the text string.
	if (m_previousFps == fps)
	{
		return true;
	}

	// Store the fps for checking next frame.
	m_previousFps = fps;

	// Truncate the fps to below 100,000.
	if (fps > 99999)
	{
		fps = 99999;
	}

	// Convert the fps integer to string format.
	sprintf_s(tempString, "%d", fps);

	// Setup the fps string.
	strcpy_s(finalString, "Fps: ");
	strcat_s(finalString, tempString);

	// If fps is 60 or above set the fps color to green.
	if (fps >= 60)
	{
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 60 set the fps color to yellow.
	if (fps < 60)
	{
		red = 1.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 30 set the fps color to red.
	if (fps < 30)
	{
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}

	// Update the sentence vertex buffer with the new string information.
	result = m_FpsString->UpdateText(m_Direct3D->GetDeviceContext(), m_Font, finalString, 10, 10, red, green, blue);
	if (!result)
	{
		logger.Log("Could not update the fps string", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	return true;
}

bool ApplicationClass::UpdateRenderCountString(int renderCount)
{
	char tempString[16], finalString[32];
	bool result;


	// Convert the render count integer to string format.
	sprintf_s(tempString, "%d", renderCount);

	// Setup the render count string.
	strcpy_s(finalString, "Render Count: ");
	strcat_s(finalString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = m_RenderCountString->UpdateText(m_Direct3D->GetDeviceContext(), m_Font, finalString, 10, 30, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		logger.Log("Could not update the render count string", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	return true;
}

XMVECTOR ApplicationClass::GetLightColor(int index)
{
	//convert to XMVECTOR
	XMVECTOR lightColor = XMVectorSet(m_Lights[index]->GetDiffuseColor().x, m_Lights[index]->GetDiffuseColor().y, m_Lights[index]->GetDiffuseColor().z, 1.0f);

	return lightColor;
}

XMVECTOR ApplicationClass::GetLightPosition(int index)
{
	//convert to XMVECTOR
	XMVECTOR lightPosition = XMVectorSet(m_Lights[index]->GetPosition().x, m_Lights[index]->GetPosition().y, m_Lights[index]->GetPosition().z, 1.0f);

	return lightPosition;
}

void ApplicationClass::SetLightColor(int index, XMVECTOR color)
{
	//convert to XMFLOAT4
	XMFLOAT4 lightColor;
	XMStoreFloat4(&lightColor, color);

	//set the color
	m_Lights[index]->SetDiffuseColor(lightColor.x, lightColor.y, lightColor.z, 1.0f);
}

void ApplicationClass::SetLightPosition(int index, XMVECTOR position)
{
	//convert to XMFLOAT4
	XMFLOAT4 lightPosition;
	XMStoreFloat4(&lightPosition, position);

	//set the position
	m_Lights[index]->SetPosition(lightPosition.x, lightPosition.y, lightPosition.z);
}

void ApplicationClass::DeleteLight(int index)
{
	logger.Log("Deleting light", __FILE__, __LINE__);

	if (index < 0 || index >= m_Lights.size())
	{
		// Index out of bounds
		return;
	}

	// Delete the light object
	delete m_Lights[index];

	// Remove the light from the vector
	m_Lights.erase(m_Lights.begin() + index);
}
