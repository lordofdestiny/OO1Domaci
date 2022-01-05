#pragma once
#include "Shipment.h"

namespace ndb {
	class ShipmentHandler {
	public:
		ShipmentHandler() = default;
		ShipmentHandler(ShipmentHandler const&) = default;
		ShipmentHandler(ShipmentHandler&&) = default;
		ShipmentHandler& operator=(ShipmentHandler const&) = default;
		ShipmentHandler& operator=(ShipmentHandler&&) = default;
		virtual ~ShipmentHandler() = default;
		virtual void process_shipment(Shipment& shipment) const = 0;
	protected:
		static Shipment::ShipmentDetails& get_shipment_details(Shipment& shipment) {
			return shipment._details;
		}
	};
}