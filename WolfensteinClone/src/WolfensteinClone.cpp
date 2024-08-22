#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include <Walnut/Timer.h>
#include "Renderer.h"
#include "glm/gtc/type_ptr.hpp"

using namespace Walnut;

namespace Utils
{
	int roundToTen(float num)
	{
		int a = (num / 10) * 10;
		int b = a + 10;
		return (num - a >= b - num) ? b : a;
	}
}

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUpdate(float ts) override
	{
		m_Player.OnUpdate(ts);
	}
	
	virtual void OnUIRender() override
	{
		// HUD elements
		ImGui::Begin("Settings");
		if (ImGui::Button("START")) m_CanRender = true;

		ImGui::Separator();

		ImGui::Text("FPS: %.3i", Utils::roundToTen(1000.0f / m_LastRenderTime));

		ImGui::Separator();

		ImGui::ColorEdit3("Sky Colour", glm::value_ptr(m_Scene.skyColour));
		ImGui::ColorEdit3("Wall Colour", glm::value_ptr(m_Scene.wallColour));
		ImGui::ColorEdit3("Floor Colour", glm::value_ptr(m_Scene.floorColour));

		ImGui::Separator();

		ImGui::DragFloat("Walk Speed", &m_Player.m_WalkSpeed, 0.1f, 0.1f, 10.0f);
		ImGui::DragFloat("Turn Speed", &m_Player.m_TurnSpeed, 0.1f, 0.1f, 5.0f);
		ImGui::DragInt("FOV", &m_Player.m_Fov, 1.0f, 30, 120);

		ImGui::Separator();

		ImGui::Text("Controls:");
		ImGui::Text("Movement - W A S D");
		ImGui::Text("Look around - Left and right arrow keys");

		ImGui::End();

		// minimap
		ImGui::Begin("Minimap");
		
		m_MapWidth = ImGui::GetContentRegionAvail().x;
		m_MapHeight = ImGui::GetContentRegionAvail().y;

		auto mapImage = m_Renderer.GetFinalMapImage();
		if (mapImage) ImGui::Image(mapImage->GetDescriptorSet(), { (float)mapImage->GetWidth(), (float)mapImage->GetHeight() });

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Scene");
		 
		m_SceneWidth = ImGui::GetContentRegionAvail().x;
		m_SceneHeight = ImGui::GetContentRegionAvail().y;

		auto image = m_Renderer.GetFinalImage();
		if (image) ImGui::Image(image->GetDescriptorSet(), { (float)image->GetWidth(), (float)image->GetHeight() });

		ImGui::End();
		ImGui::PopStyleVar();

		if (m_CanRender)
			StartGame();
	}

	void StartGame()
	{
		Timer timer;

		m_Renderer.OnResize(m_SceneWidth, m_SceneHeight, m_MapWidth, m_MapHeight);
		m_Player.OnResize(m_SceneWidth, m_SceneHeight);
		m_Renderer.Render(m_Scene, m_Player);

		m_LastRenderTime = timer.ElapsedMillis();
	}
private:
	std::shared_ptr<Image> m_Image;
	uint32_t m_SceneWidth = 0, m_SceneHeight = 0;
	uint32_t m_MapWidth = 0, m_MapHeight = 0;
	Renderer m_Renderer;
	float m_LastRenderTime = 0;
	Scene m_Scene;
	Player m_Player;
	bool m_CanRender = false;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Wolfenstein Clone";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}