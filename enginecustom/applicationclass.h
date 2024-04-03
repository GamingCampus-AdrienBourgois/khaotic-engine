#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
<<<<<<< Updated upstream
=======
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

>>>>>>> Stashed changes

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
	bool Frame();

	int GetScreenWidth() const;
	int GetScreenHeight() const;

	float GetSpeed() const { return speed; };
	void SetSpeed(float speed) { this->speed = speed; };

private:
<<<<<<< Updated upstream
	bool Render(float);
=======
	bool Render(float, float, float, float);
	bool RenderSceneToTexture(float);
	bool UpdateMouseStrings(int, int, bool);
	bool UpdateFps();
	bool UpdateRenderCountString(int);
>>>>>>> Stashed changes

private:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	IDXGISwapChain* m_swapChain;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
<<<<<<< Updated upstream
	float speed = 0.1f;
=======
	LightMapShaderClass* m_LightMapShader;
	MultiTextureShaderClass* m_MultiTextureShader;
	AlphaMapShaderClass* m_AlphaMapShader;
	ModelClass* m_Model;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
	SpriteClass* m_Sprite;
    TimerClass* m_Timer;
	TextClass* m_MouseStrings;
	LightClass* m_Lights;
	int m_numLights;
	FontShaderClass* m_FontShader;
	TextClass* m_RenderCountString;
	FontClass* m_Font;
	TextClass *m_TextString1, *m_TextString2, *m_TextString3;
	FpsClass* m_Fps;
	TextClass* m_FpsString;
	int m_previousFps;
	NormalMapShaderClass* m_NormalMapShader;
	SpecMapShaderClass* m_SpecMapShader;
	ModelListClass* m_ModelList;
	PositionClass* m_Position;
	FrustumClass* m_Frustum;
	XMMATRIX m_baseViewMatrix;
	float m_previousMouseX;
	float m_previousMouseY;
	RenderTextureClass* m_RenderTexture;
	DisplayPlaneClass* m_DisplayPlane;
>>>>>>> Stashed changes
};

#endif
