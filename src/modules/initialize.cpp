ACTION reporting::init() {
  	int usercount = 0;
	for(auto& row : _users) { 
		usercount++;
	}

	if(usercount == 0){
	reguser("peter"_n, "",true);
    reguser("emma"_n, "",true);
    reguser("isabelle"_n, "",true);
    reguser("validator1"_n, "",true);
    reguser("validator2"_n, "",true);
	reguser("validator3"_n, "",true);
	}
}

void reporting::insertitem(name reporter, string hash, int price, string description, string title, bool sale, bool report){
	require_auth( _self );

		int pk =  _items.available_primary_key();

		_items.emplace(_self, [&]( auto& row ) { 
			row.key = pk;
			row.reporter = reporter;
			row.hash = hash;
			row.price = price;
			row.description = description;
			row.title = title;
			row.sale = sale;
			row.report = report;
		});

	assignverifier(pk);
}


