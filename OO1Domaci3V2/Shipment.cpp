#include "Shipment.h"
#include "ShipmentHandler.h"

namespace ndb {
	Shipment::Shipment(Shipment const& other) :
		_item(other._item),
		_handlers(other._handlers) {}
	Shipment::Shipment(Shipment&& other) noexcept :
		_id(other._id),
		_item(std::move(other._item)) {}

	Shipment& Shipment::operator=(Shipment const& rhs) {
		_id = _next_id++;
		_details = { 0, 0 };
		_details_calculated = false;
		_item = rhs._item;
		_handlers = rhs._handlers;
		return *this;
	}

	Shipment& Shipment::operator=(Shipment&& rhs) noexcept {
		_id = rhs._id;
		_details = { 0, 0 };
		_details_calculated = false;
		_item = std::move(rhs._item);
		_handlers = std::move(rhs._handlers);
		return *this;
	}

	Shipment& Shipment::operator+=(ShipmentHandler& handler) {
		if (_details_calculated) {
			throw EShipmentDetailsCalculated();
		}
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