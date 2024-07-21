#pragma once
#include "Scene.h"

class Minigame
{
public:
	Minigame() = default;
	
	bool m_isEnabled;
	void PlaceCoin();
private:
	Scene m_Scene;
};