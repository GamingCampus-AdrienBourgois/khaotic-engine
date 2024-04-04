#include "applicationclass.h"

ApplicationClass::ApplicationClass()
{
	m_Direct3D = 0;
	m_Camera = 0; 
	m_MultiTextureShader = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_TextureShader = 0;
	m_Bitmap = 0;
	m_Sprite = 0;
	m_Timer = 0;
	m_Lights = 0;
	m_FontShader = 0;
	m_Font = 0;
	m_TextString1 = 0;
	m_TextString2 = 0;
	m_TextString3 = 0;
	m_Fps = 0;
	m_FpsString = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	char testString1[32], testString2[32], testString3[32];
	char modelFilename[128];
	char textureFilename1[128], textureFilename2[128];
	char bitmapFilename[128];
	char spriteFilename[128];
	char fpsString[32];
	bool result;

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	GenerateTerrain();

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -12.0f);
	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);

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

	// Set the sprite info file we will be using.
	strcpy_s(spriteFilename, "sprite_data_01.txt");

	// Create and initialize the sprite object.
	m_Sprite = new SpriteClass;

	result = m_Sprite->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, spriteFilename, 50, 50);
	if (!result)
	{
		return false;
	}

	// Create and initialize the timer object.
	m_Timer = new TimerClass;

	result = m_Timer->Initialize();
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
	strcpy_s(modelFilename, "plane.txt");

	// Set the file name of the textures.
	strcpy_s(textureFilename1, "stone01.tga");
	strcpy_s(textureFilename2, "moss01.tga");

	// Create and initialize the model object.
	m_Model = new ModelClass;

	result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename1, textureFilename2);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
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

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Liberez la memoire pour chaque cube
	for (auto cube : m_cubes)
	{
		cube->Shutdown();
		delete cube;
	}
	m_cubes.clear();

	// Liberez la memoire pour chaque cube du terrain
	for (auto cube : m_terrainChunk)
	{
		cube->Shutdown();
		delete cube;
	}
	m_terrainChunk.clear();

	for (auto object : m_object)
	{
		object->Shutdown();
		delete object;
	}
	m_object.clear();

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
}


bool ApplicationClass::Frame()
{
	float frameTime;
	static float rotation = 0.0f;
	static float x = 2.f;
	static float y = 0.f;
	static float z = 0.f;
	bool result;

	// Update the frames per second each frame.
	result = UpdateFps();
	if (!result)
	{
		return false;
	}

	// Update the rotation variable each frame.
	rotation -= 0.0174532925f * speed;
	if (rotation < 0.0f)
	{
		rotation += 360.0f;
	}

	// Update the x position variable each frame.
	x -= 0.0174532925f * 0.54672f;

	y -= 0.0174532925f * 0.8972f;

	// Update the z position variable each frame.
	z -= 0.0174532925f * 0.8972f;


	// Render the graphics scene.
	result = Render(rotation, x, y, z);
	if (!result)
	{
		return false;
	}

	// Update the system stats.
	m_Timer->Frame();

	// Get the current frame time.
	frameTime = m_Timer->GetTime();

	// Update the sprite object using the frame time.
	m_Sprite->Update(frameTime);

	return true;
}


