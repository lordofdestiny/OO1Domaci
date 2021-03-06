#pragma once
#include <string>
#include "Knjiga.h"

class Biblioteka
{
public:
	using count_type = unsigned long;
	Biblioteka(std::string name, count_type capacity);
	Biblioteka(Biblioteka const&);
	Biblioteka(Biblioteka&&) noexcept;
	Biblioteka& operator=(Biblioteka const&);
	Biblioteka& operator=(Biblioteka&&) noexcept;
	~Biblioteka();

	const std::string& getName() const {
		return name;
	}
	count_type getBookCount() const {
		return book_count;
	}
	count_type getCapacity() const {
		return capacity;
	}

	const Knjiga* getBookById(Knjiga::id_type id) const;

	Biblioteka& operator+=(const Knjiga& knjiga) {
		addBook(knjiga);
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, Biblioteka const& biblioteka);
private:
	bool addBook(const Knjiga& knjiga);
	void freeMemory();
	Knjiga** allocateNewMemory(count_type);
	void copyBooksFrom(Knjiga**);
	std::string name;
	count_type capacity;
	count_type book_count = 0;
	Knjiga** books = nullptr;
};

