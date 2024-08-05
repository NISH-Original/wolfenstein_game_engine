#include "Renderer.h"
#include <iostream>
#include <execution>
using namespace std;

#define PI 3.1415926f

namespace Utils
{
	static uint32_t ConvertToRGBA(const glm::vec4& color)
	{
		uint8_t r = (uint8_t)(color.r * 255.0f);
		uint8_t g = (uint8_t)(color.g * 255.0f);
		uint8_t b = (uint8_t)(color.b * 255.0f);
		uint8_t a = (uint8_t)(color.a * 255.0f);

		return (a << 24) | (b << 16) | (g << 8) | r;
	}
}

void Renderer::OnResize(uint32_t width, uint32_t height, uint32_t mapWidth, uint32_t mapHeight)
{
	if (m_FinalImage)
	{
		if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
			return;
		
		m_FinalImage->Resize(width, height);
	}	
	else
	{
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}

	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];

	m_ImageHorizontalIter.resize(width);
	m_ImageVerticalIter.resize(height);

	for (uint32_t i = 0; i < width; i++)
		m_ImageHorizontalIter[i] = i;
	for (uint32_t i = 0; i < height; i++)
		m_ImageVerticalIter[i] = i;

	if (m_FinalMapImage)
	{
		if (m_FinalMapImage->GetWidth() == mapWidth && m_FinalImage->GetHeight() == mapHeight)
			return;

		m_FinalMapImage->Resize(mapWidth, mapHeight);
	}
	else
	{
		m_FinalMapImage = std::make_shared<Walnut::Image>(mapWidth, mapHeight, Walnut::ImageFormat::RGBA);
	}

	delete[] m_MapImageData;
	m_MapImageData = new uint32_t[mapWidth * mapHeight];
}

void Renderer::Render(const Scene& scene, Player& player)
{
	// render the scene
	std::for_each(std::execution::par, m_ImageHorizontalIter.begin(), m_ImageHorizontalIter.end(),
		[this, player, scene](uint32_t x)
		{
			float fov = player.m_Fov * (PI / 180);
			float rayAngle = (player.m_Angle + (fov / 2.0f)) - ((float)x / (float)m_FinalImage->GetWidth()) * fov;
			float rayDist = 0.0f;

			glm::vec2 unitVector = { (float)sinf(rayAngle), (float)cosf(rayAngle) };

			bool hitWall = false;
			while (!hitWall && rayDist < player.m_MaxViewDist)
			{
				rayDist += 0.1f;

				// send a ray to wall from player
				glm::vec2 test = {
					(int)(player.m_Position.x + unitVector.x * rayDist),
					(int)(player.m_Position.y + unitVector.y * rayDist)
				};

				// if ray out of bounds
				if (test.x < 0 || test.x >= scene.mapWidth || test.y < 0 || test.y >= scene.mapHeight)
				{
					hitWall = true;
					rayDist = player.m_MaxViewDist;
				}
				else
				{
					if (scene.map[(int)(test.x + scene.mapWidth * test.y)] != 0)
					{
						hitWall = true;
					}
				}
			}

			// calculate the size of the vertical wall to render based on length of the raycast
			int ceiling = max((float)(m_FinalImage->GetHeight() / 2.0) - m_FinalImage->GetHeight() / ((float)rayDist), 0.0f);
			int floor = m_FinalImage->GetHeight() - ceiling;

			std::for_each(std::execution::par, m_ImageVerticalIter.begin(), m_ImageVerticalIter.end(),
				[this, ceiling, floor, scene, player, rayDist, x](uint32_t y)
				{
					if (y <= ceiling)
						m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(scene.skyColour);
					else if (y > ceiling && y <= floor)
					{
						m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(scene.wallColour * (1.0f - (rayDist / player.m_MaxViewDist)));
					}
					else
					{
						float floorDist = (((float)y - m_FinalImage->GetHeight() / 2.0f) / ((float)m_FinalImage->GetHeight() / 2.0f));
						m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(scene.floorColour * floorDist);
					}
				});
		});

	// populate buffer with pixel data
	m_FinalImage->SetData(m_ImageData);

	uint32_t blockWidth = m_FinalMapImage->GetWidth() / scene.mapWidth;
	uint32_t blockHeight = m_FinalMapImage->GetHeight() / scene.mapHeight;
	int sceneX = 0;
	int sceneY = 0;

#if 0	
	for (uint32_t x = 0; x < m_FinalMapImage->GetWidth(); x += blockWidth)
	{
		for (uint32_t y = 0; y < m_FinalMapImage->GetHeight(); y += blockHeight)
		{
			glm::vec4 shade = scene.map[sceneX + sceneY * scene.mapWidth] == 1 ? scene.wallColour : scene.floorColour;

			for (uint32_t i = x; i < x + blockWidth; i++)
			{
				for (uint32_t j = y; j < y + blockHeight; j++)
				{
					m_MapImageData[i + j * m_FinalMapImage->GetWidth()] = Utils::ConvertToRGBA(shade);
				}
			}

			sceneY++;
		}

		sceneX++;
	}
#else
	// render the minimap
	for (int x = 0; x < scene.mapWidth; x++)
	{
		for (int y = 0; y < scene.mapHeight; y++)
		{
			int offsetX = x * blockWidth;
			int offsetY = y * blockHeight;

			glm::vec4 shade = scene.map[x + y * scene.mapWidth] == 1 ? scene.wallColour : scene.floorColour;

			for (int i = offsetX; i < offsetX + blockWidth; i++)
			{
				for (int j = offsetY; j < offsetY + blockHeight; j++)
				{
					m_MapImageData[i + j * m_FinalMapImage->GetWidth()] = Utils::ConvertToRGBA(shade);
				}
			}
		}
	}
#endif

	// render player on minimap
	int playerX = player.m_Position.x;
	int playerY = player.m_Position.y;

	for (int x = playerX * blockWidth; x < playerX * blockWidth + blockWidth; x++)
	{
		for (int y = playerY * blockHeight; y < playerY * blockHeight + blockHeight; y++)
		{
			m_MapImageData[x + y * m_FinalMapImage->GetWidth()] = Utils::ConvertToRGBA(
				glm::vec4(
					1.0f - scene.floorColour.x,
					1.0f - scene.floorColour.y, 
					1.0f - scene.floorColour.z, 
					scene.floorColour.w
				));
		}
	}

	// populate buffer with pixel data
	m_FinalMapImage->SetData(m_MapImageData);
}

