#include "FramebufferExample.h"
#include "GradientExample.h"
#include "LineExample.h"
#include "TextExample.h"
#include "TextureExample.h"
#include "InputExample.h"

int main(void)
{
	GradientExample();
	LineExample();
	TextureExample();
	TextExample();
	FramebufferExample();
	InputExample();

	return 0;
}