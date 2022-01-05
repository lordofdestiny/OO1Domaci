#include "Shipment.h"
#include "ShipmentHandler.h"

namespace ndb {
	Shipment& Shipment::operator=(Shipment const& rhs) {
		_details = { 0, 0 };
		_item = rhs._item;
		_handlers = rhs._handlers;
		return *this;
	}

	Shipment& Shipment::operator+=(ShipmentHandler& handler) {
		_handlers += &handler;
		return *this;
	}

	void Shipment::calculate_details() const {
		for (std::size_t i = 0; i < _handlers.size(); ++i) {
			_handlers[i]->process_shipment(*this);
		}
		_details_calculated = true;
	}

	Shipment::ShipmentDetails const& Shipment::get_details() const {
		if (!_details_calculated) {
			throw EShipmentDetailsNotCalculated();
		}
		return _details;
	}

	std::ostream& operator<<(std::ostream& os, Shipment const& shimpemnt) {
		return os << "Posiljka[" << shimpemnt._id << ", "
			<< shimpemnt._item.get_name() << "]";
	}
}