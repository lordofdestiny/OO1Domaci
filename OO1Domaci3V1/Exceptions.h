#pragma once
#include <stdexcept>

namespace ndb {
	struct ListIteratorOutOfRange : std::out_of_range {
		ListIteratorOutOfRange() :
			std::out_of_range("Cannot access elemets that are out of range of the list") {}
	};

	struct InvalidTimepoint : std::domain_error {
		InvalidTimepoint() :
			std::domain_error("Cannot create Timepoint because one of parameters was invalid") {}
	};

	struct EMailAlreadySent : std::logic_error {
		EMailAlreadySent() :
			std::logic_error("Cannot send an email that has already been sent!") {		}
	};
}