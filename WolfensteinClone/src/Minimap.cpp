#include "Minimap.h"
#include <iostream>

using namespace std;

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

void Minimap::OnResize(uint32_t width, uint32_t height)
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
	cout << width << " : " << height << endl;
}

void Minimap::Render()
{
	cout << m_FinalImage->GetWidth() << " : " << m_FinalImage->GetHeight() << endl;
	cout << m_FinalImage->GetWidth() * m_FinalImage->GetHeight() << endl;
	
	for (uint32_t i = 0; i < m_FinalImage->GetWidth() * m_FinalImage->GetHeight(); i++)
	{
		m_ImageData[i] = 0xffffffff;
		cout << i << endl;
	}
	
	/*
	int blockWidth = m_FinalImage->GetWidth() / scene.mapWidth;
	int blockHeight = m_FinalImage->GetHeight() / scene.mapHeight;
	
	for (int x = 0; x < scene.mapWidth; x++)
	{
		for (int y = 0; y < scene.mapHeight; y++)
		{
			int offsetX = x * blockWidth;
			int offsetY = y * blockHeight;

			glm::vec4 shade = scene.map[x + y * scene.mapWidth] == 1 ? glm::vec4(1, 1, 0, 1) : glm::vec4(0, 0, 0, 1);

			for (int i = offsetX; i < offsetX + blockWidth; i++)
			{
				for (int j = offsetY; j < offsetY + blockHeight; j++)
				{
					m_ImageData[i + j * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(shade);
				}
			}
		}
	}
	*/

	m_FinalImage->SetData(m_ImageData);
}
