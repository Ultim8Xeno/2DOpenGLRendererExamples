#include "Renderer.h"

using namespace OpenGLRenderer;

int TextExample(void)
{
	Window* window = new Window("Text", Vec2(690, 690));

	TextObj* text = new TextObj("Res/Fonts/Inconsolata-Regular.fnt");

	while (!window->ShouldWindowClose())
	{
		Renderer::BeginDraw();

		text->Write("I'm the biggest bird", Vec3(window->GetWindowSize().x/2, window->GetWindowSize().y/2, 2.0f), 1.2f);
		float yOffset = text->GetTextBoxDimensions("I'm the biggest bird", 1.2f).y / 2 + text->GetTextBoxDimensions("I'm the biggest bird", 0.6f).y / 2;

		text->Write("I'm the biggest bird", Vec3(window->GetWindowSize().x / 2, window->GetWindowSize().y / 2 - yOffset, 1.0f), 0.6f);

		Renderer::EndDraw();
	}

	delete window;
	delete text;

	return 0;
}