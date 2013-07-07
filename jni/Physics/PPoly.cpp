#include "PPoly.hpp"

namespace Core
{
	PPoly::PPoly()
	{
        m_type = e_poly;
        m_vertexCount = 0;
        m_vertices = NULL;
	}

	PPoly::PPoly(PPoly p_poly)
	{
		m_type = e_poly;

		Set(&(p_poly.GetVertex(0)), p_poly.GetVertexCount());
	}

	void PPoly::ComputeAABB(PAABB* p_aabb, PVec2 p_translate, float p_angle)
	{
		*p_aabb = PAABB();
		for(int i = 0; i < m_vertexCount; i++)
		{
			p_aabb->AddPoint(m_vertices[i].Rotate(p_angle));
		}

		p_aabb->xmin += p_translate.x;
		p_aabb->xmax += p_translate.x;

		p_aabb->ymin += p_translate.y;
		p_aabb->ymax += p_translate.y;
	}


	void PPoly::Set(PVec2* p_vertices, int p_count)
	{
		delete [] m_vertices;

		m_vertexCount = p_count;
		m_vertices = new PVec2[p_count];

		for(int i = 0; i < m_vertexCount; i++)
		{
			m_vertices[i] = p_vertices[i];
		}
	}
}
