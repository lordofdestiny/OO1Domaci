#include "Vehicle.h"

namespace ndb {
	double Vehicle::get_transport_price(Path const& path) const{
		return get_starting_price() + path.get_length() * _price_per_unit;
	}

	double Vehicle::get_starting_price() const {
		return _get_starting_price;
	}

	std::ostream& Vehicle::print(std::ostream& os) const {
		return os << _model;
	}

	std::ostream& operator<<(std::ostream& os, Vehicle const& vehicle) {
		return vehicle.print(os);
	}
}