#include "FramebufferExample.h"
#include "GradientExample.h"
#include "LineExample.h"
#include "TextExample.h"
#include "TextureExample.h"
#include "InputExample.h"
#include "CameraExample.h"

int main(void)
{
	GradientExample();
	LineExample();
	TextureExample();
	TextExample();
	FramebufferExample();
	InputExample();
	CameraExample();

	return 0;
}