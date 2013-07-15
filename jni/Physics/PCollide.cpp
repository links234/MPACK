#include "PCollide.hpp"

namespace Core
{
	bool CollideObjects(const PObject& obj1, const PObject& obj2)
	{
		if(!obj1.GetAABB().Intersect(obj2.GetAABB()))
		{
			return false;
		}

		//return true;

		if(obj1.GetShape()->GetType() == PShape::e_poly && obj2.GetShape()->GetType() == PShape::e_poly)
		{
			PPoly s1(*(PPoly*)obj1.GetShape()),
				  s2(*(PPoly*)obj2.GetShape());

			for(int i = 0; i < s1.GetVertexCount(); i++)
			{
				const_cast<PVec2&>(s2.GetVertex(i)).Rotate(obj1.GetAngle());
				const_cast<PVec2&>(s2.GetVertex(i)) += obj1.GetPosition();
			}

			for(int i = 0; i < s2.GetVertexCount(); i++)
			{
				const_cast<PVec2&>(s2.GetVertex(i)).Rotate(obj2.GetAngle());
				const_cast<PVec2&>(s2.GetVertex(i)) += obj2.GetPosition();
			}

			PVec2 p1, p2;
			PSegm o1, o2;

			p1 = s1.GetVertex(s1.GetVertexCount() - 1);

			for(int i = 0; i < s1.GetVertexCount(); i++)
			{
				p2 = s1.GetVertex(i);
				PVec2 edge = p1 - p2;
				edge.Normalize();

				o1.Clear();
				o2.Clear();

				for(int j = 0; j < s1.GetVertexCount(); j++)
				{
					o1.AddPoint(s1.GetVertex(j).Dot(edge));
				}

				for(int j = 0; j < s2.GetVertexCount(); j++)
				{
					o2.AddPoint(s2.GetVertex(j).Dot(edge));
				}

				if(!o1.Intersect(o2))
				{
					return false;
				}

				p1 = p2;
			}

			p1 = s2.GetVertex(s2.GetVertexCount() - 1);

			for(int i = 0; i < s2.GetVertexCount(); i++)
			{
				p2 = s2.GetVertex(i);
				PVec2 edge = p1 - p2;
				edge.Normalize();

				o1.Clear();
				o2.Clear();

				for(int j = 0; j < s1.GetVertexCount(); j++)
				{
					o1.AddPoint(s1.GetVertex(j).Dot(edge));
				}

				for(int j = 0; j < s2.GetVertexCount(); j++)
				{
					o2.AddPoint(s2.GetVertex(j).Dot(edge));
				}

				if(!o1.Intersect(o2))
				{
					return false;
				}

				p1 = p2;
			}

		}

		return true;
	}


}
