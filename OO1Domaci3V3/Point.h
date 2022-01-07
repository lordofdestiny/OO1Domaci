#pragma once
#include <cmath>
#include <ostream>

namespace ndb {
	class Point {
		double _x, _y;
		static inline const double epsilon = 1e-7;
	public:
		Point(long x = 0, long y = 0) :
			_x(x), _y(y) { }

		static double distance(Point const& a, Point const& b);

		friend bool operator==(Point const& lhs, Point const& rhs);

		friend bool operator!=(Point const& lhs, Point const& rhs);

		friend std::ostream& operator<<(std::ostream& os, Point const& point);
	};
}