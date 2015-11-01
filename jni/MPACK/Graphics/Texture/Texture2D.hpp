/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef MPACK_TEXTURE2D_HPP
#define MPACK_TEXTURE2D_HPP

#include "Types.hpp"
#include "Uncopyable.hpp"
#include "Math.hpp"

#include <string>

#define MAX_TEXTURES 8

namespace MPACK
{
	class Uncopyable;

	namespace Graphics
	{
		class Image;

		enum FilteringType {FILTER_POINT, FILTER_BILINEAR, FILTER_TRILINEAR};

		class Texture2D : public Uncopyable
		{
		public:
			Texture2D(bool needUpdate=true);
			~Texture2D();

			bool Load(std::string path, FilteringType filtering = FILTER_POINT, GLenum s_mode = GL_REPEAT, GLenum t_mode = GL_REPEAT);
			bool Load(const Image* image, FilteringType filtering = FILTER_POINT, GLenum s_mode = GL_REPEAT, GLenum t_mode = GL_REPEAT);

			void Build(GLuint width, GLuint height, FilteringType filtering = FILTER_POINT, GLenum s_mode = GL_REPEAT, GLenum t_mode = GL_REPEAT);
			void Bind(GLenum TEXTURE);

			void SetFilteringType(FilteringType filtering);
			void SetWrapMode(GLenum s_mode,GLenum t_mode);

			GLuint GetWidth() const;
			GLuint GetHeight() const;

			GLuint			m_texId;

		private:
			void Init();

			GLenum			m_sWrapMode;
			GLenum			m_tWrapMode;
			bool			m_needUpdate;
			GLuint			m_width,m_height;
			FilteringType	m_filteringType;
		};
	
		void InitTextureSlots();
		void BindTextureSlot(GLenum TEXTURE);
		void BindTextureToSlot(int textureId, GLenum TEXTURE);
	}
}

#endif
