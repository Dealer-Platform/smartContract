

ACTION reporting::verify(uint64_t itemKey, name voter, bool accept, float rating){
	require_auth(voter);

	// find row in voteassign table
	int key = -1;
	for(auto& row : _voteassign) { 
		if(row.itemKey == itemKey && row.voter == voter){
			key = row.key;
		}
	}
	check(key != -1, "voting not available" );


	//change voteassign record
	auto currVote = _voteassign.find(key);
	_voteassign.modify(currVote, _self, [&]( auto& row ) { 
		row.done = true;
		row.timestamp = eosio::current_time_point();
		row.rating = rating; 
		row.approved = accept;	
	});

	auto item = _items.find(itemKey);
	_items.modify(item, _self, [&]( auto& row ) { 
		if(accept){
			row.accepts++;
		}
		row.votes++;
	});

	payvoterescrow(itemKey, item->reward);
}
//pays out escrow for voter if incident is fully voted
void reporting::payvoterescrow(uint64_t itemKey, uint64_t reward){
	
	vector<eosio::name> verifier; 
	for(auto& row : _voteassign) { 
	  if(row.itemKey == itemKey){
		  if(row.done == 1){
			  verifier.push_back(row.voter);
		  }
	  }	  
	}
	
		//fill escrow for all voters of this item
	if(verifier.size() >= votercount){
		 for(auto& v : verifier) {
			_users.modify(_users.find(v.value), _self, [&]( auto& row ) { 
				row.escrow = row.escrow - reward; 
				row.balance = row.balance + reward;
			});
		}
	}
}



void reporting::assignverifier(uint64_t itemKey, uint64_t reward) {    

auto item = _items.find(itemKey);

vector<eosio::name> voters =  choosverifier(votercount, item->reporter);

  for(auto& voter : voters) {
    _voteassign.emplace(_self, [&]( auto& row ) { 
      row.key = _voteassign.available_primary_key();
      row.itemKey = itemKey;
      row.voter = voter;
	  row.done = false;
  });


	//set escrow for verifier
	_users.modify(_users.find(voter.value), _self, [&]( auto& row ) { 
		row.escrow = row.escrow + reward; 
	});
  }

}

ACTION reporting::reassvoter(uint64_t itemKey){
	//only contract owner
	require_auth( _self );


	auto item = _items.find(itemKey);
	check(!(item->votes >= votercount), "already verified" );

	vector<uint64_t> idleverifier; 
	vector<eosio::name> finishedverifier; 
	vector<eosio::name> idlenames; 

	//find idle verifiers
	for(auto& row : _voteassign) { 
		if(row.itemKey == itemKey){
			if(row.done == 0){
				idleverifier.push_back(row.key);
				idlenames.push_back(row.voter);
			}else{
				finishedverifier.push_back(row.voter);	
			}
		}
	}

	//find replacement candidates
	 vector<eosio::name> replacecandidate; 
	for(auto& row : _users) { 
		//only verifier, not the reporter himself
		if(row.verifier == 1 && item->reporter != row.user){
			//dont choose already assigned verifier
			if (!(std::find(finishedverifier.begin(), finishedverifier.end(), row.user) != finishedverifier.end())){
				//dont choose one of the current verifiers
				if (!(std::find(idlenames.begin(), idlenames.end(), row.user) != idlenames.end())){
				replacecandidate.push_back(row.user);
				}
			}
		}
	}

	//replace idle voters
	for (int i = 0; i < idleverifier.size(); i++) {
		//random voter from candidates
	int rnd = random(replacecandidate.size());
	//replace
	_voteassign.modify(_voteassign.find(idleverifier[i]), _self, [&]( auto& row ) { 
		row.done = false;
		row.voter = replacecandidate[i];	
	});
	//trim candidates
	replacecandidate.erase(replacecandidate.begin()+rnd);
	}

  
print("test");

}



vector<eosio::name> reporting::choosverifier(int count, name reporter){
   	 vector<eosio::name> verifier; 
	 vector<eosio::name> chosenVerifier; 

	for(auto& row : _users) { 
		if(row.verifier == 1 && reporter != row.user){
			verifier.push_back(row.user);
		}
	}

	//choose random verifier - according to count
	check(count <= verifier.size(), "not enough voters available" );

	for (int i = 0; i < count; i++) {
		int rnd = random(verifier.size());
		chosenVerifier.push_back(verifier[rnd]);
		verifier.erase(verifier.begin()+rnd);
	} //TODO
		
	return chosenVerifier;
}