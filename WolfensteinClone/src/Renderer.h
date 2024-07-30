#pragma once

#include "Walnut/Image.h"

#include <memory>
#include <glm/glm.hpp>
#include "Scene.h"
#include "Player.h"

class Renderer
{
public:
	Renderer() = default;
	
	void Render(const Scene& scene, Player& player);

	void OnResize(uint32_t width, uint32_t height, uint32_t mapWidth, uint32_t mapHeight);

	std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; };
	std::shared_ptr<Walnut::Image> GetFinalMapImage() const { return m_FinalMapImage; };
private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	std::shared_ptr<Walnut::Image> m_FinalMapImage;
	uint32_t* m_ImageData = nullptr;
	uint32_t* m_MapImageData = nullptr;
};