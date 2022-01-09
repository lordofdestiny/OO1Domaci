#ifndef EXCPET_H
#define EXCPET_H

#include <exception>
#include <stdexcept>

namespace ndb {
	struct EListIndexOutOfRange : std::out_of_range {
		EListIndexOutOfRange() :
			std::out_of_range("List index out of range") {};
	};
	
	struct EPathContainsPoint : std::runtime_error {
		EPathContainsPoint() :
			std::runtime_error("Cannot add point. Path already contains it") {};
	};
}

#endif