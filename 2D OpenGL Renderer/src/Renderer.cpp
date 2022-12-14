#include "Renderer.h"
#include "Buffers.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include <cmath>
#include <iostream>
#include "Debug.h"
#include "Input.h"
#include "Text.h"

namespace OpenGLRenderer {

	struct RendererData
	{
		const uint32_t MAX_QUADS = 250;
		const uint32_t MAX_INDICES = MAX_QUADS * 6;
		const uint32_t MAX_VERTICES = MAX_QUADS * 4;
		const uint32_t MAX_TEXTURES = 16;

		uint32_t currentQuad = 0;
		uint32_t currentTex = 0;
		GLFWwindow* window = nullptr;
		VertexBuffer* vb = nullptr;
		IndexBuffer* ib = nullptr;
		VertexArray* va = nullptr;
		Shader* shader = nullptr;
		struct VertexData
		{
			float pos[3] = { 0.0f, 0.0f, 0.0f };
			float col[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			float texCoords[2] = { 0.0f, 0.0f };
			int texID = 0;
		};
		VertexData* vertexData = nullptr;
		uint32_t* indexData = nullptr;

		uint32_t* textures = nullptr;
		Texture* whiteTex = nullptr;

		TextObj* textObj = nullptr;

		float dt = 0.0f;
		float lastFrameTime = 0.0f;
	};

	static RendererData data;

	void Renderer::Setup(GLFWwindow* window)
	{
		data.currentQuad = 0;
		data.currentTex = 0;
		data.window = window;
		data.vertexData = new RendererData::VertexData[data.MAX_VERTICES]();
		memset(data.vertexData, 0, data.MAX_VERTICES * sizeof(RendererData::VertexData));
		data.indexData = new uint32_t[data.MAX_INDICES];
		data.shader = new Shader("src/Res/Shaders/vertex.shader", "src/Res/Shaders/fragment.shader");
		data.va = new VertexArray();

		data.textObj = new TextObj("src/Res/Fonts/RobotoCondensed-Regular.fnt");
		
		data.textures = new uint32_t[data.MAX_TEXTURES];
		memset(data.textures, 0, data.MAX_TEXTURES * sizeof(uint32_t));

		uint32_t whiteTexData = 0xffffffff;
		data.whiteTex = new Texture(&whiteTexData, 1, 1);

		// indexData = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, ... }
		for (int i = 0; i < data.MAX_QUADS; i++)
		{
			data.indexData[i * 6 + 0] = i * 4;
			data.indexData[i * 6 + 1] = i * 4 + 1;
			data.indexData[i * 6 + 2] = i * 4 + 2;
			data.indexData[i * 6 + 3] = i * 4 + 2;
			data.indexData[i * 6 + 4] = i * 4 + 3;
			data.indexData[i * 6 + 5] = i * 4;
		}

		data.ib = new IndexBuffer(data.indexData, sizeof(uint32_t) * data.MAX_INDICES);

		data.vb = new VertexBuffer(data.vertexData, sizeof(RendererData::VertexData)*data.MAX_VERTICES);

		data.va->SetAttributes({ VertexAttribute(GL_FLOAT, 3), VertexAttribute(GL_FLOAT, 4), VertexAttribute(GL_FLOAT, 2), VertexAttribute(GL_INT, 1) });

		int* samplers = new int[data.MAX_TEXTURES];
		for (int i = 0; i < data.MAX_TEXTURES; i++)
			samplers[i] = i;

		data.shader->SetUniform(samplers, "u_Textures", GL_INT, data.MAX_TEXTURES);
		
		delete[] samplers;

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		data.lastFrameTime = glfwGetTime();
	}
	
	void Renderer::Shutdown()
	{
		delete data.va;
		delete data.ib;
		delete data.vb;
		delete data.shader;
		delete data.whiteTex;
		delete data.textObj;
		delete[] data.indexData;
		delete[] data.vertexData;
		delete[] data.textures;
	}

	void Renderer::ClearColor(const Vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void Renderer::BeginDraw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		data.dt = glfwGetTime() - data.lastFrameTime;
		data.lastFrameTime = glfwGetTime();
	}

