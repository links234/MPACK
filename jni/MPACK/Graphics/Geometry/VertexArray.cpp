#include "VertexArray.hpp"

#include "Math.hpp"
//#include "Texture2D.hpp"
#include "FlexibleVertexFormat.hpp"

namespace MPACK
{
	namespace Graphics
	{
		VertexArray::VertexArray()
			: m_vertexFormat(0)
		{
		}

		VertexArray::~VertexArray()
		{
		}

		void VertexArray::UpdateVertexFormat()
		{
			m_vertexFormat=0;
			if(!m_position.empty())
			{
				m_vertexFormat|=FVF::POSITION;
			}
			if(!m_color.empty())
			{
				m_vertexFormat|=FVF::COLOR;
			}
			if(!m_texCoord[0].empty())
			{
				m_vertexFormat|=FVF::TEXCOORD0;
			}
			if(!m_texCoord[1].empty())
			{
				m_vertexFormat|=FVF::TEXCOORD1;
			}
			if(!m_texCoord[2].empty())
			{
				m_vertexFormat|=FVF::TEXCOORD2;
			}
			if(!m_texCoord[3].empty())
			{
				m_vertexFormat|=FVF::TEXCOORD3;
			}
			if(!m_texCoord[4].empty())
			{
				m_vertexFormat|=FVF::TEXCOORD4;
			}
			if(!m_texCoord[5].empty())
			{
				m_vertexFormat|=FVF::TEXCOORD5;
			}
			if(!m_texCoord[6].empty())
			{
				m_vertexFormat|=FVF::TEXCOORD6;
			}
			if(!m_texCoord[7].empty())
			{
				m_vertexFormat|=FVF::TEXCOORD7;
			}
			if(!m_normal.empty())
			{
				m_vertexFormat|=FVF::NORMAL;
			}
			if(!m_tangent.empty())
			{
				m_vertexFormat|=FVF::TANGENT;
			}
		}

		void VertexArray::UpdateArrays()
		{
			if((m_vertexFormat&FVF::POSITION)==0)
			{
				m_position.clear();
			}
			if((m_vertexFormat&FVF::COLOR)==0)
			{
				m_color.clear();
			}
			if((m_vertexFormat&FVF::TEXCOORD0)==0)
			{
				m_texCoord[0].clear();
			}
			if((m_vertexFormat&FVF::TEXCOORD1)==0)
			{
				m_texCoord[1].clear();
			}
			if((m_vertexFormat&FVF::TEXCOORD2)==0)
			{
				m_texCoord[2].clear();
			}
			if((m_vertexFormat&FVF::TEXCOORD3)==0)
			{
				m_texCoord[3].clear();
			}
			if((m_vertexFormat&FVF::TEXCOORD4)==0)
			{
				m_texCoord[4].clear();
			}
			if((m_vertexFormat&FVF::TEXCOORD5)==0)
			{
				m_texCoord[5].clear();
			}
			if((m_vertexFormat&FVF::TEXCOORD6)==0)
			{
				m_texCoord[6].clear();
			}
			if((m_vertexFormat&FVF::TEXCOORD7)==0)
			{
				m_texCoord[7].clear();
			}
			if((m_vertexFormat&FVF::NORMAL)==0)
			{
				m_normal.clear();
			}
			if((m_vertexFormat&FVF::TANGENT)==0)
			{
				m_tangent.clear();
			}
		}

		/*void VertexArray::MapTexCoordForAtlas(GLuint texCoord, Texture2D *texture)
		{
			for(vector<Vector2f>::iterator it=m_texCoord[texCoord].begin();it!=m_texCoord[texCoord].end();++it)
			{
				(*it)=texture->MapToAtlasTexCoord((*it));
			}
		}*/

		GLuint VertexArray::GetVertexFormat()
		{
			return m_vertexFormat;
		}
	}
}
