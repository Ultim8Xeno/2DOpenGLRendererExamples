#include "Renderer.h"
#include <iostream>

using namespace OpenGLRenderer;

int main(void)
{
    Window* window = new Window("Program", Vec2(768, 768));

    float t = 1.5f;
    const int rects = 1000;
    Vec3* pos = new Vec3[rects];
    Vec2* dim = new Vec2[rects];
    Vec4* col = new Vec4[rects];
    float* rot = new float[rects];
    
    std::vector<std::vector<float>> lineStarts;
    std::vector<std::vector<float>> lineEnds;
    std::vector<std::vector<float>> lineCols;
    std::vector<float> lineWidths;
    std::vector<float> lineZIndex;
    Vec2 lastMousePosPress = Vec2{ -1.0f, -1.0f };
    float textRot = 0.0f;

    Vec3 smileyPositions[4] = {
            Vec3(300, 300, 1000),
            Vec3(500, 300, 1000),
            Vec3(300, 500, 1000),
            Vec3(500, 500, 1000)
    };

    float smileyRot = 0.0f;

    /* Loop until the user closes the window */

    Texture* tex = new Texture("src/Res/Textures/Smiley.png");

    while (!window->ShouldWindowClose())
    {
        Renderer::BeginDraw();

        if (Input::GetMouseButtonState(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
        {
            if (lastMousePosPress.x >= 0 && lastMousePosPress.y >= 0)
            {
                lineStarts.push_back({ lastMousePosPress.x, lastMousePosPress.y });
                lineEnds.push_back({ Input::GetMousePos().x, Input::GetMousePos().y });
                lineCols.push_back({ (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f });
                lineWidths.push_back(rand() % 20);
                lineZIndex.push_back(rand()%1000);
                lastMousePosPress = { -1.0f, -1.0f };
            }
            else
            {
                Vec2 pos = { Input::GetMousePos().x, Input::GetMousePos().y };
                lastMousePosPress = pos;
            }
        }
        
        for (int i = 0; i < lineStarts.size(); i++)
        {
            Renderer::DrawLine(Vec2(lineStarts[i][0], lineStarts[i][1]), Vec2(lineEnds[i][0], lineEnds[i][1]), Vec4(lineCols[i][0], lineCols[i][1], lineCols[i][2], lineCols[i][3]), lineWidths[i], lineZIndex[i]);
        }
        
        if (t >= 1.5f)
        {
            for (int i = 0; i < rects; i++)
            {
                pos[i] = Vec3(rand() % (int)window->GetWindowSize().x, rand() % (int)window->GetWindowSize().y, rand() % 1000);
                dim[i] = Vec2(rand() % 300, rand() % 250);
                col[i] = Vec4((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
                rot[i] = rand() % 360;
            }
            Renderer::ClearColour(Vec4((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f));
            t -= 1.5f;
        }
        
        for (int i = 0; i < rects; i++)
        {
            rot[i]+=Renderer::GetDT()*50.0f;
            Renderer::DrawQuad(pos[i], dim[i], col[i], rot[i]);
        }
        
        t += Renderer::GetDT();

        const int signs[8] = { -1, -1, 1, -1, -1, 1, 1, 1 };

        for (int i = 0; i < 4; i++)
        {
            smileyPositions[i].RotateAroundCenter(Renderer::GetDT() * 60.0f, Vec2(400, 400));
            Renderer::DrawFromSpriteSheet(smileyPositions[i], Vec2(150, 150), tex,
                Vec2(tex->GetSize().x / 2 * ((signs[i * 2] + 1) / 2), tex->GetSize().y / 2 * ((signs[i * 2 + 1] + 1) / 2)),
                Vec2(tex->GetSize().x / 2, tex->GetSize().y / 2), Vec4(1.0f, 1.0f, 1.0f, 1.0f), smileyRot);
        }

        smileyRot += Renderer::GetDT() * 60.0f;

        Renderer::Write("Super idol de xiao rong\nDou mei ni de tian\nBa yue zheng wu de yang guang\nDou mei ni yao yan\n\
Re ai yi bai ling wu du de ni\nDi di qing chun de zheng liu shui", Vec3(300, 500, 2000), 0.25f,
                        Vec4(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f, 1.0f), textRot);

        textRot += Renderer::GetDT() * 30.0f;

        Renderer::Write("FPS: " + std::to_string(1/Renderer::GetDT()), Vec3(1000, 600, 5000), 0.25f);

        Renderer::EndDraw();
    }

    delete[] pos;
    delete[] dim;
    delete[] col;
    delete[] rot;
    delete tex;
    delete window;

    return 0;
}