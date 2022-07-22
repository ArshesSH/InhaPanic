#pragma once

#include <cassert>
#include <vector>
#include <list>
#include "IndexedLineList.h"

namespace ArshesSH
{
	template<typename V>
	class Polygon
	{
	public:
		Polygon() {};
		Polygon( const std::vector<V>& vertices )
			:
			vertices( vertices )
		{}

		int GetSafeIndex( int i ) const
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
		template <typename T>
		int GetSafeIndex( int i, const std::vector<T>& v ) const
		{
			if ( i >= (int)v.size() )
			{
				i %= (int)v.size();
			}
			else if ( i < 0 )
			{
				i = GetSafeIndex( (int)v.size() + i );
			}
			return i;
		}



	public:
		std::vector<V> vertices;
	};
}