#pragma once
#include "Exceptions.h"
#include <ostream>

namespace ndb {
	class Timepoint {
	public:
		using t_time = unsigned short;
	private:
		t_time _year, _month, _day, _hour, _minute;
	public:
		Timepoint(t_time year, t_time month, t_time day, t_time hour, t_time minute) :
			_year(year), _month(month), _day(day), _hour(hour), _minute(minute) {
			validate();
		}

		t_time year() const { return _year; }
		t_time month() const { return _month; }
		t_time day() const { return _day; }
		t_time hour() const { return _hour; }
		t_time min() const { return _minute; }
		
		friend std::ostream& operator<<(std::ostream& os, Timepoint const& timepoint);
	public:
		static inline const t_time min_year = 1950;
		static inline const t_time max_year = 2100;
	private:
		static const inline t_time month_lengths[2][12] =
		{
			{31,28,31,30,31,30,31,31,30,31,30,31},
			{31,29,31,30,31,30,31,31,30,31,30,31},
		};
		static bool is_leap_year(t_time year);
		bool is_valid_timepoint();
		void validate();
	};
}