bool ApplicationClass::Render(float rotation, float x, float y, float z)
{
	XMMATRIX worldMatrix, viewMatrix, orthoMatrix, projectionMatrix, rotateMatrix, translateMatrix, scaleMatrix, srMatrix;
	XMFLOAT4 diffuseColor[4], lightPosition[4];
	int i;
	bool result;

	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	viewMatrix = m_Camera->GetViewMatrix();
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// Disable the Z buffer and enable alpha blending for 2D rendering.
	m_Direct3D->TurnZBufferOff();
	m_Direct3D->EnableAlphaBlending();

	// Render the fps text string using the font shader.
	m_FpsString->Render(m_Direct3D->GetDeviceContext());

	result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_FpsString->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix,
		m_Font->GetTexture(), m_FpsString->GetPixelColor());
	if (!result)
	{
		return false;
	}

	// Render the first text string using the font shader.
	m_TextString1->Render(m_Direct3D->GetDeviceContext());

	result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_TextString1->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix,
		m_Font->GetTexture(), m_TextString1->GetPixelColor());
	if (!result)
	{
		return false;
	}

	// Render the second text string using the font shader.
	m_TextString2->Render(m_Direct3D->GetDeviceContext());

	result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_TextString2->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix,
		m_Font->GetTexture(), m_TextString2->GetPixelColor());
	if (!result)
	{
		return false;
	}

	// Render the second text string using the font shader.
	m_TextString3->Render(m_Direct3D->GetDeviceContext());

	result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_TextString3->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix,
		m_Font->GetTexture(), m_TextString3->GetPixelColor());
	if (!result)
	{
		return false;
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

	// Get the light properties.
	for (i = 0; i < m_numLights; i++)
	{
		// Create the diffuse color array from the four light colors.
		diffuseColor[i] = m_Lights[i].GetDiffuseColor();

		// Create the light position array from the four light positions.
		lightPosition[i] = m_Lights[i].GetPosition();
	}

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
		diffuseColor[i] = m_Lights[i].GetDiffuseColor();

		// Create the light position array from the four light positions.
		lightPosition[i] = m_Lights[i].GetPosition();
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
	result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0),
		diffuseColor, lightPosition);
	
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

		result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0),
			diffuseColor, lightPosition);
		if (!result)
		{
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

		result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0),
			diffuseColor, lightPosition);

		if (!result)
			{
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

		result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(0),
						diffuseColor, lightPosition);
		if (!result)
		{
			return false;
		}
	}



	// Render the model using the multitexture shader.
	//result = m_MultiTextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(0), m_Model->GetTexture(1));

	if (!result)
	{
		return false;
	}

	

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
	char modelFilename[128];
	char textureFilename[128];
	char textureFilename2[128];
	// Set the file name of the model.
	strcpy_s(modelFilename, "plane.txt");
	strcpy_s(textureFilename, "stone01.tga");
	strcpy_s(textureFilename2, "moss01.tga");

	// for loop to generate terrain chunks for a 10x10 grid
	for (int i = -5; i < 5; i++)
	{
		for (int j = -5; j < 5; j++)
		{
			Object* newTerrain = new Object();
			newTerrain->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename, textureFilename2);

			newTerrain->SetTranslateMatrix(XMMatrixTranslation(i*10, -5.0f, j*10));

			m_terrainChunk.push_back(newTerrain);

		}
	}

}

void ApplicationClass::AddKobject(WCHAR* filepath)
{
	char modelFilename[128];
	char textureFilename[128];
	char textureFilename2[128];
	filesystem::path p(filepath);
	string filename = p.stem().string();

	size_t convertedChars = 0;
	wcstombs_s(&convertedChars, modelFilename, sizeof(modelFilename), filepath, _TRUNCATE);


	// Set the name of the texture file that we will be loading.
	strcpy_s(textureFilename, "stone01.tga");
	strcpy_s(textureFilename2, "moss01.tga");

	Object* newObject = new Object();
	newObject->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename, textureFilename2);

	newObject->SetTranslateMatrix(XMMatrixTranslation(0.0f, 0.0f, 0.0f));
	newObject->SetName(filename);

	m_object.push_back(newObject);
}

void ApplicationClass::AddCube()
{
	char modelFilename[128];
	char textureFilename[128];
	char textureFilename2[128];

	// Set the file name of the model.
	strcpy_s(modelFilename, "cube.txt");

	// Set the name of the texture file that we will be loading.
	strcpy_s(textureFilename, "stone01.tga");
	strcpy_s(textureFilename2, "moss01.tga");
	static int cubeCount = 0;
	float position = cubeCount * 2.0f;
	Object* newCube = new Object();
	newCube->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename, textureFilename2);

	newCube->SetTranslateMatrix(XMMatrixTranslation(position, 0.0f, 0.0f));

	m_cubes.push_back(newCube);
}

void ApplicationClass::DeleteKobject(int index)
{
	if (index < m_object.size())
	{
		m_object[index]->Shutdown();
		delete m_object[index];
		m_object.erase(m_object.begin() + index);
	}
}

void ApplicationClass::DeleteTerrain()
{
	for (auto cube : m_terrainChunk)
	{
		cube->Shutdown();
		delete cube;
	}
	m_terrainChunk.clear();

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