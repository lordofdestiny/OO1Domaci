#ifndef PATH_H
#define PATH_H

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
		bool has(Point const& point) const;
	};
}

#endif