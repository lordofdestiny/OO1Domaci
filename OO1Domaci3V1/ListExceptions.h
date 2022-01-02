#pragma once
#include <stdexcept>

struct ListEmpty : std::runtime_error {
	ListEmpty() : runtime_error("Cannot access element because list is empty") {}
};

struct ListIteratorOutOfRange : std::out_of_range {
	ListIteratorOutOfRange() :
		std::out_of_range("Cannot access elemets that are out of range of the list") {}
};


