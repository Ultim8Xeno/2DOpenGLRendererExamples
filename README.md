# About

This renderer written in C++ has capabilities to render basic 2d textures.

# Installation

```bash
git clone --recurse-submodules https://github.com/Ultim8Xeno/2DOpenGLRenderer
```

# Building

First, download premake5 at https://premake.github.io/download/. You can add it to your search path or put it in the directory of your project. Once installed, go to command line and type in premake5 followed by the project files you want to generate. Examples include vs2019, gmake, codelite, etc. The full list can be found here: https://premake.github.io/docs/Using-Premake \
To generate visual studio 2019 project files, you would type in

```bash
premake5 vs2019
```

# Using Your Own Project

Open premake5.lua in the main directory\
On the line where application is defined, change it to be the name of your application project
e.g:

```lua
application = "AmongUsGame"
```

Then create your own premake5.lua file in a folder titled whatever you put in the application variable. This folder should also contain all your code and whatnot. Write a premake5 file either using this documentation https://premake.github.io/docs/ or copy and pasting the premake5.lua file in Examples.

You can now build the project (above section)

# Usage

Start by including the correct file

```cpp
#include "Renderer.h"

// Makes it easier so you don't have to write it everytime
using namespace OpenGLRenderer;
```

## Creating a Window

```cpp
// windowName : std::string (name of window)
// width, height : float (size of window)
// windowFlags : uint8_t (windowFlags)
Window* window = new Window(windowName, Vec2(width, height), windowFlags);
```

Available window flags are `WINDOW_MAXIMIZED_HINT`, `WINDOW_RESIZE_HINT`, and `WINDOW_SCALE_TO_MONITOR_HINT`

```cpp
// Make sure to clean up when the program ends
delete window;
```

## Main Loop

```cpp
// If X button is clicked, window will close
while (!window->ShouldWindowClose())
{
    // Clear frame
    Renderer::BeginDraw();

    // Render objects and get Input (we'll get to this later)

    // Renders Buffer
    Renderer::EndDraw();
}
```

## Rendering

First there's a few things you should know:

- Position/dimension values are in pixels, where (0, 0) is the bottom left of the window
- Colour values are from 0 to 1
- Rotation values are in degrees
- Render things in order of lowest z position to highest if you're using transparent images

There are 4 type of objects you can render:

- Rectangles
- Lines
- Textures
- Text

### Rectangles

```cpp
// position : Vec3 (position of center of rectangle)
// dimensions : Vec2 (dimensions of rectangle in window)
// colour : Vec4 (colour of rectangle)
// rotation : float (rotation of rectangle, can be left blank with default value of 0)
Renderer::DrawQuad(position, dimensions, colour, rotation);
```

### Lines

```cpp
// startPosition : Vec2 (position of start of line)
// endPosition : Vec2 (position of end of line)
// colour : Vec4 (colour of line)
// width : float (width of line)
// zPosition : float (z position of line)
Renderer::DrawLine(startPosition, endPosition, colour, width, zPosition);
```

### Textures

This is a little trickier because you have to load in the the texture first

```cpp
// filepath : std::string (filepath of image file)
Texture* texture = new Texture(filepath);

while (...)
{
    ...
    // position : Vec3 (position of center of texture)
    // dimensions : Vec2 (dimensions of texture in window)
    // texture : Texture* (texture object created above)
    // colour : Vec4 (colour of texture tint, can be left blank with default value of white so texture stays the same)
    // rotation : float (rotation of texture, can be left blank with default value of 0)
    Renderer::DrawTexture(position, dimensions, texture, colour, rotation);
    ...
}

delete texture;
```

If you're using a spritesheet, you use this instead

```cpp
// position : Vec3 (position of center of sprite in window)
// dimensions : Vec2 (dimensions of sprite in window)
// spritesheet : Texture* (texture object created above)
// spritePosition : Vec2 (position of bottom left pixel of sprite in texture)
// spriteDimensions : Vec2 (dimensions of sprite in texture)
// colour : float (colour of sprite tint, can be left blank with default value of white so sprite stays the same)
// rotation : float (rotation of sprite, can be left blank with default value of 0)
DrawFromSpriteSheet(position, dimensions, spritesheet, spritePosition, spriteDimensions, colour, rotation);
```

### Text

```cpp
// text : std::string (text to render)
// position : Vec3 (position of center of text box)
// scale : float (scale of text box, can be left blank with a default value of 1)
// colour : Vec4 (colour of text, can be left blank with default value of white)
// rotation : float (rotation of text, can be left blank with default value of 0)
Renderer::Write(text, position, scale, colour, rotation);
```

This creates a text box with the default font. You can change the font by the following:

Start by downloading [hiero](https://libgdx.com/wiki/tools/hiero) and running it. Load the font file in and create a .fnt and .png file of the font.  
Then load it in with the filepath and write with it:

```cpp
// filepath : std::string (filepath of .fnt file)
TextObj* textObj = new TextObj(filepath);

while (...)
{
    ...
    // text : std::string (text to render)
    // position : Vec3 (position of center of text box)
    // scale : float (scale of text box, can be left blank with a default value of 1)
    // colour : Vec4 (colour of text, can be left blank with default value of white)
    // rotation : float (rotation of text, can be left blank with default value of 0)
    textObj->Write(text, position, scale, colour, rotation);
    ...
}

delete textObj;
```

## Other Rendering Options

### Frame Buffers

```cpp
FrameBuffer* framebuffer = new FrameBuffer(window->GetWindowSize());

while (!window->ShouldWindowClose())
{
    Rendere::BeginDraw();

    framebuffer->Start();

    // Render Objects

    framebuffer->End();

    // position : Vec3 (position of center of texture)
    // dimensions : Vec2 (dimensions of texture in window)
    // tint : Vec4 (colour of texture tint, can be left blank with default value of white so texture stays the same)
    // rotation : float (rotation of texture, can be left blank with default value of 0)
    Renderer::DrawTexture(position, dimensions, framebuffer->GetTextureID(), window->GetWindowSize(), tint, rotation);
}
```

### Clear colour

```cpp
// Can be used anywhere in the program
// colour : Vec4 (background colour)
Renderer::ClearColor(colour);
```

## Input

Enums defined in Renderer/src/InputKeys.h

### Keyboard Input

```cpp
// key : uint32_t (INPUT_KEY_...)
// action : uint8_t (INPUT_PRESS, INPUT_RELEASE, or INPUT_REPEAT)
if (Input::GetKeyState(key) == action)
{
    ...
}
```

### Mouse Input

```cpp
// button : uint32_t (INPUT_MOUSE_BUTTON_...)
// action : uint8_t (INPUT_PRESS, INPUT_RELEASE, or INPUT_REPEAT)
if (Input::GetMouseButtonState(button) == action)
{
    ...
}
```

#### Mouse position

```cpp
// Pixel value where (0, 0) is bottom left corner
Vec2 mousePos = Input::GetMousePos();
```
