#include "imguiManager.h"
#include "applicationclass.h"

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
