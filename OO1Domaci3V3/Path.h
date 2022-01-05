#pragma once
#include "List.h"
#include "Point.h"

namespace ndb {
	class Path {
		List<Point> _list;
		mutable double _length = 0;
		mutable double _length_calculated = false;
	public:
		Path() = default;
		Path& operator+=(Point const& point);

		double get_length() const;

		friend std::ostream& operator<<(std::ostream& os, Path const& path);
	private:
		bool has_point(Point const& point) const;
	};
}
