#pragma once
#include <cstddef>

namespace ndb {
	template<char sep = '-', std::size_t size = 50, bool new_line = true>
	constexpr std::ostream& output_separator(std::ostream& os) {
		if constexpr (new_line) {
			return os << std::string(size, sep) << '\n';
		}
		else {
			return os << std::string(size, sep);

		}
	}
	template<std::size_t size>
	auto dash_separator = output_separator<'-', size>;
	template<std::size_t size>
	auto star_separator = output_separator<'*', size>;
	template<std::size_t size>
	auto ring_separator = output_separator<'o', size>;
	template<std::size_t size>
	auto cross_separator = output_separator<'+', size>;


	auto dsep = dash_separator<50>;
	auto ssep = star_separator<50>;
	auto rsep = ring_separator<50>;
	auto csep = cross_separator<50>;
}