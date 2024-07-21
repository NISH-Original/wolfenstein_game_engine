#pragma once

#include <cstdint>
#include <glm/glm.hpp>

/*
class Scene
{
private:
	static Scene* instancePtr;

	uint8_t mapWidth = 16;
	uint8_t mapHeight = 16;
	glm::vec4 wallColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 floorColour = glm::vec4(0.2f, 0.0f, 0.2f, 1.0f);
	glm::vec4 skyColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 coinColour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);

	uint8_t map[16 * 16] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1,
		1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	Scene() {};

public:
	Scene(const Scene& obj) = delete;

	static Scene* getInstance()
	{
		if (instancePtr == NULL)
		{
			instancePtr = new Scene();
			return instancePtr;
		}
		else
		{
			return instancePtr;
		}
	}

	void SetMapDimensions(uint8_t mapWidth, uint8_t mapHeight)
	{
		this->mapWidth = mapWidth;
		this->mapHeight = mapHeight;
	}

	void SetMap(uint8_t map[16 * 16])
	{
		for (uint32_t i = 0; i < this->mapWidth * this->mapHeight; i++)
			this->map[i] = map[i];
	}

	void SetWallColour(glm::vec4 wallColour)
	{
		this->wallColour = wallColour;
	}

	void SetFloorColour(glm::vec4 floorColour)
	{
		this->floorColour = floorColour;
	}

	void SetWallColour(glm::vec4 skyColour)
	{
		this->skyColour = skyColour;
	}

	void SetWallColour(glm::vec4 coinColour)
	{
		this->coinColour = coinColour;
	}

	uint8_t* GetMap()
	{
		return map;
	}

	uint8_t GetMapWidth()
	{
		return mapWidth;
	}

	uint8_t GetMapHeight()
	{
		return mapHeight;
	}

	glm::vec4 GetWallColour()
	{
		return wallColour;
	}

	glm::vec4 GetSkyColour()
	{
		return skyColour;
	}

	glm::vec4 GetFloorColour()
	{
		return floorColour;
	}

	glm::vec4 GetCoinColour()
	{
		return coinColour;
	}
};
*/


struct Scene
{
	uint8_t mapWidth = 16;
	uint8_t mapHeight = 16;
	glm::vec4 wallColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 floorColour = glm::vec4(0.2f, 0.0f, 0.2f, 1.0f);
	glm::vec4 skyColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 coinColour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);

	uint8_t map[16 * 16] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1,
		1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
};