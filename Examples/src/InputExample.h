#pragma once
#include "Renderer.h"

using namespace OpenGLRenderer;

int InputExample(void)
{
	Window* window = new Window("Input", Vec2(690, 690), WINDOW_MAXIMIZED_HINT);

	float rot = 0.0f;

	while (!window->ShouldWindowClose())
	{
		Renderer::BeginDraw();

		Vec2 mousePos = Input::GetMousePos();

		Renderer::DrawQuad(Vec3(mousePos.x, mousePos.y, 5.0f), Vec2(30, 30), Vec4(1.0f, 1.0f, 1.0f, 1.0f), rot);

		if (Input::GetMouseButtonState(INPUT_MOUSE_BUTTON_LEFT)) // == INPUT_PRESS OR INPUT_REPEAT
		{
			rot += Renderer::GetDT() * 60.0f;
		}

		Renderer::EndDraw();
	}

	delete window;

	return 0;
}