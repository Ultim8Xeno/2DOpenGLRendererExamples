#include "Renderer.h"

using namespace OpenGLRenderer;

int main(void)
{
	const float accuracy = 40.0f;

	Window* window = new Window("Gradient", Vec2(690, 690));

	while (!window->ShouldWindowClose())
	{
		Renderer::BeginDraw();

		for (int i = 0; i < accuracy; i++)
		{
			for (int j = 0; j < accuracy; j++)
			{
				Renderer::DrawQuad(Vec3((i+0.5f) * window->GetWindowSize().x / accuracy, (j+0.5f) * window->GetWindowSize().y / accuracy, 0.0f),
					Vec2(window->GetWindowSize().x / accuracy, window->GetWindowSize().y / accuracy), Vec4(i*0.7f/accuracy, j*0.5f/accuracy + 0.2f, i*j/accuracy/accuracy*0.8f + 0.2f, 1.0f));
			}
		}

		Renderer::EndDraw();
	}

	return 0;
}