#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "object.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include <vector>
#include <filesystem>

#include "lightmapshaderclass.h"
#include "multitextureshaderclass.h"
#include "alphamapshaderclass.h"
#include "bitmapclass.h"
#include "textureshaderclass.h"
#include "spriteclass.h"
#include "timerclass.h"
#include "fontshaderclass.h"
#include "fontclass.h"
#include "textclass.h"
#include "fpsclass.h"
#include "inputclass.h"
#include "normalmapshaderclass.h"
#include "specmapshaderclass.h"
#include "modellistclass.h"
#include "positionclass.h"
#include "frustumclass.h"
#include "rendertextureclass.h"
#include "displayplaneclass.h"
#include "translateshaderclass.h"
#include "reflectionshaderclass.h"
#include "physics.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.3f;


////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();
	D3DClass* GetDirect3D();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(InputClass*);

	int GetScreenWidth() const;
	int GetScreenHeight() const;

	float GetSpeed() const { return m_speed; };
	void SetSpeed(float speed) { this->m_speed = speed; };

	void AddCube();
	void DeleteKobject(int index);
	int GetCubeCount() const { return m_cubes.size(); };
	int GetTerrainCubeCount() const { return m_terrainChunk.size(); };
	std::vector<Object*> GetCubes() const { return m_cubes; };
	std::vector<Object*> GetTerrainCubes() const { return m_terrainChunk; };
	std::vector<Object*> GetKobjects() const { return m_object; };
	void AddKobject(WCHAR* filepath);

	void GenerateTerrain();
	void DeleteTerrain();

private:
	bool Render(float, float, float, float);
	bool UpdateMouseStrings(int, int, bool);
	bool UpdateFps();
	bool UpdateRenderCountString(int);
	bool RenderSceneToTexture(float);

private :

	// ------------------------------------- //
	// ------------- DIRECT3D -------------- //
	// ------------------------------------- //

	D3DClass* m_Direct3D;
	IDXGISwapChain* m_swapChain;
	ModelClass* m_Model;
	ModelListClass* m_ModelList;

	// ------------------------------------- //
	// ------------- RENDERING ------------- //
	// ------------------------------------- //

	XMMATRIX m_baseViewMatrix;
	RenderTextureClass* m_RenderTexture;
	DisplayPlaneClass* m_DisplayPlane;
	float m_screenWidth, m_screenHeight;
	CameraClass* m_Camera;
	PositionClass* m_Position;
	FrustumClass* m_Frustum;

	// ------------------------------------ //
	// ------------- OBJECTS -------------- //
	// ------------------------------------ //

	Object* m_SelectedObject;
	std::vector<Object*> m_cubes;
	std::vector<Object*> m_terrainChunk;
	float m_speed = 0.1f; // speed for the demo spinning object
	std::vector<Object*> m_object;
	int m_ObjectId = 0;

	// ----------------------------------- //
	// ------------- LIGHTS -------------- //
	// ----------------------------------- //

	LightClass* m_Light;
	LightClass* m_Lights;
	int m_numLights;

	// ----------------------------------- //
	// ------------- SHADERS ------------- //
	// ----------------------------------- //

	LightShaderClass* m_LightShader;
	LightMapShaderClass* m_LightMapShader;
	MultiTextureShaderClass* m_MultiTextureShader;
	AlphaMapShaderClass* m_AlphaMapShader;
	TextureShaderClass* m_TextureShader;
	FontShaderClass* m_FontShader;
	NormalMapShaderClass* m_NormalMapShader;
	SpecMapShaderClass* m_SpecMapShader;
	TranslateShaderClass* m_TranslateShader;
	ReflectionShaderClass* m_ReflectionShader;

	BitmapClass* m_Bitmap;
	SpriteClass* m_Sprite;

	// ------------------------------------------------- //
	// ------------- FPS AND INFO ON SCREEN ------------ //
	// ------------------------------------------------- //

	TimerClass* m_Timer;
	TextClass* m_MouseStrings;
	TextClass* m_RenderCountString;
	FontClass* m_Font;
	TextClass* m_TextString1, * m_TextString2, * m_TextString3;
	FpsClass* m_Fps;
	TextClass* m_FpsString;
	int m_previousFps;

	Physics* m_Physics;
	float m_gravity;
	XMVECTOR m_previousPosition;
};

#endif