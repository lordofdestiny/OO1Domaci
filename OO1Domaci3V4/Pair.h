#ifndef PATH_H
#define PATH_H

#include <ostream>
#include <utility>

namespace ndb {
	template<class Type>
	class Pair {
		Type* _first{};
		Type* _second{};
	public:
		Pair() = default;
		Pair(Type* ptr1, Type* ptr2) :
			_first(ptr1), _second(ptr2) {}
		Pair(Pair const& other) = default;
		Pair(Pair&& other) noexcept :
			_first(std::exchange(other._first, nullptr)),
			_second(std::exchange(other._second, nullptr)) {}

		Pair& operator=(Pair const& rhs) {
			if (this != &rhs) {
				_first == rhs._first;
				_second = rhs._second;
			}
			return *this;
		}

		Pair& operator=(Pair&& rhs) noexcept{
			if (this != &rhs) {
				_first == std::exchange(rhs._first, nullptr);
				_second = std::exchange(rhs._second, nullptr);
			}
			return *this;
		}

		/* Returns first pointer of pair */
		Type* get_first() { return _first; }
		Type const* const get_first() const { return _first; }

		/* Returns second pointer of pair */
		Type* get_second() { return _second; }
		Type const* const get_second() const { return _second; }

		/* Sets first pointer of pair*/
		Pair& set_first(Type* ptr) {
			_first = ptr;
			return *this;
		}

		/* Sets second pointer of pair */
		Pair& set_second(Type* ptr) {
			_second = ptr;
			return *this;
		}

		friend bool operator==(Pair const& p1, Pair const& p2) {
			return *p1.first == *p2.first && *p1._second == *p2._second;
		}

		friend std::ostream& operator<<(std::ostream& os, Pair const& pair) {
			os << "(";
			if (pair._first != nullptr) {
				os << *pair._first;
			}
			else os << "nullptr";
			os << ", ";
			if (pair._second != nullptr) {
				os << *pair._second;
			}
			else os << "nullptr";
			return os << ")";
		}

		friend void swap(Pair& one, Pair& two) {
			std::swap(one._first, two._first);
			std::swap(one._second, two._second);
		}
	};
}

#endif