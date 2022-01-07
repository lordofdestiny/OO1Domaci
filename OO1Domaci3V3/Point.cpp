#include "Point.h"

namespace ndb {
	double Point::distance(Point const& a, Point const& b) {
		return std::hypot(a._x - b._x, a._y - b._y);
	}

	bool operator==(Point const& lhs, Point const& rhs) {
		auto& epsilon = Point::epsilon;
		return std::abs(lhs._x - rhs._x) < epsilon
			&& std::abs(lhs._y - rhs._y) < epsilon;
	}

	bool operator!=(Point const& lhs, Point const& rhs) {
		return !(lhs == rhs);
	}

	std::ostream& operator<<(std::ostream& os, Point const& point) {
		return os << "(" << point._x << "," << point._y << ")";
	}
}