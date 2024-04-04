#include "applicationclass.h"

ApplicationClass::ApplicationClass()
{
	m_Direct3D = 0;
	m_Camera = 0; 
	m_MultiTextureShader = 0;
	m_AlphaMapShader = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_LightMapShader = 0;
	m_Light = 0;
	m_TextureShader = 0;
	m_Bitmap = 0;
	m_Sprite = 0;
	m_Timer = 0;
	m_MouseStrings = 0;
	m_FontShader = 0;
	m_Font = 0;
	m_TextString1 = 0;
	m_TextString2 = 0;
	m_TextString3 = 0;
	m_Fps = 0;
	m_FpsString = 0;
	m_NormalMapShader = 0;
	m_SpecMapShader = 0;
	m_RenderCountString = 0;
	m_ModelList = 0;
	m_Position = 0;
	m_Frustum = 0;
	m_DisplayPlane = 0;
	m_TranslateShader = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	char mouseString1[32], mouseString2[32], mouseString3[32];
	char testString1[32], testString2[32], testString3[32];
	char modelFilename[128], textureFilename1[128], textureFilename2[128], textureFilename3[128], renderString[32];
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
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -12.0f);
	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(m_baseViewMatrix);

	// Create and initialize the specular map shader object.
	m_SpecMapShader = new SpecMapShaderClass;

	result = m_SpecMapShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the specular map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the normal map shader object.
	m_NormalMapShader = new NormalMapShaderClass;

	result = m_NormalMapShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the normal map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the font shader object.
	m_FontShader = new FontShaderClass;

	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the font object.
	m_Font = new FontClass;

	result = m_Font->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), 0);
	if (!result)
	{
		return false;
	}

	// Set the strings we want to display.
	strcpy_s(testString1, "Yo");
	strcpy_s(testString2, "Les");
	strcpy_s(testString3, "Noobs !");

	// Create and initialize the first text object.
	m_TextString1 = new TextClass;

	result = m_TextString1->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, testString1, 25, screenHeight / 2 - m_Font->GetFontHeight(), 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	// Create and initialize the second text object.
	m_TextString2 = new TextClass;

	result = m_TextString2->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, testString2, 250, screenHeight / 2 - m_Font->GetFontHeight(), 0.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	// Create and initialize the second text object.
	m_TextString3 = new TextClass;

	result = m_TextString3->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, testString3, screenWidth / 2 - m_Font->GetSentencePixelLength(testString3), screenHeight / 2 - m_Font->GetFontHeight(), 1.0f, 1.0f, 0.0f);
	if (!result)
	{
		return false;
	}

	// Create and initialize the texture shader object.
	m_TextureShader = new TextureShaderClass;

	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the render to texture object.
	m_RenderTexture = new RenderTextureClass;

	result = m_RenderTexture->Initialize(m_Direct3D->GetDevice(), 256, 256, SCREEN_DEPTH, SCREEN_NEAR, 1);
	if (!result)
	{
		return false;
	}

	// Create and initialize the display plane object.
	m_DisplayPlane = new DisplayPlaneClass;

	result = m_DisplayPlane->Initialize(m_Direct3D->GetDevice(), 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}


	// Set the sprite info file we will be using.
	strcpy_s(spriteFilename, "sprite_data_01.txt");

	// Create and initialize the sprite object.
	m_Sprite = new SpriteClass;

	result = m_Sprite->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, spriteFilename, 50, 50);
	if (!result)
	{
		return false;
	}

	// Set the initial mouse strings.
	strcpy_s(mouseString1, "Mouse X: 0");
	strcpy_s(mouseString2, "Mouse Y: 0");
	strcpy_s(mouseString3, "Mouse Button: No");

	// Create and initialize the text objects for the mouse strings.
	m_MouseStrings = new TextClass[3];

	result = m_MouseStrings[0].Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, mouseString1, 10, 10, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	result = m_MouseStrings[1].Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, mouseString1, 10, 35, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	result = m_MouseStrings[2].Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, mouseString1, 10, 60, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	// Set the file name of the bitmap file.
	strcpy_s(bitmapFilename, "stone01.tga");

	// Create and initialize the bitmap object.
	m_Bitmap = new BitmapClass;

	result = m_Bitmap->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, bitmapFilename, 50, 50);
	if (!result)
	{
		return false;
	}

	// Create and initialize the multitexture shader object.
	m_MultiTextureShader = new MultiTextureShaderClass;

	result = m_MultiTextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the multitexture shader object.", L"Error", MB_OK);
		return false;
	}

	// Set the file name of the model.
	strcpy_s(modelFilename, "cube.txt");

	// Set the file name of the textures.
	strcpy_s(textureFilename1, "stone01.tga");
	strcpy_s(textureFilename2, "normal01.tga");
	strcpy_s(textureFilename3, "alpha01.tga");
	// A FAIRE: Ajouter une nouvelle texture pour le multitexturing

	// Create and initialize the model object.
	m_Model = new ModelClass;

	result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename1, textureFilename2, textureFilename3);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the translate shader object.
	m_TranslateShader = new TranslateShaderClass;

	result = m_TranslateShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the translate shader object.", L"Error", MB_OK);
		return false;
	}


	// Create and initialize the light shader object.
	m_LightShader = new LightShaderClass;

	result = m_LightShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the light object.
	m_Light = new LightClass;

	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(16.0f);

	// Set the number of lights we will use.
	m_numLights = 4;

	// Create and initialize the light objects array.
	m_Lights = new LightClass[m_numLights];

	// Manually set the color and position of each light.
	m_Lights[0].SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);  // Red
	m_Lights[0].SetPosition(-3.0f, 1.0f, 3.0f);

	m_Lights[1].SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);  // Green
	m_Lights[1].SetPosition(3.0f, 1.0f, 3.0f);

	m_Lights[2].SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);  // Blue
	m_Lights[2].SetPosition(-3.0f, 1.0f, -3.0f);

	m_Lights[3].SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);  // White
	m_Lights[3].SetPosition(3.0f, 1.0f, -3.0f);

	// Create and initialize the light map shader object.
	m_LightMapShader = new LightMapShaderClass;

	result = m_LightMapShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the alpha map shader object.
	m_AlphaMapShader = new AlphaMapShaderClass;

	result = m_AlphaMapShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the alpha map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the font shader object.
	m_FontShader = new FontShaderClass;

	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the font object.
	m_Font = new FontClass;

	result = m_Font->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), 0);
	if (!result)
	{
		return false;
	}

	// Set the initial render count string.
	strcpy_s(renderString, "Render Count: 0");

	// Create and initialize the text object for the render count string.
	m_RenderCountString = new TextClass;

	result = m_RenderCountString->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, renderString, 10, 10, 1.0f, 1.0f, 1.0f);
	if (!result)
	{
		return false;
	}

	// Create and initialize the model list object.
	m_ModelList = new ModelListClass;
	m_ModelList->Initialize(25);

	// Create and initialize the timer object.
	m_Timer = new TimerClass;

	result = m_Timer->Initialize();
	if (!result)
	{
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
		return false;
	}


	return true;
}


