#include "Renderer.h"
#include <iostream>
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

void Renderer::OnResize(uint32_t width, uint32_t height)
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
}

void Renderer::Render(const Scene& scene, Player& player)
{
	for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
	{
		float fov = player.m_Fov * (PI / 180);
		float rayAngle = (player.m_Angle - (fov / 2.0f)) + ((float)x / (float)m_FinalImage->GetWidth()) * fov;
		// rayAngle *= ((float)m_FinalImage->GetWidth() / m_FinalImage->GetHeight());
		float rayDist = 0.0f;
		float coinDist = 0.0f;

		glm::vec2 unitVector = { (float)sinf(rayAngle), (float)cosf(rayAngle) };

		bool hitWall = false;
		bool hitCoin = false;
		while (!hitWall && rayDist < player.m_MaxViewDist)
		{
			rayDist += 0.1f;
			// if (!hitCoin) coinDist += 0.1f;

			glm::vec2 test = {
				(int)(player.m_Position.x + unitVector.x * rayDist),
				(int)(player.m_Position.y + unitVector.y * rayDist)
			};

			// glm::vec2 testCoin = {
			// 	(int)(player.m_Position.x + unitVector.x * coinDist),
			// 	(int)(player.m_Position.y + unitVector.y * coinDist)
			// };

			// if ray out of bounds
			if (test.x < 0 || test.x >= scene.mapWidth || test.y < 0 || test.y >= scene.mapHeight)
			{
				hitWall = true;
				rayDist = player.m_MaxViewDist;
			}
			else
			{
				/*
				bool canSeeCoin = ((player.m_Angle - (fov / 8.0f)) <= rayAngle) && (rayAngle <= ((player.m_Angle - (fov / 4.0f)) + (fov / 4.0f)));

				if (scene.map[(int)(testCoin.x + scene.mapWidth * testCoin.y)] == 2 && canSeeCoin)
				{
					hitCoin = true;
				}
				*/
				
				if (scene.map[(int)(test.x + scene.mapWidth * test.y)] != 0)
				{
					if (scene.map[(int)(test.x + scene.mapWidth * test.y)] == 2)
						hitCoin = true;

					hitWall = true;
				}
			}
		}

		int ceiling = max((float)(m_FinalImage->GetHeight() / 2.0) - m_FinalImage->GetHeight() / ((float)rayDist), 0.0f);
		int floor = m_FinalImage->GetHeight() - ceiling;

		for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
		{
			if (y <= ceiling)
				m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(scene.skyColour);
			else if (y > ceiling && y <= floor)
			{
				m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(hitCoin ? scene.coinColour : scene.wallColour * (1.0f - (rayDist / player.m_MaxViewDist)));
			}
			else
			{
				float floorDist = (((float)y - m_FinalImage->GetHeight() / 2.0f) / ((float)m_FinalImage->GetHeight() / 2.0f));
				m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(scene.floorColour * floorDist);
			}
		}

		/*
			if (hitCoin)
			{
				int coinCeiling = max(((float)(m_FinalImage->GetHeight() / 2.0) - m_FinalImage->GetHeight() / ((float)coinDist)), 0.0f);
				int coinFloor = m_FinalImage->GetHeight() - coinCeiling;

				if (y > coinCeiling && y <= coinFloor)
				{
					glm::vec4 shade = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
					m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(shade);
				}
			}
			*/

		/*
		while (!hitCoin && coinDist < player.m_MaxViewDist)
		{
			coinDist += 0.1f;

			glm::vec2 test = {
				(int)(player.m_Position.x + unitVector.x * coinDist),
				(int)(player.m_Position.y + unitVector.y * coinDist)
			};

			// if ray out of bounds
			if (test.x < 0 || test.x >= scene.mapWidth || test.y < 0 || test.y >= scene.mapHeight)
			{
				hitCoin = true;
				rayDist = player.m_MaxViewDist;
			}
			else
			{
				bool canSeeCoin = (player.m_Angle - (fov / 4.0f)) <= rayAngle <= ((player.m_Angle - (fov / 4.0f)) + (fov / 2.0f));

				if (scene.map[(int)(test.x + scene.mapWidth * test.y)] == 2 && canSeeCoin)
				{
					hitCoin = true;
				}
			}
		}

		int coinCeiling = max(2 * ((float)(m_FinalImage->GetHeight() / 2.0) - m_FinalImage->GetHeight() / ((float)coinDist)), 0.0f);
		int coinFloor = m_FinalImage->GetHeight() - coinCeiling;

		for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
		{
			if (y > coinCeiling && y <= coinFloor)
			{
				glm::vec4 shade = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
				m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(shade);
			}
		}
		*/
	}

	m_FinalImage->SetData(m_ImageData);
}