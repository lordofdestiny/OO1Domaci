#include <iostream>
#include "List.h"

struct dummy {
	int i;
public:
	dummy(int i) : i(i) {}
	
	friend std::ostream& operator<<(std::ostream& os, dummy const& d) {
		return os << "D{" << d.i << '}';
	}
};

int main()
{
	List<dummy> list;
	list.append({ 1 }).append({ 2 });
	for (auto li = list.getIterator(); li.isValid(); ++li) {
		std::cout << *li << ' ';
	}
	std::cout << std::endl;
}