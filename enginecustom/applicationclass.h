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

/////////////
// GLOBALS //
/////////////
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
	void SetFullscreen(bool fullscreen);
	bool GetFullscreen() const;
	int GetScreenWidth() const;
	int GetScreenHeight() const;

private:
	bool Render(float);

private:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	IDXGISwapChain* m_swapChain;
	bool m_fullscreen = false;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
};

#endif
