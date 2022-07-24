#pragma once

#include "Vec2.h"

template <typename T>
class Ray
{
public:
	Ray(){}
	Ray( const Vec2<T>& pos)
		:
		pos(pos),
		dir({T(0), T(0)})
	{}
	Ray(const Vec2<T>& pos, const Vec2<T>& dir)
		:
		pos(pos),
		dir(dir)
	{}

	void SetDir( const Vec2<T>& normalizedDir )
	{
		dir = normalizedDir;
	}

	void ToPoint( const Vec2<T>& targetPos )
	{
		dir = (pos - targetPos).GetNormalized();
	}

	bool CastToLine( const Vec2<T>& lineStart, const Vec2<T>& lineEnd ) const
	{
		const T x1 = lineStart.x;
		const T y1 = lineStart.y;
		const T x2 = lineEnd.x;
		const T y2 = lineEnd.y;

		const T x3 = pos.x;
		const T y3 = pos.y;
		const T x4 = pos.x + dir.x;
		const T y4 = pos.y + dir.y;

		const T den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if ( den == 0 )
		{
			return false;
		}

		const T t = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4) / den;
		const T u = (x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2) / den;

		return (t > 0) && (t < 1) && (u > 0);
	}

	Vec2<T> GetCastedPos( const Vec2<T>& lineStart, const Vec2<T>& lineEnd ) const
	{
		{
			const T x1 = lineStart.x;
			const T y1 = lineStart.y;
			const T x2 = lineEnd.x;
			const T y2 = lineEnd.y;

			const T x3 = pos.x;
			const T y3 = pos.y;
			const T x4 = pos.x + dir.x;
			const T y4 = pos.y + dir.y;

			const T den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
			if ( den == 0 )
			{
				return {0,0};
			}

			const T t = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4) / den;
			const T u = (x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2) / den;

			if ( (t > 0) && (t < 1) && (u > 0) )
			{
				return { (x1 + t * (x2 - x1)), (y1 + t * (y2 - y1)) };
			}
			return { 0,0 };
		}
	}


private:
	Vec2<T> pos;
	Vec2<T> dir;
};