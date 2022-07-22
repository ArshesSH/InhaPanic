#pragma once

#include <cassert>
#include <vector>
#include <list>
#include "Vec2.h"
#include "Surface.h"
#include "IndexedLineList.h"

namespace ArshesSH
{
	struct PointToVec2
	{
		Vec2<int> operator()(const Gdiplus::Point& src)
		{
			return { src.X, src.Y };
		}
	};

	struct Vec2ToPoint
	{
		Gdiplus::Point operator()(const Vec2<int>& src)
		{
			return { src.x, src.y };
		}
	};

	class Polygon
	{
	public:
		Polygon() {}
		Polygon( const std::vector<Vec2<int>>& vertices )
			:
			vertices(vertices)
		{}

		Polygon operator+( const Vec2<int>& pos ) const
		{
			Polygon p = *this;
			for ( auto& v : p.vertices )
			{
				v += pos;
			}
			return p;
		}
		Polygon& operator+=( const Vec2<int>& pos )
		{
			for ( auto& v : vertices )
			{
				v += pos;
			}
			return *this;
		}

		size_t size() const
		{
			return vertices.size();
		}
		int GetSafeIndex(int i) const
		{
			if ( i < 0 )
			{
				i = GetSafeIndex( vertices.size() - i );
			}
			else if ( i > vertices.size() )
			{
				i = GetSafeIndex( i - vertices.size() );
			}
			
		}

	private:


	public:
		std::vector<Vec2<int>> vertices;
	private:
	};
}