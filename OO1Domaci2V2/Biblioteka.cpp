#include "Biblioteka.h"
#include <iostream>

Biblioteka::Biblioteka(std::string name, count_type capacity) :
	name(name), capacity(capacity),
	books(allocateNewMemory(capacity)) {}

Biblioteka::Biblioteka(Biblioteka const& rhs) :
	name(rhs.name), capacity(rhs.capacity),
	book_count(rhs.book_count),
	books(allocateNewMemory(rhs.capacity)) {
	copyBooksFrom(rhs.books);
}

Biblioteka::Biblioteka(Biblioteka&& rhs) noexcept :
	name(std::move(rhs.name)),
	capacity(std::exchange(rhs.capacity, 0)),
	book_count(std::exchange(rhs.book_count, 0)),
	books(std::exchange(rhs.books, nullptr)) {}

Biblioteka& Biblioteka::operator=(Biblioteka const& other) {
	if (this != &other) {
		Knjiga** newMemory = allocateNewMemory(other.capacity);

		freeMemory();

		name = other.name;
		capacity = other.capacity;
		book_count = other.book_count;
		books = newMemory;
		copyBooksFrom(other.books);
	}
	return *this;
}

Biblioteka& Biblioteka::operator=(Biblioteka&& other) noexcept {
	if (this != &other) {
		freeMemory();
		name = std::move(other.name);
		capacity = std::exchange(other.capacity, 0);
		book_count = std::exchange(other.book_count, 0);
		books = std::exchange(other.books, nullptr);
	}
	return *this;
}

Biblioteka::~Biblioteka() {
	freeMemory();
}

void Biblioteka::freeMemory() {
	for (count_type i = 0; i < book_count; i++) {
		delete books[i];
	}
	delete[] books;
}

const Knjiga* Biblioteka::getBookById(Knjiga::id_type id) const {
	Knjiga* result = nullptr;
	for (count_type i = 0; i < book_count; i++) {
		if (books[i]->getID() == id) {
			result = books[i];
			break;
		}
	}
	return result;
}

bool Biblioteka::addBook(const Knjiga& knjiga) {
	bool inserted = book_count < capacity;
	if (book_count < capacity) {
		books[book_count++] = !knjiga;
	}
	return inserted;
}

Knjiga** Biblioteka::allocateNewMemory(count_type size) {
	return new Knjiga * [size];
}

void Biblioteka::copyBooksFrom(Knjiga** books) {
	if (capacity > book_count) {
		for (count_type i = 0; i < book_count; i++) {
			this->books[i] = !*books[i];
		}
	}
}

std::ostream& operator<<(std::ostream& os, Biblioteka const& biblioteka) {
	os << "BIBLIOTEKA " << biblioteka.name;
	os << " " << biblioteka.book_count << '/' << biblioteka.capacity << '\n';
	for (Biblioteka::count_type i = 0; i < biblioteka.book_count; i++) {
		os << *biblioteka.books[i] << '\n';
	}
	return os;
}
