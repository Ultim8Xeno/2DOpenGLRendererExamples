#include "FramebufferExample.h"
#include "GradientExample.h"
#include "TextExample.h"
#include "TextureExample.h"
#include "InputExample.h"

int main(void)
{
	GradientExample();
	TextureExample();
	TextExample();
	FramebufferExample();
	InputExample();

	return 0;
}