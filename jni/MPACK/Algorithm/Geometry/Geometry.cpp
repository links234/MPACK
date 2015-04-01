#include "Geometry.hpp"

using namespace std;
using namespace MPACK::Math;

namespace MPACK
{
	namespace Algorithm
	{
		struct ConvexHull_CMP
		{
			inline bool operator() (const Vector2f &A, const Vector2f &B)
			{
				return A.x < B.x || (A.x == B.x && A.y < B.y);
			}
		};

		float Cross(const Vector2f &O, const Vector2f &A, const Vector2f &B)
		{
			return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
		}

		vector<Vector2f> ConvexHull(vector<Vector2f> points)
		{
			int n = points.size(), k = 0;
			vector<Vector2f> hull(2*n);

			sort(points.begin(), points.end(), ConvexHull_CMP());

			for (int i = 0; i < n; i++)
			{
				while (k >= 2 && Cross(hull[k-2], hull[k-1], points[i]) <= 0)
				{
					k--;
				}
				hull[k++] = points[i];
			}

			for (int i = n-2, t = k+1; i >= 0; i--)
			{
				while (k >= t && Cross(hull[k-2], hull[k-1], points[i]) <= 0)
				{
					k--;
				}
				hull[k++] = points[i];
			}

			hull.resize(k);
			return hull;
		}
	}
}
