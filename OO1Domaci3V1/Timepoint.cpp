#include "Timepoint.h"

namespace ndb {
	bool Timepoint::is_leap_year(t_time year) {
		return (year % 100 != 0 && year % 4 == 0) || year % 400 == 0;
	}

	bool Timepoint::is_valid_timepoint() {
		return min_year <= _year && _year <= max_year
			&& 1 <= _month && _month <= 12 && 1 <= _day
			&& _day <= month_lengths[is_leap_year(_year)][_month - 1]
			&& 0 <= _hour && _hour <= 23
			&& 0 <= _minute && _minute <= 59;

	}
	void Timepoint::validate() {
		if (!is_valid_timepoint()) {
			throw InvalidTimepoint();
		}
	}

	std::ostream& operator<<(std::ostream& os, Timepoint const& timepoint) {
		auto [Y, M, d, h, m] = timepoint;
		return os << Y << '.' << M << '.' << d << '-' << h << ':' << m;
	}
}