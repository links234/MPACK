#ifndef MPACK_PHYSICSPOLY_HPP
#define MPACK_PHYSICSPOLY_HPP

#include "PMath.hpp"
#include "PShape.hpp"

namespace Core
{
	class PShape;
	class PCollide;

	class PPoly : public PShape
	{
	public:
		PPoly();
		PPoly(const PPoly& p_poly);
		virtual ~PPoly();

		void ComputeAABB(PAABB* p_aabb, PVec2 p_translate, float p_angle) const;

		int 	GetVertexCount() const;
		PVec2& 	GetVertex(int index) const;

		void Set(PVec2* p_vertices, int p_count);
		void Set(float* p_vertices, int p_count, bool cooordsAre3D = false);
		void SetAsBox(float halfHeight, float halfWidth);

	private:
		friend class PCollide;

		int m_vertexCount;
		PVec2* m_vertices;
	};

	inline int PPoly::GetVertexCount() const { return m_vertexCount; }
	inline PVec2& PPoly::GetVertex(int index) const { return m_vertices[index]; }
}

#endif
