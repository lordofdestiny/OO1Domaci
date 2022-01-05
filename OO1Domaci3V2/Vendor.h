#pragma once
#include "ShipmentHandler.h"
#include "Exceptions.h"
#include "List.h"

namespace ndb {
	class Vendor : public ShipmentHandler {
		friend class Shipment;
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
		void process_shipment(Shipment& shipment) const override {
			auto& shipment_details = get_shipment_details(shipment);
			auto const& [item, margin, delivery_time] = find_item(shipment.get_item());
			shipment_details.shipping_time += delivery_time;
			shipment_details.sprice += item.get_price() + margin;
		}
	private:
		CatalogueItem const& find_item(Item const& item) const {
			for (std::size_t i = 0; i < _catalogue.size(); i++) {
				if (item == _catalogue[i].item) {
					return _catalogue[i];
				}
			}
			throw EVendorItemMissing();
		}
	};
}

