ACTION reporting::init() {
  	int usercount = 0;
	for(auto& row : _users) { 
		usercount++;
	}

	if(usercount == 0){
	reguser("bsi"_n, "",false,"");
	reguser("peter"_n, "",true, "QmYZ6jNzSSXnWDVC4RCYN4RtMEMn3KpqmWYMpqRe76saE4");
    reguser("emma"_n, "",true, "QmUPbh3gQxvRteAyWGqh3ZB3ow2FtetZagbprTxFeX7gxW");
    reguser("isabelle"_n, "",true, "QmYE8srF3n9t5cN62QL8MkC1W6mGDqmbYhB1cMhgYbVUE4");
    reguser("bob"_n, "",true,"");
    reguser("mallory"_n, "",true,"");
	reguser("carl"_n, "",true,"");

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

	int reward = price * rewardpercent / 100;

	assignverifier(pk, reward);
}


