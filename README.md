# About

This renderer written in C++ has capabilities to render quads, lines, textures, and text (coloured or rotated).

# Installation

```bash
git clone https://github.com/Ultim8Xeno/2DOpenGLRenderer
```

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

- Position/dimension values is in pixels, where (0, 0) is the bottom left of the window
- Colour value is from 0 to 1
- Rotation values are in degrees
- Render things in order of lowest z position to highest if you're using transparent images

There are 3 type of objects you can render:

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
// rot : float (rotation of sprite, can be left blank with default value of 0)
DrawFromSpriteSheet(position, dimensions, spritesheet, spritePosition, spriteDimensions, colour, rotation);
```

### Text

```cpp
// text : std::string (text to render)
// position : Vec3 (position of center of text box)
// scale : float (scale of text box, can be left blank with a default value of 1)
// colour : Vec4 (colour of text, can be left blank with default value of white)
// rot : float (rotation of text, can be left blank with default value of 0) *** ROTATION NOT IMPLEMENTED YET***
Renderer::Write(text, position, scale, colour, rotation);
```

This creates a text box with the default font. You can change the font by the following:

Start by downloading [hiero](https://libgdx.com/wiki/tools/hiero) and running it. Load the font file in and create a .fnt and .png file of the font.  
Then load it in and render it:

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
    // rot : float (rotation of text, can be left blank with default value of 0) *** ROTATION NOT IMPLEMENTED YET***
    textObj->Write(text, position, scale, colour, rotation);
    ...
}

delete textObj;
```

## Other Rendering Options

### Clear colour

```cpp
// Can be used anywhere in the program
// colour : Vec4 (background colour)
Renderer::ClearColor(colour);
```

## Input

### Keyboard Input

[Reference to keyboard enums](https://www.glfw.org/docs/3.3/group__keys.html)

```cpp
// key : uint32_t (GLFW_KEY_...)
// action : uint8_t (GLFW_PRESS, GLFW_RELEASE or, GLFW_REPEAT)
if (Input::GetKeyState(key) == action)
{
    ...
}
```

### Mouse Input

[Reference to mouse enums](https://www.glfw.org/docs/3.3/group__buttons.html)

```cpp
// button : uint32_t (GLFW_MOUSE_BUTTON_...)
// action : uint8_t (GLFW_PRESS, GLFW_RELEASE or, GLFW_REPEAT)
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
