#include <iostream>
#include <random>
#include "Path.h"
#include "Vehicle.h"
#include "Exceptions.h"

ndb::Path generate_path(std::size_t length) {
	using ndb::Point, ndb::Path;
	std::random_device r;
	std::default_random_engine engine(r());
	std::uniform_int_distribution<long> uniform_dist(-10, 10);
	Path path;
	for (std::size_t i = 0; i < length; ++i) {
		bool generated = false;
		while (!generated) {
			try {
				path += {uniform_dist(engine), uniform_dist(engine)};
				generated = true;
			}
			catch (ndb::EPathContainsPoint const&) {
				generated = false;
			}
		}
	}

	return path;
}

int main() {
	using ndb::Path, ndb::Vehicle;
	Path path = generate_path(2);
	std::cout << "Path length: " << path.get_length() << '\n';
	std::cout << "Path length: " << path.get_length() << '\n';
	std::cout << path << '\n';
	Vehicle car("Honda Civic");
	double price = car.get_transport_price(path);
	std::cout << "Transport price: " << car.get_transport_price(path) << '\n';
}
