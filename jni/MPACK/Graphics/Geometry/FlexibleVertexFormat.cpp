#include "FlexibleVertexFormat.hpp"

namespace MPACK
{
	namespace Graphics
	{
		namespace FVF
		{
			const GLuint POSITION		=	1<<0;
			const GLuint COLOR			=	1<<1;
			const GLuint TEXCOORD0		=	1<<2;
			const GLuint TEXCOORD1		=	1<<3;
			const GLuint TEXCOORD2		=	1<<4;
			const GLuint TEXCOORD3		=	1<<5;
			const GLuint TEXCOORD4		=	1<<6;
			const GLuint TEXCOORD5		=	1<<7;
			const GLuint TEXCOORD6		=	1<<8;
			const GLuint TEXCOORD7		=	1<<9;
			const GLuint NORMAL			=	1<<10;
			const GLuint TANGENT		=	1<<11;

			GLuint getSize(GLuint format)
			{
				GLuint size=0;
				if(format&POSITION)
				{
					size+=3;
				}
				if(format&COLOR)
				{
					size+=4;
				}
				if(format&TEXCOORD0)
				{
					size+=2;
				}
				if(format&TEXCOORD1)
				{
					size+=2;
				}
				if(format&TEXCOORD2)
				{
					size+=2;
				}
				if(format&TEXCOORD3)
				{
					size+=2;
				}
				if(format&TEXCOORD4)
				{
					size+=2;
				}
				if(format&TEXCOORD5)
				{
					size+=2;
				}
				if(format&TEXCOORD6)
				{
					size+=2;
				}
				if(format&TEXCOORD7)
				{
					size+=2;
				}
				if(format&NORMAL)
				{
					size+=3;
				}
				if(format&TANGENT)
				{
					size+=3;
				}
				return size*sizeof(GLfloat);
			}
		}
	}
}