void ApplicationClass::Shutdown()
{
	// Release the translate shader object.
	if (m_TranslateShader)
	{
		m_TranslateShader->Shutdown();
		delete m_TranslateShader;
		m_TranslateShader = 0;
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

	// Release the text string objects.
	if (m_TextString3)
	{
		m_TextString3->Shutdown();
		delete m_TextString3;
		m_TextString3 = 0;
	}

	if (m_TextString2)
	{
		m_TextString2->Shutdown();
		delete m_TextString2;
		m_TextString2 = 0;
	}

	if (m_TextString1)
	{
		m_TextString1->Shutdown();
		delete m_TextString1;
		m_TextString1 = 0;
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

	  // Release the light objects.
    if(m_Lights)
    {
        delete [] m_Lights;
        m_Lights = 0;
    }

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the specular map shader object.
	if (m_SpecMapShader)
	{
		m_SpecMapShader->Shutdown();
		delete m_SpecMapShader;
		m_SpecMapShader = 0;
	}

	// Release the normal map shader object.
	if (m_NormalMapShader)
	{
		m_NormalMapShader->Shutdown();
		delete m_NormalMapShader;
		m_NormalMapShader = 0;
	}

	// Release the multitexture shader object.
	if (m_MultiTextureShader)
	{
		m_MultiTextureShader->Shutdown();
		delete m_MultiTextureShader;
		m_MultiTextureShader = 0;
		// Release the bitmap object.
		if (m_Bitmap)
		{
			m_Bitmap->Shutdown();
			delete m_Bitmap;
			m_Bitmap = 0;
		}

		// Release the texture shader object.
		if (m_TextureShader)
		{
			m_TextureShader->Shutdown();
			delete m_TextureShader;
			m_TextureShader = 0;
		}

		// Release the camera object.
		if (m_Camera)
		{
			delete m_Camera;
			m_Camera = 0;
		}

		// Release the D3D object.
		if (m_Direct3D)
		{
			m_Direct3D->Shutdown();
			delete m_Direct3D;
			m_Direct3D = 0;
		}

		return;
	}

	// Release the alpha map shader object.
	if (m_AlphaMapShader)
	{
		m_AlphaMapShader->Shutdown();
		delete m_AlphaMapShader;
		m_AlphaMapShader = 0;
	}
}


bool ApplicationClass::Frame(InputClass* Input)
{
	int mouseX, mouseY, currentMouseX, currentMouseY;
	bool result, mouseDown, keyDown, buttonQ, buttonD, buttonZ, buttonS, buttonA, buttonE;
	float rotationY, rotationX, positionX, positionY, positionZ;
	static float textureTranslation = 0.0f;

	float frameTime;

	static int lastMouseX = 0, lastMouseY = 0;

	static float rotation = 360.0f;
	static float x = 6.f;
	static float y = 3.f;
	static float z = 0.f;

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

	currentMouseX = mouseX;

	float deltaX = currentMouseX - lastMouseX;  // Calculez le déplacement de la souris
	lastMouseX = currentMouseX;  // Mettez à jour la dernière position de la souris pour la prochaine image

	currentMouseY = mouseY;

	float deltaY = currentMouseY - lastMouseY;  // Calculez le déplacement de la souris
	lastMouseY = currentMouseY;  // Mettez à jour la dernière position de la souris pour la prochaine image

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(m_Timer->GetTime());

	// Check if the left or right arrow key has been pressed, if so rotate the camera accordingly.
	keyDown = Input->IsLeftArrowPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = Input->IsRightArrowPressed();
	m_Position->TurnRight(keyDown);

	m_Position->TurnMouse(deltaX, deltaY);

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
		return false;
	}

	// Update the frames per second each frame.
	result = UpdateFps();
	if (!result)
	{
		return false;
	}

	// Update the rotation variable each frame.
	rotation -= 0.0174532925f * 0.8f;
	if (rotation < 0.0f)
	{
		rotation += 360.0f;
	}

	// Update the x position variable each frame.
	x -= 0.0174532925f * 0.6f;

	y -= 0.0174532925f * 0.2f;

	// Update the z position variable each frame.
	z -= 0.0174532925f * 0.2f;

	// Render the scene to a render texture.
	result = RenderSceneToTexture(rotation);
	if (!result)
	{
		return false;
	}

	// Check if the mouse has been pressed.
	mouseDown = Input->IsMousePressed();

	// Update the mouse strings each frame.
	result = UpdateMouseStrings(mouseX, mouseY, mouseDown);
	if (!result)
	{
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

	// Render the graphics scene.
	result = Render(rotation, x, y, z, textureTranslation);
	if (!result)
	{
		return false;
	}

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
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);
	m_Camera->Render();

	// Get the matrices.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_RenderTexture->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the cube will spin.
	worldMatrix = XMMatrixRotationY(rotation);

	// Render the model using the texture shader.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(1));
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
	XMMATRIX worldMatrix, viewMatrix, orthoMatrix, projectionMatrix, rotateMatrix, translateMatrix, scaleMatrix, srMatrix;
	float positionX, positionY, positionZ, radius;
	XMFLOAT4 diffuseColor[4], lightPosition[4];
	int  modelCount, renderCount, i;
	bool result, renderModel;

	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// Setup matrices - Top display plane.
	worldMatrix = XMMatrixTranslation(0.0f, 1.5f, 0.0f);

	// Render the display plane using the texture shader and the render texture resource.
	m_DisplayPlane->Render(m_Direct3D->GetDeviceContext());

	result = m_TranslateShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(0), textureTranslation);
	if (!result)
	{
		return false;
	}

	// Setup matrices - Bottom left display plane.
	worldMatrix = XMMatrixTranslation(-1.5f, -1.5f, 0.0f);

	// Render the display plane using the texture shader and the render texture resource.
	m_DisplayPlane->Render(m_Direct3D->GetDeviceContext());

	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_DisplayPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_RenderTexture->GetShaderResourceView());
	if (!result)
	{
		return false;
	}

	// Setup matrices - Bottom right display plane.
	worldMatrix = XMMatrixTranslation(1.5f, -1.5f, 0.0f);

	// Render the display plane using the texture shader and the render texture resource.
	m_DisplayPlane->Render(m_Direct3D->GetDeviceContext());

	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_DisplayPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_RenderTexture->GetShaderResourceView());
	if (!result)
	{
		return false;
	}

	// Get the light properties.
	for (i = 0; i < m_numLights; i++)
	{
		// Create the diffuse color array from the four light colors.
		diffuseColor[i] = m_Lights[i].GetDiffuseColor();

		// Create the light position array from the four light positions.
		lightPosition[i] = m_Lights[i].GetPosition();
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

			result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Model->GetTexture(0), diffuseColor, lightPosition);
			if (!result)
			{
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
		return false;
	}

	// Render the fps text string using the font shader.
	m_FpsString->Render(m_Direct3D->GetDeviceContext());

	result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_FpsString->GetIndexCount(), worldMatrix, m_baseViewMatrix, orthoMatrix,
		m_Font->GetTexture(), m_FpsString->GetPixelColor());
	if (!result)
	{
		return false;
	}

	// Render the first text string using the font shader.
	m_TextString1->Render(m_Direct3D->GetDeviceContext());

	result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_TextString1->GetIndexCount(), worldMatrix, m_baseViewMatrix, orthoMatrix,
		m_Font->GetTexture(), m_TextString1->GetPixelColor());
	if (!result)
	{
		return false;
	}

	// Render the second text string using the font shader.
	m_TextString2->Render(m_Direct3D->GetDeviceContext());

	result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_TextString2->GetIndexCount(), worldMatrix, m_baseViewMatrix, orthoMatrix,
		m_Font->GetTexture(), m_TextString2->GetPixelColor());
	if (!result)
	{
		return false;
	}

	// Render the second text string using the font shader.
	m_TextString3->Render(m_Direct3D->GetDeviceContext());

	result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_TextString3->GetIndexCount(), worldMatrix, m_baseViewMatrix, orthoMatrix,
		m_Font->GetTexture(), m_TextString3->GetPixelColor());
	if (!result)
	{
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
	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Sprite->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Sprite->GetTexture());
	if (!result)
	{
		return false;
	}

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	m_Bitmap->SetRenderLocation(1200, 50);

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	//scaleMatrix = XMMatrixScaling(0.75f, 0.75f, 0.75f);  // Build the scaling matrix.
	//rotateMatrix = XMMatrixRotationY(rotation);  // Build the rotation matrix.
	//translateMatrix = XMMatrixTranslation(x, y, z);  // Build the translation matrix.

	//// Multiply the scale, rotation, and translation matrices together to create the final world transformation matrix.
	//srMatrix = XMMatrixMultiply(scaleMatrix, rotateMatrix);
	//worldMatrix = XMMatrixMultiply(srMatrix, translateMatrix);

	//// Render the model using the multitexture shader.
	//m_Model->Render(m_Direct3D->GetDeviceContext());

	// Lighting, utilise plusieurs lights donc Multiple Points Lighting
	//result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0),
	//	diffuseColor, lightPosition);
	//if (!result)
	//{
	//	return false;
	//}

	// Lightmapping, utiliser light01.tga en deuxieme texture
	//result = m_LightMapShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(0), m_Model->GetTexture(1));
	//if (!result)
	//{
	//	return false;
	//}

	// MultiTexturing
	//result = m_MultiTextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(0), m_Model->GetTexture(1));
	//if (!result)
	//{
	//	return false;
	//}

	// Alphamapping
	/*result = m_AlphaMapShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(0), m_Model->GetTexture(1), m_Model->GetTexture(2));
	if (!result)
	{
		return false;
	}*/

	////Normal Mapping
	//result = m_NormalMapShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(0), m_Model->GetTexture(1), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	//if (!result)
	//{
	//	return false;
	//}

	////Specular Mapping
	//result = m_SpecMapShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(0), m_Model->GetTexture(1), m_Model->GetTexture(2), m_Light->GetDirection(), m_Light->GetDiffuseColor(),
	//	m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	//if (!result)
	//{
	//	return false;
	//}

	//scaleMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);  // Build the scaling matrix.
	//rotateMatrix = XMMatrixRotationY(40);  // Build the rotation matrix.
	//translateMatrix = XMMatrixTranslation(0, -2.0f, -10.0f);  // Build the translation matrix.

	//// Multiply the scale, rotation, and translation matrices together to create the final world transformation matrix.
	//srMatrix = XMMatrixMultiply(scaleMatrix, rotateMatrix);
	//worldMatrix = XMMatrixMultiply(srMatrix, translateMatrix);

	//// Render the model using the multitexture shader.
	//m_Model->Render(m_Direct3D->GetDeviceContext());

	////Normal Mapping
	//result = m_NormalMapShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(0), m_Model->GetTexture(1), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	//if (!result)
	//{
	//	return false;
	//}

	//scaleMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);  // Build the scaling matrix.
	//rotateMatrix = XMMatrixRotationY(40);  // Build the rotation matrix.
	//translateMatrix = XMMatrixTranslation(0, 5.0f, -10.0f);  // Build the translation matrix.

	//// Multiply the scale, rotation, and translation matrices together to create the final world transformation matrix.
	//srMatrix = XMMatrixMultiply(scaleMatrix, rotateMatrix);
	//worldMatrix = XMMatrixMultiply(srMatrix, translateMatrix);

	//// Render the model using the multitexture shader.
	//m_Model->Render(m_Direct3D->GetDeviceContext());

	////Normal Mapping
	//result = m_NormalMapShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(0), m_Model->GetTexture(1), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	//if (!result)
	//{
	//	return false;
	//}

	// Enable the Z buffer and disable alpha blending now that 2D rendering is complete.
	m_Direct3D->TurnZBufferOn();
	m_Direct3D->DisableAlphaBlending();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
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
		return false;
	}

	return true;
}