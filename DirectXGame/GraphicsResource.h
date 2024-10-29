#pragma once
#include <d3d11.h>

#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsResource
{
public:
	GraphicsResource(RenderSystem* system) : renderSystem(system) {}

	// // Rule of Five (because ReSharper won't stop bitching about it)
	// virtual ~GraphicsResource() = 0; // did not know that this was possible
	// GraphicsResource(const GraphicsResource& obj) = default;
	// GraphicsResource(GraphicsResource&& other) noexcept = default;
	// GraphicsResource& operator=(const GraphicsResource& other) = default;
	// GraphicsResource& operator=(GraphicsResource&& other) noexcept = default;

protected:
	RenderSystem* renderSystem = nullptr;		
};
