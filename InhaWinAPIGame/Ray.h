#pragma once

#include "Vec2.h"

template <typename T>
class Ray
{
public:
	Ray(){}
	Ray( const Vec2<T>& pos)
		:
		pos(pos)
	{}

	//void ToPoint( const Vec2<T>& targetPos )
	//{
	//	dir = (targetPos - pos).GetNormalized();
	//}

	bool CastToLine( const Vec2<T>& lineStart, const Vec2<T>& lineEnd ) const
	{
		bool a = (pos.y < lineStart.y);
		bool b = (pos.y < lineEnd.y);
		bool c = (pos.x < (lineEnd.x - lineStart.x)* (pos.y - lineStart.y) / (lineEnd.y - lineStart.y) + lineStart.x);

		return (a != b) && c;

		/*return ((pos.y < lineStart.y) != (pos.y < lineEnd.y)&&
			pos.x < (lineEnd.x - lineStart.x)* (pos.y - lineStart.y) / (lineEnd.y - lineStart.y) + lineStart.x);*/
	}

	Vec2<T> GetCastedPos( const Vec2<T>& lineStart, const Vec2<T>& lineEnd ) const
	{
		return { 0,0 };
	}


private:
	Vec2<T> pos;
};