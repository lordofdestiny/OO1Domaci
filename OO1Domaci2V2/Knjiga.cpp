#include "Knjiga.h"
#include <iostream>

Knjiga::Knjiga(Knjiga&& rhs) noexcept :
	title(std::move(rhs.title)),
	author(std::move(rhs.author)),
	id(std::exchange(rhs.id, -1)) {}


Knjiga& Knjiga::operator=(Knjiga&& other) noexcept {
	if (this != &other) {
		title = std::move(other.title);
		author = std::move(other.author);
		id = std::exchange(other.id, -1);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, Knjiga const& knjiga) {
	return os << "KNJIGA " << knjiga.id << " : " << knjiga.title << " - " << knjiga.author;
}
