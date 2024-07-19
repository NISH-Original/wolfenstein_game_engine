#include "Renderer.h"

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

void Renderer::Render(const Scene& scene, const Player& player)
{
	for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
	{
		float rayAngle = (player.m_Angle - (player.m_Fov / 2.0f)) + ((float)x / (float)m_FinalImage->GetWidth()) * player.m_Fov;
		float rayDist = 0.0f;

		glm::vec2 unitVector = { (float)sinf(rayAngle), (float)cosf(rayAngle) };

		bool hitWall = false;
		while (!hitWall && rayDist < player.m_MaxViewDist)
		{
			rayDist += 0.1f;

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
				if (scene.map[(int)(test.x + scene.mapWidth * test.y)] == 1)
				{
					hitWall = true;
				}
			}
		}

		int ceiling = (float)(m_FinalImage->GetHeight() / 2.0) - m_FinalImage->GetHeight() / ((float)rayDist);
		int floor = m_FinalImage->GetHeight() - ceiling;

		// glm::vec4 shade = glm::vec4(1, 0, 1, 1);
		// make block darker the farther from player
		// if (rayDist <= player.m_MaxViewDist / 4.0f)     shade *= 1; // close
		// else if (rayDist < player.m_MaxViewDist / 3.0f) shade *= 0.75;
		// else if (rayDist < player.m_MaxViewDist / 2.0f) shade *= 0.5;
		// else if (rayDist < player.m_MaxViewDist)        shade *= 0.25;
		// else                                            shade *= 0; // far

		for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
		{
			if (y <= ceiling)
				m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(glm::vec4(0, 0, 0, 1));
			else if (y > ceiling && y <= floor)
			{
				glm::vec4 shade = glm::vec4(1, 0, 1, 1);
				m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(shade * (1.0f - (rayDist / player.m_MaxViewDist)));
			}
			else
			{
				float floorDist = 1.0f - (((float)y - m_FinalImage->GetHeight() / 2.0f) / ((float)m_FinalImage->GetHeight() / 2.0f));
				glm::vec4 fshade = glm::vec4(0, 0, 0.5, 1);
				// if (floorDist < 0.25)      fshade *= 1; // close
				// else if (floorDist < 0.5)  fshade *= 0.75;
				// else if (floorDist < 0.75) fshade *= 0.5;
				// else if (floorDist < 0.9)  fshade *= 0.25;
				// else                       fshade *= 0;    // far
				m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(fshade * (1.0f - floorDist));
			}
		}
	}

	m_FinalImage->SetData(m_ImageData);
}