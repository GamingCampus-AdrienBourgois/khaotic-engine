#pragma once
#ifndef _IMGUI_MANAGER_H_
#define _IMGUI_MANAGER_H_

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <windows.h>

class imguiManager
{
public:
	imguiManager();
	~imguiManager();

	bool Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown();
	void Render();
	void NewFrame();
	void WidgetFullscreenBox(bool* fullscreen);

private:
	ImGuiIO* io;
};

#endif