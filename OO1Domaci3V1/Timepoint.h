#pragma once
#include "Exceptions.h"
#include <ostream>

namespace ndb {
	class Timepoint {
	public:
		using time_type = unsigned short;
	private:
		time_type _year, _month, _day, _hour, _minute;
	public:
		Timepoint(time_type year, time_type month, time_type day,
			time_type hour, time_type minute) :
			_year(year), _month(month), _day(day),
			_hour(hour), _minute(minute) {
			validate();
		}
		friend std::ostream& operator<<(std::ostream& os, Timepoint const& timepoint) {
			auto [y, M, d, h, m] = timepoint;
			return os << y << '.' << M << '.' << d << '-' << h << ':' << m;
		}
	public:
		static const time_type min_year = 1950;
		static const time_type max_year = 2100;
	private:
		static const inline time_type month_lengths[2][12] =
		{
			{31,28,31,30,31,30,31,31,30,31,30,31},
			{31,29,31,30,31,30,31,31,30,31,30,31},
		};
		static bool is_leap_year(time_type year);
		bool is_valid_timepoint();
		void validate();
	};
}
