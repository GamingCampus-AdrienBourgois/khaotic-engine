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

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(InputClass*);

private:
	bool Render(float, float, float, float);
	bool UpdateMouseStrings(int, int, bool);
	bool UpdateFps();
	bool UpdateRenderCountString(int);

private:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
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
	float m_screenWidth, m_screenHeight;
};

#endif
