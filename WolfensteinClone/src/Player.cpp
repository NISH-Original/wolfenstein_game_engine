#include "Player.h"
#include "Walnut/Input/Input.h"
using namespace std;

using namespace Walnut;

void Player::OnUpdate(float ts)
{
	if (Input::IsKeyDown(KeyCode::W))
	{
		glm::vec2 forwardDir = { sinf(m_Angle), cosf(m_Angle) };
		m_Position += forwardDir * m_WalkSpeed * ts;

		if (m_Scene.map[(int)m_Position.y * m_Scene.mapWidth + (int)m_Position.x] == 1)
		{
			m_Position -= forwardDir * m_WalkSpeed * ts;
		}

		if (m_Scene.map[(int)m_Position.y * m_Scene.mapWidth + (int)m_Position.x] == 2)
		{
			m_Scene.map[(int)m_Position.y * m_Scene.mapWidth + (int)m_Position.x] == 0;
			m_Minigame.PlaceCoin();
		}
	}
	else if (Input::IsKeyDown(KeyCode::S))
	{
		glm::vec2 forwardDir = { sinf(m_Angle), cosf(m_Angle) };
		m_Position -= forwardDir * m_WalkSpeed * ts;

		if (m_Scene.map[(int)m_Position.y * m_Scene.mapWidth + (int)m_Position.x] == 1)
		{
			m_Position += forwardDir * m_WalkSpeed * ts;
		}
	}
	else if (Input::IsKeyDown(KeyCode::D))
	{
		m_Angle += m_TurnSpeed * ts;
	}
	else if (Input::IsKeyDown(KeyCode::A))
	{
		m_Angle -= m_TurnSpeed * ts;
	}
}

void Player::OnResize(uint32_t width, uint32_t height)
{
	if (width == m_SceneWidth && height == m_SceneHeight)
		return;

	m_SceneWidth = width;
	m_SceneHeight = height;
}
