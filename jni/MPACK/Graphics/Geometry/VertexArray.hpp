#ifndef MPACK_VERTEXARRAY_H
#define MPACK_VERTEXARRAY_H

#include "Types.hpp"
#include "Math.hpp"

#include <vector>

namespace MPACK
{
	namespace Graphics
	{
		class VertexArray
		{
		public:
			VertexArray();
			~VertexArray();

			void	UpdateVertexFormat();
			void	UpdateArrays();
		//	void	MapTexCoordForAtlas(GLuint texCoord, Texture2D *texture);

			GLuint	GetVertexFormat();

			std::vector<Math::Vector3f>	m_position;
			std::vector<Math::Vector4f>	m_color;
			std::vector<Math::Vector2f>	m_texCoord[8];
			std::vector<Math::Vector3f>	m_normal;
			std::vector<Math::Vector3f>	m_tangent;
		protected:
			GLuint					m_vertexFormat;
		};
	}
}
	
#endif
