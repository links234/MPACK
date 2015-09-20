#include "PolygonShape.hpp"

#include "Body.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace Physics
	{
		PolygonShape::PolygonShape()
			: m_vertexCount(0)
		{
		}

		void PolygonShape::Initialize()
		{
			ComputeMass(body->m_material.density);
		}

		Shape* PolygonShape::Clone() const
		{
			PolygonShape *poly=new PolygonShape();
			poly->u=u;
			for(int i=0;i<m_vertexCount;++i)
			{
				poly->m_vertices[i]=m_vertices[i];
				poly->m_normals[i]=m_normals[i];
			}
			poly->m_vertexCount=m_vertexCount;
			return poly;
		}

		void PolygonShape::ComputeMass(float density)
		{
			Vector2f c(0.0f,0.0f);
			float area=0.0f;
			float momentOfInertia=0.0f;
			const float k_inv3=1.0f/3.0f;

			for(int i1=0;i1<m_vertexCount;++i1)
			{
				Vector2f p1(m_vertices[i1]);
				int i2=i1+1<m_vertexCount?i1+1:0;
				Vector2f p2(m_vertices[i2]);

				float _D=Cross(p1,p2);
				float triangleArea=0.5f*_D;

				area+=triangleArea;

				c+=triangleArea*k_inv3*(p1+p2);

				float intx2 = p1.x*p1.x+p2.x*p1.x+p2.x*p2.x;
				float inty2 = p1.y*p1.y+p2.y*p1.y+p2.y*p2.y;
				momentOfInertia+=(0.25f*k_inv3*_D)*(intx2+inty2);
			}

			c*=1.0f/area;

			for(int i=0;i<m_vertexCount;++i)
			{
				m_vertices[i]-=c;
			}

			body->m_mass=density*area;
			body->m_inverseMass=(body->m_mass)?1.0f/body->m_mass:0.0f;
			body->m_momentOfInertia=momentOfInertia*density;
			body->m_inverseMomentOfInertia=body->m_momentOfInertia?1.0f/body->m_momentOfInertia:0.0f;
		}

		void PolygonShape::SetOrientation(float radians)
		{
			u.Set(radians);
		}

		Shape::Type PolygonShape::GetType() const
		{
			return ePoly;
		}

		void PolygonShape::ComputeAABB()
		{
			m_aabb.Clear();
			for(int index=0;index<m_vertexCount;++index)
			{
				m_aabb.AddPoint(body->m_position+u*m_vertices[index]);
			}
		}

		void PolygonShape::SetAsBox(float hw,float hh)
		{
			m_vertexCount=4;
			m_vertices[0].Set(-hw,-hh);
			m_vertices[1].Set(hw,-hh);
			m_vertices[2].Set(hw,hh);
			m_vertices[3].Set(-hw,hh);
			m_normals[0].Set(0.0f,-1.0f);
			m_normals[1].Set(1.0f,0.0f);
			m_normals[2].Set(0.0f,1.0f);
			m_normals[3].Set(-1.0f,0.0f);
		}

		void PolygonShape::Set(Vector2f *vertices,int count)
		{
			count=MPACK::Math::Misc<float>::Min(count,POLYGONSHAPE_MAXVERTEXCOUNT);

			int rightMost=0;
			float highestXCoord=vertices[0].x;
			for(int i=1;i<count;++i)
			{
				float x=vertices[i].x;
				if(x>highestXCoord)
				{
					highestXCoord=x;
					rightMost=i;
				}
				else if(x==highestXCoord)
				if(vertices[i].y<vertices[rightMost].y)
				{
					rightMost=i;
				}
			}

			int hull[POLYGONSHAPE_MAXVERTEXCOUNT];
			int outCount=0;
			int indexHull=rightMost;

			for(;;)
			{
				hull[outCount]=indexHull;

				int nextHullIndex=0;
				for(int i=1;i<(int)count;++i)
				{
					if(nextHullIndex==indexHull)
					{
						nextHullIndex=i;
						continue;
					}

					Vector2f e1=vertices[nextHullIndex]-vertices[hull[outCount]];
					Vector2f e2=vertices[i]-vertices[hull[outCount]];
					float c=Cross(e1,e2);
					if(c<0.0f)
					nextHullIndex=i;

					if(c==0.0f && e2.SquareLength()>e1.SquareLength())
					{
						nextHullIndex=i;
					}
				}

				++outCount;
				indexHull=nextHullIndex;

				if(nextHullIndex==rightMost)
				{
					m_vertexCount=outCount;
					break;
				}
			}

			for(int i=0;i<m_vertexCount;++i)
			{
				m_vertices[i]=vertices[hull[i]];
			}

			for(int i1=0;i1<m_vertexCount;++i1)
			{
				int i2=i1+1<m_vertexCount?i1+1:0;
				Vector2f face=m_vertices[i2]-m_vertices[i1];

				m_normals[i1]=Vector2f(face.y,-face.x);
				m_normals[i1].Normalize();
			}
		}

		Vector2f PolygonShape::GetSupport(const Vector2f& dir)
		{
			float bestProjection=MPACK::Math::Misc<float>::c_Min;
			Vector2f bestVertex;

			for(int i=0;i<m_vertexCount;++i)
			{
				Vector2f v=m_vertices[i];
				float projection=Dot(v,dir);

				if(projection>bestProjection)
				{
					bestVertex=v;
					bestProjection=projection;
				}
			}

			return bestVertex;
		}
	}
}
