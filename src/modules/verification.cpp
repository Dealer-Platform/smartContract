

ACTION reporting::verify(uint64_t itemKey, name voter, bool accept, uint64_t rating){
	require_auth(voter);

	int key = -1;
	for(auto& row : _voteassign) { 
		if(row.itemKey == itemKey && row.voter == voter){
			key = row.key;
		}
	}

	check(key != -1, "voting not available" );

	auto currVote = _voteassign.find(key);

	_voteassign.modify(currVote, _self, [&]( auto& row ) { 
		row.done = true;
		row.timestamp = eosio::current_time_point();
		row.rating = rating; 
		row.approved = accept;	
	});


	_items.modify(_items.find(itemKey), _self, [&]( auto& row ) { 
		if(accept){
			row.accepts++;
		}
		row.votes++;
	});

}



void reporting::assignverifier(uint64_t itemKey) {    

auto item = _items.find(itemKey);
vector<eosio::name> voters =  choosverifier(3, item->reporter);

  for(auto& voter : voters) {
    _voteassign.emplace(_self, [&]( auto& row ) { 
      row.key = _voteassign.available_primary_key();
      row.itemKey = itemKey;
      row.voter = voter;
	  row.done = false;
  });
}
}


vector<eosio::name> reporting::choosverifier(int count, name reporter){
   	 vector<eosio::name> verifier; 
	 vector<eosio::name> chosenVerifier; 
	//user_t users( _self, _self.value );
	for(auto& row : _users) { 
		if(row.verifier == 1 && reporter != row.user){
			verifier.push_back(row.user);
		}
	}
	//choose random verifier - according to count
	for (int i = 0; i < count; i++) {
		int rnd = random(verifier.size());
		chosenVerifier.push_back(verifier[rnd]);
		verifier.erase(verifier.begin()+rnd);
	}
	return chosenVerifier;
}