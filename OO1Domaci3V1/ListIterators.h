#pragma once

template<class ListType>
class ListIterator {
public:
	using value_type = typename ListType::value_type;
	using reference = value_type&;
	using const_reference = value_type const&;
	using Node = typename ListType::Node;
	using NodePointer = Node*;
private:
	NodePointer _node;
	ListType& _list;
	friend typename ListType;
	ListIterator(ListType& list) :
		_list(list), _node(list._begin) {}
public:
	ListIterator(ListIterator const&) = delete;
	ListIterator& operator = (ListIterator const&) = delete;
	value_type* operator->() const {
		if (this->_node == nullptr) throw ListIteratorOutOfRange();
		return &this->_node->data;
	}
	reference operator*() const {
		if (this->_node == nullptr) throw ListIteratorOutOfRange();
		return this->_node->data;
	}
	bool isValid() const {
		return this->_node != nullptr;
	}
	ListIterator& operator++() {
		this->_node = this->_node->next;
		return *this;
	}
};

template<class ListType>
class ConstListIterator {
public:
	using value_type = typename ListType::value_type;
	using reference = value_type&;
	using const_reference = value_type const&;
	using Node = typename ListType::Node;
	using NodePointer = Node*;
private:
	NodePointer _node;
	ListType const& _list;
	friend typename ListType;
	ConstListIterator(ListType const& list) :
		_list(list), _node(list._begin) {}
public:
	ConstListIterator(ConstListIterator const&) = delete;
	ConstListIterator& operator = (ConstListIterator const&) = delete;
	value_type const* operator->() const {
		if (_node == nullptr) throw ListIteratorOutOfRange();
		return &_node->data;
	}
	const_reference operator*() const {
		if (_node == nullptr) throw ListIteratorOutOfRange();
		return _node->data;
	}
	bool isValid() const {
		return _node != nullptr;
	}
	ConstListIterator& operator++() {
		_node = _node->next;
		return *this;
	}
};
