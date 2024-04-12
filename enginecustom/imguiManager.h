#pragma once
#ifndef _IMGUI_MANAGER_H_
#define _IMGUI_MANAGER_H_

#include "Logger.h"	

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <windows.h>

class ApplicationClass;

class imguiManager
{
public:
	imguiManager();
	~imguiManager();

	bool Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown();
	void Render();
	void NewFrame();

	// Widgets
	void WidgetSpeedSlider(float* speed);
	void WidgetButton();
	void WidgetFPS();
	void WidgetAddObject(ApplicationClass* app);

	void WidgetObjectWindow(ApplicationClass* app);
	void WidgetTerrainWindow(ApplicationClass* app);
	void WidgetLightWindow(ApplicationClass* app);

	bool ImGuiWidgetRenderer(ApplicationClass* app);

private :
	bool showObjectWindow = false;
	bool showTerrainWindow = false;
	bool showLightWindow = false;

private:
	ImGuiIO* io;

};

#endif