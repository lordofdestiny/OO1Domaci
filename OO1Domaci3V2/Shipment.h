#pragma once
#include <utility>
#include "Item.h"
#include "List.h"

namespace ndb {
	class ShipmentHandler;
	class Shipment {
	public:
		struct ShipmentDetails {
			double sprice = 0;
			unsigned shipping_time = 0;
		};
		friend class ShipmentHandler;
		using id_type = unsigned long long;
	private:
		static inline id_type _next_id = 0;
		id_type _id = _next_id++;
		Item _item;
		mutable bool _details_calculated = false;
		mutable ShipmentDetails _details{ 0, 0 };
		List<ShipmentHandler*> _handlers{};
	public:
		Shipment(Item const& item) :
			_item(item) {}
		Shipment(Shipment const& other) :
			_item(other._item),
			_handlers(other._handlers) {}
		Shipment(Shipment&& other) = delete;

		Shipment& operator=(Shipment const& rhs);
		Shipment& operator=(Shipment&& rhs) = delete;

		Shipment& operator+=(ShipmentHandler& handler);

		void calculate_details() const;

		Item const& get_item() const { return _item; }

		id_type get_id() const { return _id; }

		friend std::ostream& operator<<(std::ostream& os, Shipment const& shimpemnt);
		
		ShipmentDetails const& get_details() const;
	};
}
