#include "Collider.hpp"

#include "Manifold.hpp"
#include "Shapes.hpp"
#include "Body.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace Physics
	{
		Collider::Callback Collider::Dispatch[Shape::eCount][Shape::eCount] =
		{
			{
					Collider::CircleToCircle,Collider::CircleToPolygon
			},
			{
					Collider::PolygonToCircle,Collider::PolygonToPolygon
			},
		};

		void Collider::CircleToCircle(Manifold *m,Body *a,Body *b)
		{
			CircleShape *A=reinterpret_cast<CircleShape*>(a->m_shape);
			CircleShape *B=reinterpret_cast<CircleShape*>(b->m_shape);

			Vector2f normal=b->m_position-a->m_position;

			float distSqr=normal.SquareLength();
			float radius=A->radius+B->radius;

			if(distSqr>=radius*radius)
			{
				m->m_contactCount=0;
				return;
			}

			float distance=Misc<float>::Sqrt(distSqr);

			m->m_contactCount=1;

			if(distance==0.0f)
			{
				m->m_penetration=A->radius;
				m->m_normal=Vector2f(1,0);
				m->m_contacts[0]=a->m_position;
			}
			else
			{
				m->m_penetration=radius-distance;
				m->m_normal=normal/distance;
				m->m_contacts[0]=m->m_normal*A->radius+a->m_position;
			}
		}

		void Collider::CircleToPolygon(Manifold *m,Body *a,Body *b)
		{
			CircleShape *A=reinterpret_cast<CircleShape*>(a->m_shape);
			PolygonShape *B=reinterpret_cast<PolygonShape*>(b->m_shape);

			m->m_contactCount=0;

			Vector2f center=a->m_position;
			center=B->u.Transpose()*(center-b->m_position);

			float separation=MPACK::Math::Misc<float>::c_Min;
			int faceNormal=0;
			for(int i=0;i<B->m_vertexCount;++i)
			{
				float s=Dot(B->m_normals[i],center-B->m_vertices[i]);

				if(s>A->radius)
				{
					return;
				}

				if(s>separation)
				{
					separation=s;
					faceNormal=i;
				}
			}

			Vector2f v1=B->m_vertices[faceNormal];
			int i2=faceNormal+1<B->m_vertexCount?faceNormal+1:0;
			Vector2f v2 = B->m_vertices[i2];

			if(separation<MPACK::Math::Misc<float>::c_Epsilon)
			{
				m->m_contactCount=1;
				m->m_normal=-(B->u*B->m_normals[faceNormal]);
				m->m_contacts[0]=m->m_normal*A->radius+a->m_position;
				m->m_penetration=A->radius;
				return;
			}

			float dot1=Dot(center-v1,v2-v1);
			float dot2=Dot(center-v2,v1-v2);
			m->m_penetration=A->radius-separation;

			if(dot1<=0.0f)
			{
				if(SquareDistance(center,v1)>A->radius*A->radius)
				{
					return;
				}

				m->m_contactCount=1;
				Vector2f n=v1-center;
				n=B->u*n;
				n.Normalize();
				m->m_normal=n;
				v1=B->u*v1+b->m_position;
				m->m_contacts[0]=v1;
			}
			else if(dot2<=0.0f)
			{
				if(SquareDistance(center,v2)>A->radius*A->radius)
				{
					return;
				}

				m->m_contactCount=1;
				Vector2f n=v2-center;
				v2=B->u*v2+b->m_position;
				m->m_contacts[0]=v2;
				n=B->u*n;
				n.Normalize();
				m->m_normal=n;
			}
			else
			{
				Vector2f n=B->m_normals[faceNormal];
				if(Dot(center-v1,n)>A->radius)
				{
					return;
				}

				n=B->u*n;
				m->m_normal=-n;
				m->m_contacts[0]=m->m_normal*A->radius+a->m_position;
				m->m_contactCount=1;
			}
		}

		void Collider::PolygonToCircle(Manifold *m,Body *a,Body *b)
		{
			CircleToPolygon(m,b,a);
			m->m_normal=-m->m_normal;
		}

		float Collider::FindAxisLeastPenetration(int *faceIndex,PolygonShape *A,PolygonShape *B)
		{
			float bestDistance=MPACK::Math::Misc<float>::c_Min;
			int bestIndex;

			for(int i=0;i<A->m_vertexCount;++i)
			{
				Vector2f n=A->m_normals[i];
				Vector2f nw=A->u*n;

				Matrix2f buT=B->u.Transpose();
				n=buT*nw;

				Vector2f s=B->GetSupport(-n);

				Vector2f v=A->m_vertices[i];
				v=A->u*v+A->body->m_position;
				v-=B->body->m_position;
				v=buT*v;

				float d=Dot(n,s-v);

				if(d>bestDistance)
				{
					bestDistance=d;
					bestIndex=i;
				}
			}

			*faceIndex=bestIndex;
			return bestDistance;
		}

		void Collider::FindIncidentFace(Vector2f *v,PolygonShape *RefPoly,PolygonShape *IncPoly,int referenceIndex)
		{
			Vector2f referenceNormal=RefPoly->m_normals[referenceIndex];

			referenceNormal=RefPoly->u*referenceNormal;
			referenceNormal=IncPoly->u.Transpose()*referenceNormal;

			int incidentFace=0;
			float minDot=MPACK::Math::Misc<float>::c_Max;
			for(int i=0;i<IncPoly->m_vertexCount;++i)
			{
				float dot=Dot(referenceNormal,IncPoly->m_normals[i]);
				if(dot<minDot)
				{
					minDot=dot;
					incidentFace=i;
				}
			}

			v[0]=IncPoly->u*IncPoly->m_vertices[incidentFace]+IncPoly->body->m_position;
			incidentFace=incidentFace+1>=(int)IncPoly->m_vertexCount?0:incidentFace+1;
			v[1]=IncPoly->u*IncPoly->m_vertices[incidentFace]+IncPoly->body->m_position;
		}

		int Collider::Clip(Vector2f n,float c,Vector2f *face)
		{
			int sp = 0;
			Vector2f out[2] = {
				face[0],
				face[1]
			};

			float d1=Dot(n,face[0])-c;
			float d2=Dot(n,face[1])-c;

			if(d1<=0.0f)
			{
				out[sp++]=face[0];
			}

			if(d2<=0.0f)
			{
				out[sp++]=face[1];
			}

			if(d1*d2<0.0f)
			{
				float alpha=d1/(d1-d2);
				out[sp]=face[0]+alpha*(face[1]-face[0]);
				++sp;
			}

			face[0]=out[0];
			face[1]=out[1];

			return sp;
		}

		void Collider::PolygonToPolygon( Manifold *m, Body *a, Body *b )
		{
			PolygonShape *A=reinterpret_cast<PolygonShape *>(a->m_shape);
			PolygonShape *B=reinterpret_cast<PolygonShape *>(b->m_shape);
			m->m_contactCount=0;

			int faceA;
			float penetrationA=FindAxisLeastPenetration(&faceA,A,B);
			if(penetrationA>=0.0f)
			{
				return;
			}

			int faceB;
			float penetrationB=FindAxisLeastPenetration(&faceB,B,A);
			if(penetrationB>=0.0f)
			{
				return;
			}

			int referenceIndex;
			bool flip;

			PolygonShape *RefPoly;
			PolygonShape *IncPoly;

			if(MPACK::Math::Misc<float>::BiasGreaterThan(penetrationA,penetrationB))
			{
				RefPoly = A;
				IncPoly = B;
				referenceIndex = faceA;
				flip = false;
			}
			else
			{
				RefPoly = B;
				IncPoly = A;
				referenceIndex = faceB;
				flip = true;
			}

			Vector2f incidentFace[2];
			FindIncidentFace(incidentFace,RefPoly,IncPoly,referenceIndex);

			Vector2f v1=RefPoly->m_vertices[referenceIndex];
			referenceIndex=referenceIndex+1==RefPoly->m_vertexCount?0:referenceIndex+1;
			Vector2f v2=RefPoly->m_vertices[referenceIndex];

			v1 = RefPoly->u * v1 + RefPoly->body->m_position;
			v2 = RefPoly->u * v2 + RefPoly->body->m_position;

			Vector2f sidePlaneNormal=(v2-v1);
			sidePlaneNormal.Normalize();

			Vector2f refFaceNormal(sidePlaneNormal.y,-sidePlaneNormal.x);

			float refC=Dot(refFaceNormal,v1);
			float negSide=-Dot(sidePlaneNormal,v1);
			float posSide=Dot(sidePlaneNormal,v2);

			if(Clip(-sidePlaneNormal,negSide,incidentFace )<2)
			{
				return;
			}

			if(Clip(sidePlaneNormal,posSide,incidentFace )<2)
			{
				return;
			}

			m->m_normal=flip?-refFaceNormal:refFaceNormal;

			int contactPoints=0;
			float separation=Dot(refFaceNormal,incidentFace[0])-refC;
			if(separation<=0.0f)
			{
				m->m_contacts[contactPoints]=incidentFace[0];
				m->m_penetration=-separation;
				++contactPoints;
			}
			else
			{
				m->m_penetration=0;
			}

			separation=Dot(refFaceNormal,incidentFace[1])-refC;
			if(separation<=0.0f)
			{
				m->m_contacts[contactPoints]=incidentFace[1];

				m->m_penetration+=-separation;
				++contactPoints;

				m->m_penetration/=(float)contactPoints;
			}

			m->m_contactCount=contactPoints;
		}
	}
}
