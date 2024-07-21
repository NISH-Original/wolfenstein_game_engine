#pragma once

#include <glm/glm.hpp>
#include "Scene.h"
#include "Minigame.h"

class Player
{
public:
	void OnUpdate(float ts);
	void OnResize(uint32_t width, uint32_t height);

	float m_MaxViewDist = 16.0f;
	float m_Angle = 0.0f;
	int m_Fov = 45;
	glm::vec2 m_Position = { 8, 8 };
	bool m_HitWall = false;
	float m_WalkSpeed = 4.0f;
	float m_TurnSpeed = 2.0f;
private:
	uint32_t m_SceneWidth = 0, m_SceneHeight = 0;
	Scene m_Scene;
	Minigame m_Minigame;
};
