#pragma once
#include <cmath>
#include <ostream>

namespace ndb {


	class Point {
		double _x, _y;
		static double inline epsilon = 1e-7;
	public:
		Point(long x = 0, long y = 0) :
			_x(x), _y(y) { }

		friend bool operator==(Point const& lhs, Point const& rhs) {
			return std::abs(lhs._x - rhs._x) < epsilon
				&& std::abs(lhs._y - rhs._y) < epsilon;
		}

		friend bool operator!=(Point const& lhs, Point const& rhs) {
			return !(lhs == rhs);
		}

		friend std::ostream& operator<<(std::ostream& os, Point const& point) {
			return os << "(" << point._x << "," << point._y << ")";
		}

		static double distance(Point const& a, Point const& b) {
			return std::hypot(a._x - b._x, a._y - b._y);
		}
	};
}