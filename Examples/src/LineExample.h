#pragma once
#pragma once
#include "Renderer.h"

using namespace OpenGLRenderer;

int LineExample(void)
{
	const float accuracy = 30.0f;

	Window* window = new Window("Line", Vec2(690, 690));

	while (!window->ShouldWindowClose())
	{
		Renderer::BeginDraw();
		
		Renderer::DrawLine(Vec2(0, 0), window->GetWindowSize(), Vec4(1.0f, 1.0f, 1.0f, 1.0f), 10.0f);
		Renderer::DrawLine(Vec2(window->GetWindowSize().x / 2, window->GetWindowSize().y / 2 - 100),
			Vec2(window->GetWindowSize().x / 2, window->GetWindowSize().y / 2 + 100), Vec4(1.0f, 1.0f, 1.0f, 1.0f), 10.0f);
		
		Renderer::EndDraw();
	}

	delete window;

	return 0;
}