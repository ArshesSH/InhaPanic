#pragma once

#include <cassert>
#include <vector>
#include <list>
#include "Vec2.h"
#include "Surface.h"
#include "IndexedLineList.h"

namespace ArshesSH
{
	struct PointConversion
	{
		Vec2<int> operator()( const Gdiplus::Point& src ) const
		{
			return { src.X, src.Y };
		}

		Gdiplus::Point operator()( const Vec2<int>& src ) const
		{
			return { src.x, src.y };
		}

		std::vector<Gdiplus::Point> operator()( const std::vector<Vec2<int>>& src ) const
		{
			std::vector<Gdiplus::Point> points;
			PointConversion conversion;
			points.resize( src.size() );
			for ( int i = 0; i < (int)src.size(); ++i )
			{
				points[i] = conversion( src[i] );
			}
		}
	};


	class Polygon
	{
	public:
		Polygon() {}
		Polygon( const std::vector<Vec2<int>>& vertices )
			:
			vertices(vertices)
		{
		}

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
		static std::vector<Gdiplus::Point> ConvertToVectorOfPoint( const Polygon& src )
		{
			PointConversion conversion;
			return conversion( src.vertices );
		}

		size_t size() const
		{
			return vertices.size();
		}
		int GetSafeIndex(int i) const
		{
			if ( i >= (int)vertices.size() )
			{
				i %= (int)vertices.size();
			}
			else if ( i < 0 )
			{
				i = GetSafeIndex( (int)vertices.size() + i );
			}
			return i;
		}
		bool IsHorizontal(const Vec2<int>& lineStart, const Vec2<int>& lineEnd) const
		{
			return (lineStart.y == lineEnd.y);
		}
		bool IsHorizontal( int startIdx, int endIdx ) const
		{
			return vertices[startIdx].y == vertices[endIdx].y;
		}
		bool IsVertical( const Vec2<int>& lineStart, const Vec2<int>& lineEnd ) const
		{
			return (lineStart.x == lineEnd.x);
		}
		bool IsVertical( int startIdx, int endIdx ) const
		{
			return vertices[startIdx].x == vertices[endIdx].x;
		}
		bool IsOnAnyVertex(const Vec2<int>& pos) const
		{
			for ( const auto& v : vertices )
			{
				if ( v == pos )
				{
					return true;
				}
			}
			return false;
		}
		bool IsOnLine( const Vec2<int>& pos, int startIdx, int endIdx )
		{
		}

	private:


	public:
		
	private:
		std::vector<Vec2<int>> vertices;
	};
}