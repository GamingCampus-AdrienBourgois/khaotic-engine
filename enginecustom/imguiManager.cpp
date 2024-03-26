#include "imguiManager.h"
#include "applicationclass.h"
#include <string>

imguiManager::imguiManager()
{
	io = nullptr;
}

imguiManager::~imguiManager()
{
}

bool imguiManager::Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO();

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, deviceContext);
	ImGui::StyleColorsDark();

	return true;
}

void imguiManager::Shutdown()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void imguiManager::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void imguiManager::NewFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void imguiManager::WidgetSpeedSlider(float* speed)
{
	ImGui::SliderFloat("Speed", speed, 0.0f, 100.0f);
}

void imguiManager::WidgetButton()
{
	static int counter = 0;

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);
}

void imguiManager::WidgetFPS()
{
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
}

void imguiManager::WidgetAddObject(ApplicationClass* app)
{
	if (ImGui::CollapsingHeader("Objects"))
	{
		if (ImGui::Button("Add Cube"))
		{
			app->AddCube();
		}
		ImGui::SameLine();
		ImGui::Text("Number of cubes: %d", app->GetCubeCount());
	}
}

void imguiManager::WidgetObjectWindow(ApplicationClass* app)
{
	ImGui::Begin("Objects");
	int index = 0;
	for (auto object : app->GetCubes())
	{
		std::string headerName = "Object " + std::to_string(index);
		if (ImGui::CollapsingHeader(headerName.c_str()))
		{
			XMVECTOR position = object->GetPosition();
			XMVECTOR rotation = object->GetRotation();
			XMVECTOR scale = object->GetScale();
			ImGui::Text("Position: %.2f %.2f %.2f", XMVectorGetX(position), XMVectorGetY(position), XMVectorGetZ(position));
			ImGui::Text("Rotation: %.2f %.2f %.2f", XMVectorGetX(rotation), XMVectorGetY(rotation), XMVectorGetZ(rotation));
			ImGui::Text("Scale: %.2f %.2f %.2f", XMVectorGetX(scale), XMVectorGetY(scale), XMVectorGetZ(scale));
		}
		index++;
	}
	
	ImGui::End();
}