	void Renderer::Flush()
	{
		for (int i = 0; i < data.currentTex; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, data.textures[i]);
		}

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(RendererData::VertexData) * 4 * data.currentQuad, data.vertexData);
		glDrawElements(GL_TRIANGLES, data.currentQuad * 6, GL_UNSIGNED_INT, 0);
		data.currentQuad = 0;
		data.currentTex = 0;
	}

	void Renderer::SetBounds(const Vec2& bounds)
	{
		float dims[2] = { bounds.x, bounds.y };
		data.shader->SetUniform(dims, "u_MonitorBounds", GL_FLOAT_VEC2, 1);
	}

	float Renderer::GetDT()
	{
		return data.dt;
	}

	void Renderer::EndDraw()
	{
		Flush();
		glfwSwapBuffers(data.window);
		glfwPollEvents();
		Input::Update();
	}

	void Renderer::DrawQuad(const Vec3& pos, const Vec2& dim, const Vec4& col, float rot)
	{
		DrawTexture(pos, dim, data.whiteTex, col, rot);
	}

	void Renderer::DrawTexture(const Vec3& pos, const Vec2& dim, Texture* tex, const Vec4& col, float rot)
	{
		DrawFromSpriteSheet(pos, dim, tex, Vec2(0.0f, 0.0f), Vec2(tex->GetSize().x, tex->GetSize().y), col, rot);
	}

	void Renderer::DrawFromSpriteSheet(const Vec3& pos, const Vec2& dim, Texture* tex, const Vec2& startingTexPos, const Vec2& spriteSize, const Vec4& col, float rot)
	{
		DrawFromSpriteSheet(pos, dim, tex->GetID(), tex->GetSize(), startingTexPos, spriteSize, col, rot);
	}

	void Renderer::DrawFromSpriteSheet(const Vec3& pos, const Vec2& dim, uint32_t tex, const Vec2& texSize, const Vec2& startingTexPos, const Vec2& spriteSize, const Vec4& col, float rot)
	{
		int texID = 0;
		for (int i = 0; i < data.currentTex; i++)
		{
			if (tex == data.textures[i])
				texID = i;
		}
		if (!texID)
		{
			data.textures[data.currentTex] = tex;
			texID = data.currentTex;
			data.currentTex++;
		}

		int8_t signs[8] = { -1, 1, 1, 1, 1, -1, -1, -1 };
		double r = 0.0;
		if (rot)
			r = sqrt(dim.x * dim.x + dim.y * dim.y) / 2;
		for (int i = 0; i < 4; i++)
		{
			if (rot)
			{
				float angle = std::atan2(dim.y / 2 * signs[2 * i + 1], dim.x / 2 * signs[2 * i]);
				data.vertexData[data.currentQuad * 4 + i].pos[0] = pos.x + r * std::cos(angle + rot * 0.0174532925);
				data.vertexData[data.currentQuad * 4 + i].pos[1] = pos.y + r * std::sin(angle + rot * 0.0174532925);
			}
			else
			{
				data.vertexData[data.currentQuad * 4 + i].pos[0] = pos.x + signs[2 * i] * dim.x / 2;
				data.vertexData[data.currentQuad * 4 + i].pos[1] = pos.y + signs[2 * i + 1] * dim.y / 2;
			}

			data.vertexData[data.currentQuad * 4 + i].pos[2] = pos.z/-100000.0f;
			data.vertexData[data.currentQuad * 4 + i].col[0] = col.x;
			data.vertexData[data.currentQuad * 4 + i].col[1] = col.y;
			data.vertexData[data.currentQuad * 4 + i].col[2] = col.z;
			data.vertexData[data.currentQuad * 4 + i].col[3] = col.w;
			data.vertexData[data.currentQuad * 4 + i].texCoords[0] = (startingTexPos.x + (signs[2 * i] == 1 ? 1 : 0) * spriteSize.x) / texSize.x;
			data.vertexData[data.currentQuad * 4 + i].texCoords[1] = (startingTexPos.y + (signs[2 * i + 1] == 1 ? 1 : 0) * spriteSize.y) / texSize.y;
			data.vertexData[data.currentQuad * 4 + i].texID = texID;
		}
		data.currentQuad++;

		if (data.currentQuad >= data.MAX_QUADS || data.currentTex >= data.MAX_TEXTURES)
			Flush();
	}

	void Renderer::Write(const std::string& text, const Vec3& pos, float size, const Vec4& col, float rot)
	{
		data.textObj->Write(text, pos, size, col, rot);
	}

	void Renderer::DrawLine(const Vec2& start, const Vec2& end, const Vec4& col, float width, float zIndex)
	{
		Vec3 center = { (end.x + start.x) / 2, (start.y + end.y) / 2, zIndex };
		Vec2 dim = { width, std::sqrt((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y)) };
		float rot = std::atan2(end.y - start.y, end.x - start.x) * 57.2957795f - 90.0f;
		DrawQuad(center, dim, col, rot);
	}
}