#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define DIRECTINPUT_VERSION 0x0800

/////////////
// LINKING //
/////////////
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//////////////
// INCLUDES //
//////////////
#include <dinput.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsEscapePressed() const;
	void GetMouseLocation(int&, int&) const;
	bool IsLeftMousePressed() const;
	bool IsRightMousePressed() const;
	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	bool IsLeftArrowPressed() const;
	bool IsRightArrowPressed() const;
	bool IsScrollUp() const;
	bool IsScrollDown() const;
	bool IsUpArrowPressed() const;
	bool IsDownArrowPressed() const;
	bool IsAPressed() const;
	bool IsDPressed() const;
	bool IsWPressed() const;
	bool IsSPressed() const;
	bool IsQPressed() const;
	bool IsEPressed()const;

	bool IsKeyDown(unsigned int) const;

private:
	bool m_keys[256];

	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight, m_mouseX, m_mouseY;
};

#endif