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

	void AddCube();
	int GetCubeCount() const { return m_cubes.size(); };
	std::vector<Object*> GetCubes() const { return m_cubes; };

private:
	bool Render(float);

private:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	IDXGISwapChain* m_swapChain;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	float speed = 0.1f;
	std::vector<Object*> m_cubes;
	Object* m_SelectedObject;
};

#endif
