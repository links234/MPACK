#ifndef PHYSICSPOLY_HPP
#define PHYSICSPOLY_HPP

#include "PhysicsService.hpp"
#include "PShape.hpp"

namespace Core
{
	class PPoly : PShape
	{
	public:
		PPoly();
		PPoly(PPoly p_poly);

		void ComputeAABB(PAABB* p_aabb, PVec2 p_translate, float p_angle);

		int GetVertexCount();
		const PVec2& GetVertex(int index);

		void Set(PVec2* p_vertices, int p_count);

	private:
		int m_vertexCount;
		PVec2* m_vertices;
	};

	inline int PPoly::GetVertexCount() { return m_vertexCount; }
	inline PVec2& PPoly::GetVertex(int index) { return m_vertices[index]; }
}

#endif
