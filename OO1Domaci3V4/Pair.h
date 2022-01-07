#pragma once
#include <ostream>
#include <utility>

namespace ndb {
	template<class Type1, class Type2>
	class Pair {
		Type1* _first;
		Type2* _second;
	public:
		Pair(Type1* ptr1, Type2* ptr2) :
			_first(ptr1), _second(ptr2) {}
		Pair(Pair const& other) = default;
		Pair(Pair&& other) noexcept:
			_first(std::exchange(other._first, nullptr)),
			_second(std::exchange(other._second, nullptr)) {}

		Type1* get_first() {
			return _first;
		}

		Type1 const* get_first() const {
			return _first;
		}

		Type2* get_second() {
			return _second;
		}

		Type2 const* get_second() const {
			return _second;
		}

		Pair& set_first(Type1* ptr) {
			_first = ptr;
			return *this;
		}

		Pair& set_second(Type2* ptr) {
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
			else {
				os << "nullptr";
			}
			os << ", ";
			if (pair._second != nullptr) {
				os << *pair._second;
			}
			else {
				os << "nullptr";
			}
			return os << ")";
		}

		friend void swap(Pair& one, Pair& two) {
			std::swap(one._first, two._first);
			std::swap(one._second, two._second);
		}

	};
}