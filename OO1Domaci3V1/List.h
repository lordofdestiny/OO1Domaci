#pragma once
#include "Exceptions.h"
#include <iostream>
#include <utility>
#include <functional>

namespace ndb {
	template<class T>
	class List {
	public:
		using value_type = T;
		using reference = T&;
		using const_reference = const T&;
	private:
		struct Node {
			value_type data;
			Node* next = nullptr;
		};
		using NodePtr = Node*;
		NodePtr _head = nullptr, _tail = nullptr;
		mutable NodePtr _curr = nullptr, _prev = nullptr;
		std::size_t _size = 0;
	public:
		List() = default;
		List(List const& other) {
			copy_list(other);
		}

		List(List&& other) noexcept {
			move_list(other);
		}

		List& operator=(List const& rhs) {
			if (this != &rhs) {
				free_list();
				copy_list(rhs);
				_curr = _prev = nullptr;
			}
			return *this;
		}

		List& operator=(List&& rhs) noexcept {
			if (this != &rhs) {
				free_list();
				move_list(rhs);
				_curr = _prev = nullptr;
			}
			return *this;
		}

		virtual ~List() {
			free_list();
		}

		bool empty() const {
			return _head == nullptr;
		}

		std::size_t size() const {
			return _size;
		}

		List& push_back(const_reference value) {
			_prev = _tail;
			_curr = _tail = (_head == nullptr ? _head : _tail->next) = new Node{ value };
			++_size;
			return *this;
		}

		List& push_front(const_reference value) {
			_head = new Node{ value, _head };
			if (_head->next == nullptr) {
				_tail = _head;
			}
			_prev = nullptr;
			_curr = _head;
			++_size;
			return *this;
		}

		/*List& insert_before_current(const_reference value) {
			if (_curr == nullptr) {
				return this->push_back(value);
			}
			if (_curr == _head) {
				return this->push_front(value);
			}
			_curr = _prev->next = new Node{ value, _prev->next };
			++_size;
			return *this;
		}*/

		/*List& insert_after_current(const_reference value) {
			if (_curr == nullptr) throw ListIndexOutOfRange();
			if (_curr == _head) {
				return this->push_back(value);
			}
			_curr->next = new Node{ value, _curr->next };
			_prev = std::exchange(_curr, _curr->next);
			if (_prev == _tail) {
				_tail = _curr;
			}
			++_size;
			return *this;
		}*/

		/*bool seek_from_current(std::function<bool(const_reference)> const& f) const {
			if (_curr == nullptr) throw ListIndexOutOfRange();
			NodePtr prev = _prev, curr = _curr;

			bool found = false;
			while (is_valid() && !found) {
				if (!(found = f(get_current()))) {
					seek_next();
				}
			}

			if (!found || !is_valid()) {
				_prev = prev;
				_curr = curr;
			}

			return found;
		}*/

		List& to_begin() {
			return const_cast<List&>(const_cast<const List&>(*this).to_begin());
		}

		const List& to_begin() const {
			_curr = _head;
			_prev = nullptr;
			return *this;
		}

		List& seek_next() {
			return const_cast<List&>(const_cast<const List&>(*this).seek_next());
		}

		const List& seek_next() const {
			if (_curr != nullptr) {
				_prev = std::exchange(_curr, _curr->next);
			}
			return *this;
		}

		bool is_valid() const {
			return _curr != nullptr;
		}

		reference get_current() {
			return const_cast<reference>(const_cast<List const&>(*this).get_current());
		}

		const_reference get_current() const {
			if (_curr == nullptr) throw EListIndexOutOfRange();
			return _curr->data;
		}

		List& remove_current() {
			if (_curr == nullptr) throw EListIndexOutOfRange();
			NodePtr to_free = _curr;
			_curr = (_curr == _head ? _head : _prev->next) = _curr->next;
			if (_curr == nullptr) _tail = _prev;
			delete to_free;
			--_size;
			return *this;
		}


		friend std::ostream& print(List const& list, bool from_current = true,
			bool new_line = true, std::ostream& os = std::cout) {
			NodePtr prev = list._prev, curr = list._curr;
			if (!from_current) {
				list.to_begin();
			}
			while (list.is_valid()) {
				os << list.get_current() << ' ';
				list.seek_next();
			}
			if (new_line) {
				os << '\n';
			}
			list._prev = prev;
			list._curr = curr;
			return os;
		}

		friend std::ostream& operator<<(std::ostream& os, List const& list) {
			return print(list, false, false);
		}
	private:
		void copy_list(List const& other) {
			NodePtr temp = other._head;
			NodePtr head = nullptr, tail = nullptr;
			while (temp != nullptr) {
				tail = (tail == nullptr ? head : tail->next) = new Node{ *temp };
				temp = temp->next;
			}
			_head = head;
			_tail = tail;
			_size = other._size;
		}
		void move_list(List& other) noexcept {
			_head = std::exchange(other._head, nullptr);
			_tail = std::exchange(other._tail, nullptr);
			_size = std::exchange(other._size, 0);
		}
		void free_list() {
			while (_head != nullptr) {
				delete std::exchange(_head, _head->next);
			}
			_tail = nullptr;
			_size = 0;
		}
	};
}