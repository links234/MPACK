#ifndef MPACK_MATRIX4IMPLEMENTATION_HPP
#define MPACK_MATRIX4IMPLEMENTATION_HPP

namespace MPACK
{
	template<class T> inline Math::Matrix4<T> Math::Matrix4<T>::operator* (const Math::Matrix4<T> &matrix) const
	{
		Math::Matrix4<T> rmatrix;
		for(register int i=0;i<4;++i)
		{
			for(register int j=0;j<4;++j)
			{
				rmatrix.m_matrix[i][j]=0;
				for(register int k=0;k<4;++k)
				{
					rmatrix.m_matrix[i][j]+=this->m_matrix[i][k]*matrix.m_matrix[k][j];
				}
			}
		}
		return rmatrix;
	}

	template<class T> inline void Math::Matrix4<T>::SetIdentity(Math::Matrix4<T> &matrix)
	{
		matrix.m_matrix[0][0]=1; matrix.m_matrix[0][1]=0; matrix.m_matrix[0][2]=0; matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=0; matrix.m_matrix[1][1]=1; matrix.m_matrix[1][2]=0; matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=0; matrix.m_matrix[2][1]=0; matrix.m_matrix[2][2]=1; matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0; matrix.m_matrix[3][1]=0; matrix.m_matrix[3][2]=0; matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetScale(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		matrix.m_matrix[0][0]=x; matrix.m_matrix[0][1]=0; matrix.m_matrix[0][2]=0; matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=0; matrix.m_matrix[1][1]=y; matrix.m_matrix[1][2]=0; matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=0; matrix.m_matrix[2][1]=0; matrix.m_matrix[2][2]=z; matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0; matrix.m_matrix[3][1]=0; matrix.m_matrix[3][2]=0; matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetTrans(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		matrix.m_matrix[0][0]=1; matrix.m_matrix[0][1]=0; matrix.m_matrix[0][2]=0; matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=0; matrix.m_matrix[1][1]=1; matrix.m_matrix[1][2]=0; matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=0; matrix.m_matrix[2][1]=0; matrix.m_matrix[2][2]=1; matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=x; matrix.m_matrix[3][1]=y; matrix.m_matrix[3][2]=z; matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetRoll(Math::Matrix4<T> &matrix, T angle)
	{
		angle=Math::Misc<T>::DegToRad(angle);
		T cosa=Math::Misc<T>::Cos(angle);
		T sina=Math::Misc<T>::Sin(angle);
		matrix.m_matrix[0][0]=cosa;  matrix.m_matrix[0][1]=sina;  matrix.m_matrix[0][2]=0; matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=-sina; matrix.m_matrix[1][1]=cosa;  matrix.m_matrix[1][2]=0; matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=0;     matrix.m_matrix[2][1]=0;     matrix.m_matrix[2][2]=1; matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0;     matrix.m_matrix[3][1]=0;     matrix.m_matrix[3][2]=0; matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetPitch(Math::Matrix4<T> &matrix, T angle)
	{
		angle=Math::Misc<T>::DegToRad(angle);
		T cosa=Math::Misc<T>::Cos(angle);
		T sina=Math::Misc<T>::Sin(angle);
		matrix.m_matrix[0][0]=1; matrix.m_matrix[0][1]=0;     matrix.m_matrix[0][2]=0;     matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=0; matrix.m_matrix[1][1]=cosa;  matrix.m_matrix[1][2]=-sina; matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=0; matrix.m_matrix[2][1]=sina;  matrix.m_matrix[2][2]=cosa;  matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0; matrix.m_matrix[3][1]=0;     matrix.m_matrix[3][2]=0;     matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetYaw(Math::Matrix4<T> &matrix, T angle)
	{
		angle=Math::Misc<T>::DegToRad(angle);
		T cosa=Math::Misc<T>::Cos(angle);
		T sina=Math::Misc<T>::Sin(angle);
		matrix.m_matrix[0][0]=cosa;  matrix.m_matrix[0][1]=0; matrix.m_matrix[0][2]=-sina;  matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=0;     matrix.m_matrix[1][1]=1; matrix.m_matrix[1][2]=0;      matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=sina;  matrix.m_matrix[2][1]=0; matrix.m_matrix[2][2]=cosa;   matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0;     matrix.m_matrix[3][1]=0; matrix.m_matrix[3][2]=0;      matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetRotationXYZ(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		Math::Matrix4<T> pitch,yaw,roll;
		SetPitch(pitch,x);
		SetYaw(yaw,y);
		SetRoll(roll,z);
		matrix=pitch*yaw*roll;
	}

	template<class T> inline void Math::Matrix4<T>::SetRotationXZY(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		Math::Matrix4<T> pitch,yaw,roll;
		SetPitch(pitch,x);
		SetYaw(yaw,y);
		SetRoll(roll,z);
		matrix=pitch*roll*yaw;
	}

	template<class T> inline void Math::Matrix4<T>::SetRotationYXZ(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		Math::Matrix4<T> pitch,yaw,roll;
		SetPitch(pitch,x);
		SetYaw(yaw,y);
		SetRoll(roll,z);
		matrix=yaw*pitch*roll;
	}

	template<class T> inline void Math::Matrix4<T>::SetRotationYZX(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		Math::Matrix4<T> pitch,yaw,roll;
		SetPitch(pitch,-x);
		SetYaw(yaw,y);
		SetRoll(roll,z);
		matrix=yaw*roll*pitch;
	}

	template<class T> inline void Math::Matrix4<T>::SetRotationZXY(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		Math::Matrix4<T> pitch,yaw,roll;
		SetPitch(pitch,-x);
		SetYaw(yaw,y);
		SetRoll(roll,z);
		matrix=roll*pitch*yaw;
	}

	template<class T> inline void Math::Matrix4<T>::SetRotationZYX(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		Math::Matrix4<T> pitch,yaw,roll;
		SetPitch(pitch,-x);
		SetYaw(yaw,y);
		SetRoll(roll,z);
		matrix=roll*yaw*pitch;
	}

	template<class T> inline void Math::Matrix4<T>::SetAxisRotation(Math::Matrix4<T> &matrix, Math::Vector3<T> axis, T angle)
	{
		axis.Normalize();
		T &X=axis.x;
		T &Y=axis.y;
		T &Z=axis.z;
		angle=Math::Misc<T>::DegToRad(angle);
		T c=Math::Misc<T>::Cos(angle);
		T s=Math::Misc<T>::Sin(angle);
		T t=1-c;
		T tX2=t*X*X;
		T tXY=t*X*Y;
		T tXZ=t*X*Z;
		T tYZ=t*Y*Z;
		T tZ2=t*Z*Z;
		T tY2=t*Y*Y;
		T sY=s*Y;
		T sX=s*X;
		T sZ=s*Z;
		matrix.m_matrix[0][0]=tX2+c;  matrix.m_matrix[0][1]=tXY+sZ; matrix.m_matrix[0][2]=tXZ-sY; matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=tXY-sZ; matrix.m_matrix[1][1]=tY2+c;  matrix.m_matrix[1][2]=tYZ+sX; matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=tXY+sY; matrix.m_matrix[2][1]=tYZ-sX; matrix.m_matrix[2][2]=tZ2+c;  matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0;	  matrix.m_matrix[3][1]=0;		matrix.m_matrix[3][2]=0;      matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetInverseScale(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		if(x==static_cast<T>(0))
		{
			x=Math::Misc<T>::c_Epsilon;
		}
		x=1.0f/x;
		if(y==static_cast<T>(0))
		{
			y=Math::Misc<T>::c_Epsilon;
		}
		y=1.0f/y;
		if(z==static_cast<T>(0))
		{
			z=Math::Misc<T>::c_Epsilon;
		}
		z=1.0f/z;
		matrix.m_matrix[0][0]=x; matrix.m_matrix[0][1]=0; matrix.m_matrix[0][2]=0; matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=0; matrix.m_matrix[1][1]=y; matrix.m_matrix[1][2]=0; matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=0; matrix.m_matrix[2][1]=0; matrix.m_matrix[2][2]=z; matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0; matrix.m_matrix[3][1]=0; matrix.m_matrix[3][2]=0; matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetInverseTrans(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		matrix.m_matrix[0][0]=1;  matrix.m_matrix[0][1]=0;  matrix.m_matrix[0][2]=0;  matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=0;  matrix.m_matrix[1][1]=1;  matrix.m_matrix[1][2]=0;  matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=0;  matrix.m_matrix[2][1]=0;  matrix.m_matrix[2][2]=1;  matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=-x; matrix.m_matrix[3][1]=-y; matrix.m_matrix[3][2]=-z; matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetInverseRoll(Math::Matrix4<T> &matrix, T angle)
	{
		angle=Math::Misc<T>::DegToRad(angle);
		T cosa=Math::Misc<T>::Cos(angle);
		T sina=Math::Misc<T>::Sin(angle);
		matrix.m_matrix[0][0]=cosa;  matrix.m_matrix[0][1]=sina;  matrix.m_matrix[0][2]=0; matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=-sina; matrix.m_matrix[1][1]=cosa;  matrix.m_matrix[1][2]=0; matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=0;     matrix.m_matrix[2][1]=0;     matrix.m_matrix[2][2]=1; matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0;     matrix.m_matrix[3][1]=0;     matrix.m_matrix[3][2]=0; matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetInversePitch(Math::Matrix4<T> &matrix, T angle)
	{
		angle=Math::Misc<T>::DegToRad(angle);
		T cosa=Math::Misc<T>::Cos(angle);
		T sina=Math::Misc<T>::Sin(angle);
		matrix.m_matrix[0][0]=1; matrix.m_matrix[0][1]=0;     matrix.m_matrix[0][2]=0;     matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=0; matrix.m_matrix[1][1]=cosa;  matrix.m_matrix[1][2]=-sina; matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=0; matrix.m_matrix[2][1]=sina;  matrix.m_matrix[2][2]=cosa;  matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0; matrix.m_matrix[3][1]=0;     matrix.m_matrix[3][2]=0;     matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetInverseYaw(Math::Matrix4<T> &matrix, T angle)
	{
		angle=Math::Misc<T>::DegToRad(angle);
		T cosa=Math::Misc<T>::Cos(angle);
		T sina=Math::Misc<T>::Sin(angle);
		matrix.m_matrix[0][0]=cosa;  matrix.m_matrix[0][1]=0; matrix.m_matrix[0][2]=-sina;  matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=0;     matrix.m_matrix[1][1]=1; matrix.m_matrix[1][2]=0;      matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=sina;  matrix.m_matrix[2][1]=0; matrix.m_matrix[2][2]=cosa;   matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0;     matrix.m_matrix[3][1]=0; matrix.m_matrix[3][2]=0;      matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetInverseRotationXYZ(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		SetRotationXYZ(matrix,-x,-y,-z);
	}

	template<class T> inline void Math::Matrix4<T>::SetInverseRotationXZY(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		SetRotationXZY(matrix,-x,-y,-z);
	}

	template<class T> inline void Math::Matrix4<T>::SetInverseRotationYXZ(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		SetRotationYXZ(matrix,-x,-y,-z);
	}

	template<class T> inline void Math::Matrix4<T>::SetInverseRotationYZX(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		SetRotationYZX(matrix,-x,-y,-z);
	}

	template<class T> inline void Math::Matrix4<T>::SetInverseRotationZXY(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		SetRotationZXY(matrix,-x,-y,-z);
	}

	template<class T> inline void Math::Matrix4<T>::SetInverseRotationZYX(Math::Matrix4<T> &matrix, T x, T y, T z)
	{
		SetRotationZYX(matrix,-x,-y,-z);
	}

	template<class T> inline void Math::Matrix4<T>::SetInverseAxisRotation(Math::Matrix4<T> &matrix, Math::Vector3<T> axis, T angle)
	{
		axis.normalize();
		T &X=axis.x;
		T &Y=axis.y;
		T &Z=axis.z;
		angle=Math::Misc<T>::DegToRad(angle);
		T c=Math::Misc<T>::Cos(angle);
		T s=Math::Misc<T>::Sin(angle);
		T t=1-c;
		T tX2=t*X*X;
		T tXY=t*X*Y;
		T tXZ=t*X*Z;
		T tYZ=t*Y*Z;
		T tZ2=t*Z*Z;
		T tY2=t*Y*Y;
		T sY=s*Y;
		T sX=s*X;
		T sZ=s*Z;
		matrix.m_matrix[0][0]=tX2+c;  matrix.m_matrix[0][1]=tXY+sZ; matrix.m_matrix[0][2]=tXZ-sY; matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=tXY-sZ; matrix.m_matrix[1][1]=tY2+c;  matrix.m_matrix[1][2]=tYZ+sX; matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=tXY+sY; matrix.m_matrix[2][1]=tYZ-sX; matrix.m_matrix[2][2]=tZ2+c;  matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0;	  matrix.m_matrix[3][1]=0;		matrix.m_matrix[3][2]=0;      matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetOrtho(Math::Matrix4<T> &matrix, T l, T r, T b, T t, T n, T f)
	{
		T rl=static_cast<T>(1)/(r-l);
		T tb=static_cast<T>(1)/(t-b);
		T fn=static_cast<T>(1)/(f-n);
		matrix.m_matrix[0][0]=static_cast<T>(2)*rl;	matrix.m_matrix[0][1]=0;					matrix.m_matrix[0][2]=0;					matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=0;					matrix.m_matrix[1][1]=static_cast<T>(2)*tb;	matrix.m_matrix[1][2]=0;					matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=0;					matrix.m_matrix[2][1]=0;					matrix.m_matrix[2][2]=static_cast<T>(-2)*fn;matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=-(r+l)*rl;			matrix.m_matrix[3][1]=-(t+b)*tb;			matrix.m_matrix[3][2]=-(f+n)*fn;			matrix.m_matrix[3][3]=1;
	}

	template<class T> inline void Math::Matrix4<T>::SetFrustum(Math::Matrix4<T> &matrix, T l, T r, T b, T t, T n, T f)
	{
		T rl=static_cast<T>(1)/(r-l);
		T tb=static_cast<T>(1)/(t-b);
		T fn=static_cast<T>(1)/(f-n);
		matrix.m_matrix[0][0]=(static_cast<T>(2)*n)*rl;		matrix.m_matrix[0][1]=static_cast<T>(0);            matrix.m_matrix[0][2]=static_cast<T>(0);            matrix.m_matrix[0][3]=static_cast<T>(0);
		matrix.m_matrix[1][0]=static_cast<T>(0);            matrix.m_matrix[1][1]=(static_cast<T>(2)*n)*tb;		matrix.m_matrix[1][2]=static_cast<T>(0);            matrix.m_matrix[1][3]=static_cast<T>(0);
		matrix.m_matrix[2][0]=(r+l)*rl;						matrix.m_matrix[2][1]=(t+b)*tb;						matrix.m_matrix[2][2]=-(f+n)*fn;					matrix.m_matrix[2][3]=static_cast<T>(-1);
		matrix.m_matrix[3][0]=static_cast<T>(0);            matrix.m_matrix[3][1]=static_cast<T>(0);            matrix.m_matrix[3][2]=(-static_cast<T>(2)*f*n)*fn;	matrix.m_matrix[3][3]=static_cast<T>(1);
	}

	template<class T> inline void Math::Matrix4<T>::SetPerspective(Math::Matrix4<T> &matrix, T fov, T aspect, T n, T f)
	{
		T top ( Misc<T>::Tan(Misc<T>::DegToRad(fov))*static_cast<T>(0.5) * n );
		T bottom(-top);
		SetFrustum(matrix,aspect*bottom,aspect*top,bottom,top,n,f);
	}

	template<class T> inline void Math::Matrix4<T>::SetCamera(Math::Matrix4<T> &matrix, Math::Vector3<T> look, Math::Vector3<T> up, Math::Vector3<T> right, Math::Vector3<T> position)
	{
		look.Normalize();
		up.Normalize();
		right.Normalize();
		matrix.m_matrix[0][0]=right.x;           matrix.m_matrix[0][1]=up.x;           matrix.m_matrix[0][2]=look.x;           matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=right.y;           matrix.m_matrix[1][1]=up.y;           matrix.m_matrix[1][2]=look.y;           matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=right.z;           matrix.m_matrix[2][1]=up.z;           matrix.m_matrix[2][2]=look.z;           matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0;				 matrix.m_matrix[3][1]=0;			   matrix.m_matrix[3][2]=0;				   matrix.m_matrix[3][3]=1;
		Matrix4<T> trans;
		SetInverseTrans(trans,position.x,position.y,position.z);
		matrix=trans*matrix;
	}

	template<class T> inline void Math::Matrix4<T>::SetObject(Math::Matrix4<T> &matrix, Math::Vector3<T> look, Math::Vector3<T> up, Math::Vector3<T> right, Math::Vector3<T> position)
	{
		look.Normalize();
		up.Normalize();
		right.Normalize();
		matrix.m_matrix[0][0]=right.x;           matrix.m_matrix[0][1]=right.y;         matrix.m_matrix[0][2]=right.z;      matrix.m_matrix[0][3]=0;
		matrix.m_matrix[1][0]=up.x;				 matrix.m_matrix[1][1]=up.y;			matrix.m_matrix[1][2]=up.z;			matrix.m_matrix[1][3]=0;
		matrix.m_matrix[2][0]=look.x;			 matrix.m_matrix[2][1]=look.y;          matrix.m_matrix[2][2]=look.z;		matrix.m_matrix[2][3]=0;
		matrix.m_matrix[3][0]=0;				 matrix.m_matrix[3][1]=0;			    matrix.m_matrix[3][2]=0;			matrix.m_matrix[3][3]=1;
		Matrix4<T> trans;
		SetTrans(trans,position.x,position.y,position.z);
		matrix=matrix*trans;
	}

	template<class T> inline void Math::Matrix4<T>::Transpose(Math::Matrix4<T> &matrix)
	{
		Matrix4<T> t=matrix;
		matrix.m_matrix[0][0]=t.m_matrix[0][0];
		matrix.m_matrix[1][0]=t.m_matrix[0][1];
		matrix.m_matrix[2][0]=t.m_matrix[0][2];
		matrix.m_matrix[3][0]=t.m_matrix[0][3];

		matrix.m_matrix[0][1]=t.m_matrix[1][0];
		matrix.m_matrix[1][1]=t.m_matrix[1][1];
		matrix.m_matrix[2][1]=t.m_matrix[1][2];
		matrix.m_matrix[3][1]=t.m_matrix[1][3];

		matrix.m_matrix[0][2]=t.m_matrix[2][0];
		matrix.m_matrix[1][2]=t.m_matrix[2][1];
		matrix.m_matrix[2][2]=t.m_matrix[2][2];
		matrix.m_matrix[3][2]=t.m_matrix[2][3];

		matrix.m_matrix[0][3]=t.m_matrix[3][0];
		matrix.m_matrix[1][3]=t.m_matrix[3][1];
		matrix.m_matrix[2][3]=t.m_matrix[3][2];
		matrix.m_matrix[3][3]=t.m_matrix[3][3];
	}

	#define MATRIX4_MINOR3(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,a2,b2,c2,d2) matrix.m_matrix[a][b]*(matrix.m_matrix[c][d]*matrix.m_matrix[e][f]-matrix.m_matrix[g][h]*matrix.m_matrix[i][j])-matrix.m_matrix[k][l]*(matrix.m_matrix[m][n]*matrix.m_matrix[o][p]-matrix.m_matrix[q][r]*matrix.m_matrix[s][t])+matrix.m_matrix[u][v]*(matrix.m_matrix[w][x]*matrix.m_matrix[y][z]-matrix.m_matrix[a2][b2]*matrix.m_matrix[c2][d2]);

	template<class T> inline void Math::Matrix4<T>::Inverse(Math::Matrix4<T> &matrix)
	{
		Matrix4<T> C;

		C.m_matrix[0][0]=MATRIX4_MINOR3(1,1,2,2,3,3,3,2,2,3,1,2,2,1,3,3,3,1,2,3,1,3,2,1,3,2,3,1,2,2);
		C.m_matrix[0][1]=-MATRIX4_MINOR3(1,0,2,2,3,3,3,2,2,3,1,2,2,0,3,3,3,0,2,3,1,3,2,0,3,2,3,0,2,2);
		C.m_matrix[0][2]=MATRIX4_MINOR3(1,0,2,1,3,3,3,1,2,3,1,1,2,0,3,3,3,0,2,3,1,3,2,0,3,1,3,0,2,1);
		C.m_matrix[0][3]=-MATRIX4_MINOR3(1,0,2,1,3,2,3,1,2,2,1,1,2,0,3,2,3,0,2,2,1,2,2,0,3,1,3,0,2,1);

		C.m_matrix[1][0]=-MATRIX4_MINOR3(0,1,2,2,3,3,3,2,2,3,0,2,2,1,3,3,3,1,2,3,0,3,2,1,3,2,3,1,2,2);
		C.m_matrix[1][1]=MATRIX4_MINOR3(0,0,2,2,3,3,3,2,2,3,0,2,2,0,3,3,3,0,2,3,0,3,2,0,3,2,3,0,2,2);
		C.m_matrix[1][2]=-MATRIX4_MINOR3(0,0,2,1,3,3,3,1,2,3,0,1,2,0,3,3,3,0,2,3,0,3,2,0,3,1,3,0,2,1);
		C.m_matrix[1][3]=MATRIX4_MINOR3(0,0,2,1,3,2,3,1,2,2,0,1,2,0,3,2,3,0,2,2,0,2,2,0,3,1,3,0,2,1);

		C.m_matrix[2][0]=MATRIX4_MINOR3(0,1,1,2,3,3,3,2,1,3,0,2,1,1,3,3,3,1,1,3,0,3,1,1,3,2,1,2,3,1);
		C.m_matrix[2][1]=-MATRIX4_MINOR3(0,0,1,2,3,3,3,2,1,3,0,2,1,0,3,3,3,0,1,3,0,3,1,0,3,2,3,0,1,2);
		C.m_matrix[2][2]=MATRIX4_MINOR3(0,0,1,1,3,3,3,1,1,3,0,1,1,0,3,3,3,0,1,3,0,3,1,0,3,1,3,0,1,1);
		C.m_matrix[2][3]=-MATRIX4_MINOR3(0,0,1,1,3,2,1,2,3,1,0,1,1,0,3,2,3,0,1,2,0,2,1,0,3,1,3,0,1,1);

		C.m_matrix[3][0]=-MATRIX4_MINOR3(0,1,1,2,2,3,2,2,1,3,0,2,1,1,2,3,2,1,1,3,0,3,1,1,2,2,2,1,1,2);
		C.m_matrix[3][1]=MATRIX4_MINOR3(0,0,1,2,2,3,2,2,1,3,0,2,1,0,2,3,2,0,1,3,0,3,1,0,2,2,2,0,1,2);
		C.m_matrix[3][2]=-MATRIX4_MINOR3(0,0,1,1,2,3,2,1,1,3,0,1,1,0,2,3,2,0,1,3,0,3,1,0,2,1,2,0,1,1);
		C.m_matrix[3][3]=MATRIX4_MINOR3(0,0,1,1,2,2,1,2,2,1,0,1,1,0,2,2,2,0,1,2,0,2,1,0,2,1,2,0,1,1);

		T oneOverDet  = static_cast<T>(1)/(matrix.m_matrix[0][0]*C.m_matrix[0][0]+matrix.m_matrix[0][1]*C.m_matrix[0][1]+matrix.m_matrix[0][2]*C.m_matrix[0][2]+matrix.m_matrix[0][3]*C.m_matrix[0][3]);

		matrix.m_matrix[0][0]=C.m_matrix[0][0] * oneOverDet;
		matrix.m_matrix[1][0]=C.m_matrix[0][1] * oneOverDet;
		matrix.m_matrix[2][0]=C.m_matrix[0][2] * oneOverDet;
		matrix.m_matrix[3][0]=C.m_matrix[0][3] * oneOverDet;

		matrix.m_matrix[0][1]=C.m_matrix[1][0] * oneOverDet;
		matrix.m_matrix[1][1]=C.m_matrix[1][1] * oneOverDet;
		matrix.m_matrix[2][1]=C.m_matrix[1][2] * oneOverDet;
		matrix.m_matrix[3][1]=C.m_matrix[1][3] * oneOverDet;

		matrix.m_matrix[0][2]=C.m_matrix[2][0] * oneOverDet;
		matrix.m_matrix[1][2]=C.m_matrix[2][1] * oneOverDet;
		matrix.m_matrix[2][2]=C.m_matrix[2][2] * oneOverDet;
		matrix.m_matrix[3][2]=C.m_matrix[2][3] * oneOverDet;

		matrix.m_matrix[0][3]=C.m_matrix[3][0] * oneOverDet;
		matrix.m_matrix[1][3]=C.m_matrix[3][1] * oneOverDet;
		matrix.m_matrix[2][3]=C.m_matrix[3][2] * oneOverDet;
		matrix.m_matrix[3][3]=C.m_matrix[3][3] * oneOverDet;
	}
}

#endif
