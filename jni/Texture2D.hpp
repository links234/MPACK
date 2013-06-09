/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include "Types.hpp"
#include "Uncopyable.hpp"
#include "Maths.hpp"

#include <string>

#define MAX_TEXTURES 8

using namespace std;

class Uncopyable;

namespace Core
{
	class Image;

	enum FilteringType{Point,Bilinear,Trilinear};

	class Texture2D : public Uncopyable
	{
	public:
		Texture2D();
		~Texture2D();

		bool Load(string path, FilteringType filtering=Point, GLenum s_mode=GL_REPEAT, GLenum t_mode=GL_REPEAT);
		bool Load(const Image* image, FilteringType filtering=Point, GLenum s_mode=GL_REPEAT, GLenum t_mode=GL_REPEAT);

		void Build(GLuint width, GLuint height, FilteringType filtering=Point, GLenum s_mode=GL_REPEAT, GLenum t_mode=GL_REPEAT);
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

	void BindTextureSlot(GLenum TEXTURE);
}
#endif
