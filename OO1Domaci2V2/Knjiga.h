#pragma once
#include <string>

class Knjiga
{
public:
	using id_type = unsigned long long;
	Knjiga(std::string title, std::string author) :
		title(title), author(author), id(next_id++) {}
	Knjiga(Knjiga const&) = delete;
	Knjiga(Knjiga&& rhs) noexcept :
		title(std::move(rhs.title)),
		author(std::move(rhs.author)),
		id(std::exchange(rhs.id, -1)) {}

	Knjiga& operator=(Knjiga const&) = delete;
	Knjiga& operator=(Knjiga&&) noexcept;

	std::string const& getName() const {
		return title;
	}
	std::string const& getAuthor() const {
		return author;
	}
	id_type getID() const {
		return id;
	}
	Knjiga* operator!() const {
		return new Knjiga(title, author);
	}
	friend std::ostream& operator<<(std::ostream& os, Knjiga const& knjiga);
private:
	static inline id_type next_id = 0;
	std::string title, author;
	id_type id;
};

