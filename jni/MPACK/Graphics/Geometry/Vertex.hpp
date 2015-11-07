#ifndef MPACK_VERTEX_HPP
#define MPACK_VERTEX_HPP

#include "Math.hpp"
#include "Types.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class SpriteVertex
		{
		public:
			SpriteVertex(GLfloat x=0, GLfloat y=0, GLfloat s=0, GLfloat t=0, GLfloat r=0, GLfloat g=0, GLfloat b=0, GLfloat a=0, GLfloat stype=0):x(x),y(y),s(s),t(t),r(r),g(g),b(b),a(a),stype(stype){}

			GLfloat x,y,s,t,r,g,b,a,stype;

			enum SpriteShadingMode{NONE, ALPHA_TEST, ALPHA_BLEND, NOTEXTURE, COLOR_SUM_ALPHA_BLEND};
		};
	}
}

#endif
