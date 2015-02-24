#include "PCollide.hpp"

namespace MPACK
{
	namespace Physics
	{
		bool PCollide::CollideObjects(const PObject& obj1, const PObject& obj2)
		{
			if(!obj1.GetAABB().Intersect(obj2.GetAABB()))
			{
				return false;
			}

			//return true;
			PShape::Type t1 = obj1.GetShape()->GetType(),
				  t2 = obj2.GetShape()->GetType();

			if(t1 == PShape::e_poly && t2 == PShape::e_poly)
			{
				return CollidePolys(obj1, obj2);
			}
			else if(t1 == PShape::e_circle && t2 == PShape::e_circle)
			{
				return CollideCircles(obj1, obj2);
			}
			else if(t1 == PShape::e_circle && t2 == PShape::e_poly)
			{
				return CollideCirclePoly(obj1, obj2);
			}
			else if(t1 == PShape::e_poly && t2 == PShape::e_circle)
			{
				return CollideCirclePoly(obj2, obj1);
			}
			return false;
		}

		bool PCollide::CollidePolys(const PObject& obj1, const PObject& obj2)
		{

			PPoly s1(*(PPoly*)obj1.GetShape()),
				  s2(*(PPoly*)obj2.GetShape());

			for(int i = 0; i < s1.GetVertexCount(); i++)
			{
				s1.m_vertices[i].Rotate(obj1.GetAngle());
				s1.m_vertices[i] += obj1.GetPosition();
			}

			for(int i = 0; i < s2.GetVertexCount(); i++)
			{
				s2.m_vertices[i].Rotate(obj2.GetAngle());
				s2.m_vertices[i] += obj2.GetPosition();
			}

			PVec2 p1, p2;
			PSegm o1, o2;

			p1 = s1.GetVertex(s1.GetVertexCount() - 1);

			for(int i = 0; i < s1.GetVertexCount(); i++)
			{
				p2 = s1.GetVertex(i);
				PVec2 edge = p1 - p2;
				float tmp = edge.x;
				edge.x = -edge.y;
				edge.y = tmp;

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
				float tmp = edge.x;
				edge.x = -edge.y;
				edge.y = tmp;

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

			return true;
		}

		bool PCollide::CollideCircles(const PObject& obj1, const PObject& obj2)
		{
			PCircle *c1, *c2;
			c1 = (PCircle*)obj1.GetShape();
			c2 = (PCircle*)obj2.GetShape();

			if((obj1.GetPosition() - obj2.GetPosition()).Length() <= (c1->GetRadius() + c2->GetRadius()))
			{
				return true;
			}

			return false;
		}

		bool PCollide::CollideCirclePoly(const PObject& obj1, const PObject& obj2)
		{
			PCircle c(*(PCircle*)obj1.GetShape());
			PPoly p(*(PPoly*)obj2.GetShape());

			for(int i = 0; i < p.GetVertexCount(); i++)
			{
				p.m_vertices[i].Rotate(obj2.GetAngle());
				p.m_vertices[i] += obj2.GetPosition();
			}

			PVec2 p1, p2;
			PSegm o1, o2;


			p1 = p.GetVertex(p.GetVertexCount() - 1);

			for(int i = 0; i < p.GetVertexCount(); i++)
			{
				p2 = p.GetVertex(i);
				PVec2 edge = p1 - p2;
				float tmp = edge.x;
				edge.x = -edge.y;
				edge.y = tmp;

				edge.Normalize();

				o1.Clear();
				o2.Clear();

				for(int j = 0; j < p.GetVertexCount(); j++)
				{
					o1.AddPoint(p.GetVertex(j).Dot(edge));
				}

				o2.AddPoint(obj1.GetPosition().Dot(edge));
				o2.m_xmax += c.GetRadius();
				o2.m_xmin -= c.GetRadius();

				if(!o1.Intersect(o2))
				{
					return false;
				}

				p1 = p2;
			}

			p1 = obj1.GetPosition();

			for(int i = 0; i < p.GetVertexCount(); i++)
			{
				p2 = p.GetVertex(i);
				PVec2 edge = p1 - p2;

	/*			float tmp = edge.x;
				edge.x = -edge.y;
				edge.y = tmp;
	*/
				edge.Normalize();

				o1.Clear();
				o2.Clear();

				for(int j = 0; j < p.GetVertexCount(); j++)
				{
					o1.AddPoint(p.GetVertex(j).Dot(edge));
				}


				o2.AddPoint(obj1.GetPosition().Dot(edge));
				o2.m_xmax += c.GetRadius();
				o2.m_xmin -= c.GetRadius();

				if(!o1.Intersect(o2))
				{
					return false;
				}

			}

			return true;
		}
	}
}
