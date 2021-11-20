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

	bool addBook(const Knjiga& knjiga);

	Biblioteka& operator+= (const Knjiga& knjiga) {
		addBook(knjiga);
		return *this;
	}

	const Knjiga* const getBookById(Knjiga::id_type id) const;

	const std::string& getName() const {
		return name;
	}
	count_type getBookCount() const {
		return book_count;
	}
	count_type getCapacity() const {
		return capacity;
	}

	friend std::ostream& operator<<(std::ostream& os, Biblioteka const& biblioteka);
private:
	void freeMemory();
	Knjiga** allocateNewMemory(count_type);
	void copyNewBooksFrom(Knjiga**);
	std::string name;
	count_type capacity;
	count_type book_count = 0;
	Knjiga** books = nullptr;
};

