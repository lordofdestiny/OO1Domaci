#pragma once
#include <iostream>
#include <utility>
#include "Exceptions.h"

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
			}
			return *this;
		}

		List& operator=(List&& rhs) noexcept {
			if (this != &rhs) {
				free_list();
				move_list(rhs);
			}
			return *this;
		}

		~List() {
			free_list();
		}

		bool empty() const {
			return _head == nullptr;
		}

		std::size_t size() const {
			return _size;
		}

		List& operator+=(const_reference value) {
			_tail = (_head == nullptr ? _head : _tail->next) = new Node{ value };
			++_size;
			return *this;
		}

		reference operator[](std::size_t index) {
			return const_cast<reference>(const_cast<List const&>(*this)[index]);
		}

		const_reference operator[](std::size_t index) const {
			NodePtr temp = _head;
			while (index > 0 && temp != nullptr) {
				--index;
				temp = temp->next;
			}
			if (temp == nullptr || index < 0) {
				throw EListIndexOutOfRange();
			}

			return temp->data;
		}

		List& remove_at(std::size_t index) {
			NodePtr prev = nullptr, curr = _head;
			while (index > 0 || index >= _size) {
				--index;
				prev = std::exchange(curr, curr->next);
			}
			if (curr == nullptr || index < 0) {
				throw EListIndexOutOfRange();
			}
			NodePtr to_delete = curr;
			curr = (curr == _head ? _head : prev->next) = curr->next;
			if (curr == nullptr) _tail = prev;
			delete to_delete;
			--_size;
			return *this;
		}

		std::ostream& print(bool new_line = true, std::ostream& os = std::cout) {
			if (_size == 0) return os << "[empty]";
			NodePtr temp = _head;
			while (temp != nullptr) {
				os << temp->data << ' ';
				temp = temp->next;
			}
			return new_line ? os << '\n' : os;
		}

		friend std::ostream& operator<<(std::ostream& os, List const& list) {
			return print(list, false);
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