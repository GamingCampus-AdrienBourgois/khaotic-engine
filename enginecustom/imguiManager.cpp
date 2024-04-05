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

		if (ImGui::Button("Import Object"))
		{
			// Open file dialog
			OPENFILENAME ofn;
			WCHAR szFile[260];
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = L"OBJ\0*.obj\0TXT\0*.txt\0KOBJ\0*.kobj";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&ofn))
			{
				app->AddKobject(ofn.lpstrFile);
			}

		}
	}
}

void imguiManager::WidgetObjectWindow(ApplicationClass* app)
{
	ImGui::Begin("Objects");
	int index = 0;
	for (auto& object : app->GetKobjects())
	{
		std::string headerName = object->GetName() + " " + std::to_string(index);
		if (ImGui::CollapsingHeader(headerName.c_str()))
		{

			XMVECTOR position = object->GetPosition();
			XMVECTOR rotation = object->GetRotation();
			XMVECTOR scale = object->GetScale();

			float pos[3] = { XMVectorGetX(position), XMVectorGetY(position), XMVectorGetZ(position) };
			std::string posLabel = "Position##" + std::to_string(index);
			if (ImGui::DragFloat3(posLabel.c_str(), pos))
			{
				object->SetPosition(XMVectorSet(pos[0], pos[1], pos[2], 0.0f));
			}

			float rot[3] = { XMVectorGetX(rotation), XMVectorGetY(rotation), XMVectorGetZ(rotation) };
			std::string rotLabel = "Rotation##" + std::to_string(index);
			if (ImGui::DragFloat3(rotLabel.c_str(), rot))
			{
				object->SetRotation(XMVectorSet(rot[0], rot[1], rot[2], 0.0f));
			}

			float scl[3] = { XMVectorGetX(scale), XMVectorGetY(scale), XMVectorGetZ(scale) };
			std::string sclLabel = "Scale##" + std::to_string(index);
			if (ImGui::DragFloat3(sclLabel.c_str(), scl))
			{
				object->SetScale(XMVectorSet(scl[0], scl[1], scl[2], 0.0f));
			}

			ImGui::Separator();

			// Delete button
			std::string deleteLabel = "Delete##" + std::to_string(index);
			if (ImGui::Button(deleteLabel.c_str()))
			{
				app->DeleteKobject(index);
			}

			ImGui::Separator();

			// Demo spinning
			std::string demoLabel = "Demo spinning##" + std::to_string(index);
			ImGui::Checkbox(demoLabel.c_str(), &object->m_demoSpinning);
		}
		index++;
	}
	
	ImGui::End();
}

void imguiManager::WidgetTerrainWindow(ApplicationClass* app)
{
	ImGui::Begin("Terrain");

	ImGui::Text("Number of terrain cubes: %d", app->GetTerrainCubeCount());

	ImGui::Separator();

	if (ImGui::Button("Generate Terrain"))
	{
		app->GenerateTerrain();
	}

	ImGui::SameLine();

	if (ImGui::Button("Delete All Terrain Cubes"))
	{
		app->DeleteTerrain();
	}

	ImGui::End();
}

void imguiManager::ImGuiWidgetRenderer(ApplicationClass* app)
{
	// Start the Dear ImGui frame
	NewFrame();

	//ImGui Widget
	ImGui::Begin("Khaotic Engine", NULL);

	float speed = app->GetSpeed();
	WidgetSpeedSlider(&speed);
	app->SetSpeed(speed);
	WidgetButton();
	WidgetFPS();
	WidgetAddObject(app);
	WidgetObjectWindow(app);
	WidgetTerrainWindow(app);

	ImGui::End();

	//render imgui
	Render();

	app->GetDirect3D()->m_swapChain->Present(0, NULL);
}