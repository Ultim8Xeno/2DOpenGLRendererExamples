#pragma once
#include <string>
#include "Vector.h"
#include <unordered_map>
#include "Texture.h"

namespace OpenGLRenderer {

	class TextObj
	{
	public:
		TextObj(const std::string& filepath);
		~TextObj();
		void Write(const std::string& text, const Vec3& pos, float scale = 1.0f, const Vec4& col = Vec4(1.0f, 1.0f, 1.0f, 1.0f), float rot = 0.0f);
	private:
		struct Character
		{
			Vec2 texCoords;
			Vec2 dims;
			Vec2 offset;
			uint32_t advance;
			std::unordered_map<char, int> kernings;
		};
		std::unordered_map<char, Character> m_CharacterData;
		Texture* m_Texture = nullptr;
	};
}