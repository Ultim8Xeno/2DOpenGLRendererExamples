#include "Text.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Debug.h"
#include "Renderer.h"
#include <glad/glad.h>

namespace OpenGLRenderer {

	static std::string GetStr(const std::string& inStr, const std::string& id, char end)
	{
		std::string outStr = "";
		uint32_t offset = inStr.find(id) + id.length();
		outStr = inStr.substr(offset, inStr.find(end, offset) - offset);
		return outStr;
	}

	TextObj::TextObj(const std::string& filepath)
	{
		std::ifstream file(filepath);
		if (!file.is_open()) return;
		std::string s;
		for (int i = 0; i < 3; i++)
			std::getline(file, s);
		ASSERT(!s.empty());
		
		std::string fileDir = "";
		fileDir = filepath.substr(0, filepath.find_last_of('/') + 1);
		std::string textureFilePath = fileDir + GetStr(s, "file=\"", '"');
		m_Texture = new Texture(textureFilePath);
		std::getline(file, s);
		uint32_t charCount = atoi(GetStr(s, "count=", '\n').c_str());

		for (int i = 0; i < charCount; i++)
		{
			std::getline(file, s);
			uint32_t id = atoi(GetStr(s, "id=", ' ').c_str());
			m_CharacterData[id].dims = Vec2(
				atoi(GetStr(s, "width=", ' ').c_str()),
				atoi(GetStr(s, "height=", ' ').c_str())
			);
			m_CharacterData[id].texCoords = Vec2(
				atoi(GetStr(s, "x=", ' ').c_str()),
				m_Texture->GetSize().y - atoi(GetStr(s, "y=", ' ').c_str()) - m_CharacterData[id].dims.y
			);
			m_CharacterData[id].offset = Vec2(
				atoi(GetStr(s, "xoffset=", ' ').c_str()),
				atoi(GetStr(s, "yoffset=", ' ').c_str())
			);
			m_CharacterData[id].advance = atoi(GetStr(s, "xadvance=", ' ').c_str());
		}
		std::getline(file, s);
		uint32_t kerningsCount = atoi(GetStr(s, "kernings count=", '\n').c_str());
		for (int i = 0; i < kerningsCount; i++)
		{
			std::getline(file, s);
			uint32_t first = atoi(GetStr(s, "first=", ' ').c_str());
			uint32_t second = atoi(GetStr(s, "second=", ' ').c_str());
			int amount = atoi(GetStr(s, "amount=", '\n').c_str());
			m_CharacterData[first].kernings[second] = amount;
		}
	}

	TextObj::~TextObj()
	{
		delete m_Texture;
	}

	void TextObj::Write(const std::string& text, const Vec3& pos, float size, const Vec4& col, float rot)
	{
		Vec2 topLeft = Vec2(0.0f, 0.0f);
		{
			Vec2 text_size = Vec2(0.0f, m_CharacterData['|'].dims.y * size);
			float lineLen = 0.0f;
			for (int i = 0; i < text.length(); i++)
			{
				if (text[i] == '\n')
				{
					if (i)
					{
						lineLen -= m_CharacterData[text[i - 1]].advance * size;
						lineLen += m_CharacterData[text[i - 1]].dims.x * size;
					}
					text_size.y += m_CharacterData['|'].dims.y * size;
					text_size.x = std::max(text_size.x, lineLen);

					lineLen = 0.0f;
				}
				lineLen += m_CharacterData[text[i]].advance * size;
			}
			lineLen -= m_CharacterData[text[text.length() - 1]].advance * size;
			lineLen += m_CharacterData[text[text.length() - 1]].dims.x * size;

			text_size.x = std::max(text_size.x, lineLen);
			topLeft.x = pos.x - text_size.x / 2;
			topLeft.y = pos.y + text_size.y / 2;
		}

		float xPos = topLeft.x;
		float yPos = topLeft.y;

		for (int i = 0; i < text.length(); i++)
		{
			char c = text[i];
			if (c == '\n')
			{
				yPos -= m_CharacterData['|'].dims.y * size;
				xPos = topLeft.x;
				continue;
			}

			Vec3 letterPos = Vec3(
				  xPos + m_CharacterData[c].dims.x*size/2 + m_CharacterData[c].offset.x * size
				, yPos - m_CharacterData[c].dims.y * size / 2 - m_CharacterData[c].offset.y * size
				, pos.z
			);

			Renderer::DrawFromSpriteSheet(letterPos, Vec2(m_CharacterData[c].dims.x * size, m_CharacterData[c].dims.y * size),
				m_Texture, m_CharacterData[c].texCoords, m_CharacterData[c].dims, col);

			xPos += m_CharacterData[c].advance * size;
			if (i < text.length() - 1)
			{
				if (m_CharacterData[c].kernings.find(text[i + 1]) != m_CharacterData[c].kernings.end())
				{
					xPos += m_CharacterData[c].kernings[text[i + 1]] * size;
				}
			}
		}
	}
}