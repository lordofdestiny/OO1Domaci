#pragma once
#include "ShipmentHandler.h"
#include "Exceptions.h"
#include "List.h"

namespace ndb {
	class Vendor : public ShipmentHandler {
		struct CatalogueItem {
			Item item;
			double margin;
			short delivery_time;
		};
		std::string _name;
		List<CatalogueItem> _catalogue;
	public:
		Vendor(std::string name) : _name(name) {}

		void expand_catalogue(Item const& item, double margin, short delivery_time) {
			_catalogue += {item, margin, delivery_time};
		}

		std::string const& get_name() const {
			return _name;
		}
	protected:
		void process_shipment(Shipment const& shipment) const override;
	private:
		CatalogueItem const& find_item(Item const& item) const;
	};
}

