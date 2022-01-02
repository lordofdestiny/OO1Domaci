#pragma once
#include "ListExceptions.h"
#include "ListIterators.h"

template<class T>
class List {
public:
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using iterator = ListIterator<typename List<T>>;
	using const_iterator = ConstListIterator<typename List<T>>;
	friend class iterator;
	friend class const_iterator;
	struct Node
	{
		value_type data;
		Node* next;
		Node(const_reference data, Node* next = nullptr) :
			data(data), next(next) {}
	};
	using NodePointer = Node*;
private:
	NodePointer _begin = nullptr;
	NodePointer _end = nullptr;
	std::size_t _size = 0;
public:
	List() = default;
	List(List const& other) :
		_begin(List::copy_list(other)),
		_end(find_end(_begin)),
		_size(other._size) {}

	List(List&& other) noexcept :
		_begin(std::exchange(other._begin, nullptr)),
		_end(std::exchange(other._end, nullptr)),
		_size(std::exchange(other._size,0)) {}

	List& operator=(List const& rhs) {
		if (this != &rhs) {
			auto newData = copy_list(rhs);

			delete_list();

			_begin = newData;
			_end = find_end(_begin);
			_size = rhs._size;
		}
		return *this;
	}

	List& operator=(List&& rhs) noexcept {
		if (this != &rhs) {
			delete_list();

			_begin = std::exchange(rhs._begin,nullptr);
			_end = std::exchange(rhs._end, nullptr);
			_size = std::exchange(rhs._size, 0);
		}
		return *this;
	}

	~List() {
		delete_list();
	}

	bool empty() const {
		return _begin == nullptr;
	}

	std::size_t size() const {
		return _size;
	}

	iterator getIterator() {
		return iterator(*this);
	}

	const_iterator getIterator() const {
		return const_iterator(*this);
	}

	const_iterator getConstIterator() const {
		return const_iterator(*this);
	}

	List& append(const_reference value) {
		NodePointer newNode = new Node(value);
		if (_begin == nullptr) {
			_begin = newNode;
		}
		else {
			_end->next = newNode;
		}
		_end = newNode;
		_size += 1;
		return *this;
	}
private:
	static NodePointer copy_list(List const& other) {
		NodePointer temp = other._begin;
		NodePointer start = nullptr;
		NodePointer end = nullptr;
		while (temp != nullptr) {
			NodePointer copy = new Node(*temp);
			if (start == nullptr) {
				start = copy;
			}
			else {
				end->next = copy;
			}
			end = copy;
			temp = temp->next;
		}
		return start;
	}
	static NodePointer find_end(NodePointer begin) {
		if (begin == nullptr) return nullptr;
		if (begin->next == nullptr) return begin;
		NodePointer prev = nullptr, tmp = begin;
		while (tmp != nullptr) {
			prev = std::exchange(tmp, tmp->next);
		}
		return prev;
	}
	void delete_list() {
		while (_begin != nullptr) {
			delete std::exchange(_begin, _begin->next);
		}
		_end = nullptr;
		_size = 0;
	}
};
