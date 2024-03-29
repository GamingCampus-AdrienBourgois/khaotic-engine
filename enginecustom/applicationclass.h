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
#include "multitextureshaderclass.h"
#include "bitmapclass.h"
#include "textureshaderclass.h"
#include "spriteclass.h"
#include "timerclass.h"
#include "textclass.h"

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

private:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	MultiTextureShaderClass* m_MultiTextureShader;
	ModelClass* m_Model;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
	SpriteClass* m_Sprite;
    TimerClass* m_Timer;
	TextClass* m_MouseStrings;
};

#endif
