#ifndef MPACK_TEXTUREMAPPEDFONT_HPP
#define MPACK_TEXTUREMAPPEDFONT_HPP

#include "Texture2D.hpp"
#include "Vertex.hpp"
#include "Debug.hpp"
#include "Math.hpp"
#include "Sprite.hpp"

#include <vector>
#include <string>

namespace MPACK
{
	namespace Graphics
	{
		struct CellSpacing
		{
			GLfloat top,bottom,left,right;
		};

		class TextureMappedFont
		{
		public:
			TextureMappedFont();

			enum AlignType {ALIGN_LEFT_TOP, ALIGN_CENTER};
			enum CaseType {NONE, UPPERCASE, LOWERCASE};
			enum FormatType {RGB_MAGNITUDE, ALPHA};

			void SetFontSize(GLfloat fontSize);
			void SetCharSpacing(GLfloat charSpacing=0.0f);
			void SetMonospaced(bool monospaced=true);
			void SendString(std::string str, GLfloat x, GLfloat y, AlignType alignType=ALIGN_LEFT_TOP, std::vector<Math::Vector4f> *colorPattern=NULL);

			void SetCase(CaseType caseType);
			CaseType GetCase() const;

			FormatType GetFormat() const;

			void SetCharPadding(GLfloat charPadding);
			GLfloat GetCharPadding() const;

			void AutoCalibrate();

			bool 		Load(const std::string& textureName, FormatType format);

			Texture2D* 	GetTexturePointer();

			GLfloat 	GetFontSize() const;
			GLfloat 	GetTextWidth(const std::string &str);

			GLfloat 		m_layer;

		private:
			static const BYTE 		FORMATTYPE_ALPHA_THRESHOLD=3;
			static constexpr float	FORMATTYPE_RGB_MAGNITUDE_THRESHOLD=0.01f;

			void		BuildCellSpacing_RGB_MAGNITUDE(Image *pFontImage);
			void		BuildCellSpacing_ALPHA(Image *pFontImage);

			Texture2D		m_texture;

			GLfloat			m_fontSize;
			GLfloat			m_charSpacing;
			GLfloat			m_charPadding;
			bool			m_monospaced;

			CellSpacing		m_cellSpacing[16][16];

			CaseType		m_caseType;
			FormatType		m_formatType;
		};
	}
}

#endif
