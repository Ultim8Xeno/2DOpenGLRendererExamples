#pragma once
#include "Renderer.h"

using namespace OpenGLRenderer;

int TextureExample(void)
{
	const float accuracy = 100.0f;

	Window* window = new Window("Texture", Vec2(690, 690));

	Texture* texture = new Texture("Res/Textures/Among_Us.png");

	while (!window->ShouldWindowClose())
	{
		Renderer::BeginDraw();

		for (int i = 0; i < accuracy; i++)
		{
			for (int j = 0; j < accuracy; j++)
			{
				Renderer::DrawFromSpriteSheet(Vec3((i + 0.5f) * window->GetWindowSize().x / accuracy, (j + 0.5f) * window->GetWindowSize().y / accuracy, 0.0f),
					Vec2(window->GetWindowSize().x / accuracy, window->GetWindowSize().y / accuracy), texture, Vec2(i*texture->GetSize().x/accuracy, j*texture->GetSize().y/accuracy)
					, Vec2(texture->GetSize().x/accuracy, texture->GetSize().y / accuracy), Vec4(i/accuracy, j/accuracy, 1.0f, 1.0f));
			}
		}

		Renderer::DrawTexture(Vec3(window->GetWindowSize().x / 2, window->GetWindowSize().y / 2, 1.0f), Vec2(200, 200), texture);

		Renderer::EndDraw();
	}

	delete window;
	delete texture;

	return 0;
}