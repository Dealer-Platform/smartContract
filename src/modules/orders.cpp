ACTION reporting::keyupload(uint64_t orderno){
    auto it_order = _orders.find(orderno);

    require_auth( it_order->seller);


    _orders.modify(it_order, _self, [&]( auto& row ) { 
		row.bkeyupload = true;
	});

}
//download failed -> open dispute
ACTION reporting::opendispute(name user, uint64_t orderno){
    auto it_order = _orders.find(orderno);
    require_auth( it_order->buyer);

    _orders.modify(it_order, _self, [&]( auto& row ) { 
		  row.dispute = true;
	});

}

//temporarily close dispute (try next download)
ACTION reporting::closedispute(name user, uint64_t orderno){
    auto it_order = _orders.find(orderno);
    require_auth( it_order->buyer);

    _orders.modify(it_order, _self, [&]( auto& row ) { 
		  row.dispute = false;
	});

}
//download succeeded, remove dispute, finish order, release escrow
ACTION reporting::finishorder(name user, uint64_t orderno){
    auto it_order = _orders.find(orderno);
    require_auth( it_order->buyer);

    auto it_item = _items.find(it_order->itemKey);

    _orders.modify(it_order, _self, [&]( auto& row ) { 
		  row.dispute = false;
          row.finished = true;
          row.timestamp = eosio::current_time_point(); 	
	});

    payescrow(it_order->seller, it_item->price);

}