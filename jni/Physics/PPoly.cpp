#include "PPoly.hpp"

#ifndef NULL
#define NULL	0
#endif

namespace Core
{
	PPoly::PPoly()
	{
        m_type = e_poly;
        m_vertexCount = 0;
        m_vertices = NULL;

        SetAsBox(0.5, 0.5);
	}

	PPoly::PPoly(const PPoly& p_poly):
			m_vertices(NULL), m_vertexCount(0)
	{
		m_type = e_poly;
		//Set(&(p_poly.GetVertex(0)), p_poly.GetVertexCount());
		Set(p_poly.m_vertices, p_poly.m_vertexCount);
	}

	PPoly::~PPoly()
	{
	}

	void PPoly::ComputeAABB(PAABB* p_aabb, PVec2 p_translate, float p_angle) const
	{
		*p_aabb = PAABB();
		for(int i = 0; i < m_vertexCount; i++)
		{
			p_aabb->AddPoint(m_vertices[i].Rotated(p_angle));
		}

		p_aabb->xmin += p_translate.x;
		p_aabb->xmax += p_translate.x;

		p_aabb->ymin += p_translate.y;
		p_aabb->ymax += p_translate.y;
	}


	void PPoly::Set(PVec2* p_vertices, int p_count)
	{
		if (m_vertices != NULL)
			delete [] m_vertices;

		m_vertexCount = p_count;
		m_vertices = new PVec2[p_count];

		for(int i = 0; i < m_vertexCount; i++)
		{
			m_vertices[i] = p_vertices[i];
		}
	}


	void PPoly::Set(float* p_vertices, int p_count, bool coordsAre3D)
	{
		if (m_vertices != NULL)
			delete [] m_vertices;

		m_vertexCount = p_count;
		m_vertices = new PVec2[p_count];

		int step = 2;
		if(coordsAre3D)
			step = 3;

		for(int i = 0; i < m_vertexCount; i++)
		{
			m_vertices[i].x = p_vertices[step*i];
			m_vertices[i].y = p_vertices[step*i+1];
		}
	}

	void PPoly::SetAsBox(float halfHeight, float halfWidth)
	{
		if (m_vertices != NULL)
			delete [] m_vertices;


		m_vertexCount = 4;
		m_vertices = new PVec2[4];
		m_vertices[0] = PVec2(-halfWidth,  halfHeight);
		m_vertices[1] = PVec2(-halfWidth, -halfHeight);
		m_vertices[2] = PVec2( halfWidth, -halfHeight);
		m_vertices[3] = PVec2( halfWidth,  halfHeight);
	}


}
