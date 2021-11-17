#pragma once
#include <string>

class Knjiga
{
public:
	using id_type = unsigned long long;
	Knjiga(std::string title, std::string author) :
		title(title), author(author), id(next_id++) {}
	Knjiga(Knjiga const&) = delete;
	Knjiga(Knjiga&&) noexcept;
	Knjiga& operator=(Knjiga const&) = delete;
	Knjiga& operator=(Knjiga&&) noexcept;
	const std::string& getName() const {
		return title;
	}
	const std::string& getAuthor() const {
		return author;
	}
	id_type getID() const {
		return id;
	}
	Knjiga* operator!() const {
		return new Knjiga(this->title, this->author);
	}
	friend std::ostream& operator<<(std::ostream& os, Knjiga const& knjiga);
private:
	static inline id_type next_id = 0;
	std::string title, author;
	id_type id;
};

