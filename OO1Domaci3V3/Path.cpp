#include "Path.h"

namespace ndb {
	Path& Path::operator+=(Point const& point) {
		if (has(point)) throw EPathContainsPoint();
		_list += point;
		_length_calculated = false;
		return *this;
	}

	double Path::get_length() const {
		if (_length_calculated) return _length;
		_length = 0;
		for (std::size_t i = 0; i + 1 < _list.size(); ++i) {
			_length += Point::distance(_list[i], _list[i + 1]);
		}
		_length_calculated = true;
		return _length;
	}

	bool Path::has(Point const& point) const {
		for (std::size_t i = 0; i < _list.size(); ++i) {
			if (_list[i] == point) return true;
		}
		return false;
	}

	std::ostream& operator<<(std::ostream& os, Path const& path) {
		for (std::size_t i = 0; i < path._list.size(); ++i) {
			os << path._list[i] <<'\n';
		}
		return os;
	}

}