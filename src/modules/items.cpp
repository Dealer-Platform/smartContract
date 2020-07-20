ACTION reporting::placeorder( name buyer, uint64_t itemKey ) {
	require_auth( buyer );
	auto it_buyer = _users.find(buyer.value);
	check( !(it_buyer == _users.end()) , "Please enrol first." );

	auto it_item = _items.find(itemKey);
	check( !(it_item == _items.end()), "No such item" );
	check( !(it_item->reporter == buyer), "You cannot buy your own item." );
	check( !(it_buyer->balance < it_item->price ), "you have insufficient balance for this order" );

	auto _item_index = _orders.get_index<name("itemkey")>();
	auto itr = _item_index.lower_bound(itemKey);
	auto itr_end = _item_index.upper_bound(itemKey);
	for (;itr != itr_end; itr++){
	    if(itr->buyer == buyer)
	        break;
	}
	check( itr == _item_index.end(), "That order was already placed." );

	_orders.emplace(_self, [&]( auto& row ) {
	  row.key = _orders.available_primary_key();
	  row.itemKey = itemKey;
	  row.seller = it_item->reporter;
	  row.buyer = buyer;
	  row.finished = 0;
	  row.timestamp = eosio::current_time_point();
	});

	if(it_item->price > 0) {
	  transferescrow(buyer, it_item->reporter, it_item->price);
	}
}

