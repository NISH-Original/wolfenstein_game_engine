#include "Minigame.h"
#include <vector>
#include <ctime>

void Minigame::PlaceCoin()
{
	std::vector<int> zeroIndices;

	for (uint32_t i = 0; i < m_Scene.mapHeight * m_Scene.mapWidth; i++)
	{
		if (m_Scene.map[i] == 0)
			zeroIndices.push_back(i);
	}

	if (zeroIndices.empty())
		return;

	std::srand(std::time(0));

	int randomIndex = zeroIndices[std::rand() % zeroIndices.size()];

	m_Scene.map[randomIndex] = 2;
}
