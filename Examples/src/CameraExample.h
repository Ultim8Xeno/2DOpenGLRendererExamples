#pragma once
#include "Renderer.h"

using namespace OpenGLRenderer;

int CameraExample(void)
{
	Window* window = new Window("Camera", Vec2(690, 690), WINDOW_MAXIMIZED_HINT);

	Vec2 offset = Vec2(0.0f, 0.0f);
	Vec2 lastMousePos = Vec2(0.0f, 0.0f);
	Vec2 scale = Vec2(1.0f, 1.0f);

	while (!window->ShouldWindowClose())
	{
		Renderer::BeginDraw();

		if (Input::GetMouseButtonState(INPUT_MOUSE_BUTTON_LEFT) == INPUT_PRESS)
			lastMousePos = Input::GetMousePos();

		if (Input::GetMouseButtonState(INPUT_MOUSE_BUTTON_LEFT) == INPUT_REPEAT)
		{
			offset.x += Input::GetMousePos().x - lastMousePos.x;
			offset.y += Input::GetMousePos().y - lastMousePos.y;
			lastMousePos = Input::GetMousePos();
		}

		if (Input::GetMouseScroll() > 0)
		{
			scale.x *= 1.01f;
			scale.y *= 1.01f;
		}
		else if (Input::GetMouseScroll() < 0)
		{
			scale.x *= 0.99f;
			scale.y *= 0.99f;
		}

		Renderer::SetOffset(offset);
		Renderer::SetScale(scale);

		Renderer::DrawQuad(Vec3(), Vec2(100, 100), Vec4(0.8f, 0.3f, 0.2f, 1.0f));

		Renderer::DrawQuad(Vec3(600, 600, 0.0f), Vec2(100, 100), Vec4(0.2f, 0.3f, 0.8f, 1.0f));

		Renderer::EndDraw();
	}

	delete window;

	return 0;
}