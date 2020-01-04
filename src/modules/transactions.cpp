	void reporting::transferescrow(name from, name to, uint64_t reward){
		auto it_from = _users.find(from.value); 
		auto it_to = _users.find(to.value);
	
		check( it_from->balance - reward >= 0 , "Sender has not enough token.");

		_users.modify(it_from, _self, [&]( auto& row ) { 
			if(row.balance - reward >= 0){
				row.balance = row.balance - reward; 
			}else{
				row.balance = 0;
			}
		});

		_users.modify(it_to, _self, [&]( auto& row ) { 
			row.escrow = row.escrow + reward; 
		});
	}

    void reporting::addescrow(name user, uint64_t reward){
		_users.modify(_users.find(user.value), _self, [&]( auto& row ) { 
			row.escrow = row.escrow + reward; 
		});
	}

    void reporting::payescrow(name user, uint64_t reward){
		_users.modify(_users.find(user.value), _self, [&]( auto& row ) { 
			if(row.escrow - reward >= 0){
				row.escrow = row.escrow - reward; 
			}else{
				row.escrow = 0;
			}
			row.balance = row.balance + reward; 
		});
	}
