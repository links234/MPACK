#include "AnimatedSprite.hpp"

using namespace std;
using namespace MPACK::Math;

namespace MPACK
{
	namespace Graphics
	{
		AnimatedSprite::AnimatedSprite()
		{
		}

		AnimatedSprite::~AnimatedSprite()
		{
		}

		void AnimatedSprite::Render()
		{
			const AABB2Df &frame=m_frames[m_currentFrame];
			const GLfloat &Um=frame.m_xmin;
			const GLfloat &UM=frame.m_xmax;
			const GLfloat &Vm=frame.m_ymin;
			const GLfloat &VM=frame.m_ymax;

			Math::Vector2f v[4];
			v[0].x=-m_width;v[0].y=-m_height;
			v[0].Rotate(m_angle);
			v[0]+=m_position;

			v[1].x=+m_width;v[1].y=-m_height;
			v[1].Rotate(m_angle);
			v[1]+=m_position;

			v[2].x=+m_width;v[2].y=+m_height;
			v[2].Rotate(m_angle);
			v[2]+=m_position;

			v[3].x=-m_width;v[3].y=+m_height;
			v[3].Rotate(m_angle);
			v[3]+=m_position;

			swap(v[0],v[3]);
			swap(v[1],v[2]);

			SpriteVertex vertexData[]={	SpriteVertex(v[0].x,v[0].y,	Um,Vm,	m_color[0].x,m_color[0].y,m_color[0].z,m_color[0].w,	m_spriteShadingType),
										SpriteVertex(v[1].x,v[1].y,	UM,Vm,	m_color[1].x,m_color[1].y,m_color[1].z,m_color[1].w,	m_spriteShadingType),
										SpriteVertex(v[2].x,v[2].y,	UM,VM,	m_color[2].x,m_color[2].y,m_color[2].z,m_color[2].w,	m_spriteShadingType),
										SpriteVertex(v[3].x,v[3].y,	Um,VM,	m_color[3].x,m_color[3].y,m_color[3].z,m_color[3].w,	m_spriteShadingType) };

			Batcher::SendSpriteVertexQuad(vertexData,4,m_texture,IndexData::TRIANGLES,m_layer);
		}

		void AnimatedSprite::BuildFrameGrid(int rows, int cols)
		{
			m_frames.resize(rows*cols);

			GLfloat u=0.0f,v=1.0f;
			GLfloat uLength=1.0f/cols;
			GLfloat vLength=1.0f/rows;

			int index=0;
			for(int i=0;i<rows;++i,v-=vLength)
			{
				u=0.0f;
				for(int j=0;j<cols;++j,u+=uLength,++index)
				{
					m_frames[index].m_xmin=u;
					m_frames[index].m_xmax=u+uLength;
					m_frames[index].m_ymin=v-vLength;
					m_frames[index].m_ymax=v;
				}
			}
		}
	}
}
