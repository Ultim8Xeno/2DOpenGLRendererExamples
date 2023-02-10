#pragma once
#include "Renderer.h"

using namespace OpenGLRenderer;

int FramebufferExample(void)
{
	const float accuracy = 30.0f;

	Window* window = new Window("Framebuffer", Vec2(690, 690));

	FrameBuffer* framebuffer = new FrameBuffer(window->GetWindowSize());

	float rot = 0.0f;

	while (!window->ShouldWindowClose())
	{
		Renderer::BeginDraw();

		framebuffer->Start();

		for (int i = 0; i < accuracy; i++)
		{
			for (int j = 0; j < accuracy; j++)
			{
				Renderer::DrawQuad(Vec3((i + 0.5f) * window->GetWindowSize().x / accuracy, (j + 0.5f) * window->GetWindowSize().y / accuracy, 0.0f),
					Vec2(window->GetWindowSize().x / accuracy, window->GetWindowSize().y / accuracy), Vec4(i * 0.7f / accuracy, j * 0.5f / accuracy + 0.2f, i * j / accuracy / accuracy * 0.8f + 0.2f, 1.0f));
			}
		}

		framebuffer->End();

		rot += Renderer::GetDT() * 60.0f;

		Renderer::DrawTexture(Vec3(window->GetWindowSize().x / 2, window->GetWindowSize().y / 2, 0.0f), Vec2(300, 300),
			framebuffer->GetTextureID(), window->GetWindowSize(), Vec4(1.0f, 1.0f, 1.0f, 1.0f), rot);

		Renderer::EndDraw();
	}

	delete window;
	delete framebuffer;

	return 0;
}