ACTION reporting::clearall(){
	require_auth(_self);
	user_t users( _self, _self.value );
	auto itr = users.begin();
	while(itr != users.end()){
    	itr = users.erase(itr);
	}

	order_t orders( _self, _self.value );
	auto itr2 = orders.begin();
	while(itr2 != orders.end()){
    	itr2 = orders.erase(itr2);
	}

	item_t items( _self, _self.value );
	auto itr3 = items.begin();
	while(itr3 != items.end()){
    	itr3 = items.erase(itr3);
	}
	voteassign_t voteassign( _self, _self.value );
	auto itr4 = voteassign.begin();
	while(itr4 != voteassign.end()){
    	itr4 = voteassign.erase(itr4);
	}
}

ACTION reporting::init() {
  	int usercount = 0;
	for(auto& row : _users) { 
		usercount++;
	}

	if(usercount == 0){
	reguser("dealerbsiger"_n, "MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEA1OIupFdeYsxdSPgdHjpH\n4V1r9rkcHNGxHM3qXErHlrOpz30fo/n3tB8z12gLamYcTYhPDuea86lgXe0Sz5Ti\ngnCixDvxSdCgBw79w6Tm9IbwWAFdbnk5IGJnUOvSz3ib3foAxt3ycQMxmQXh2fA3\n5RaKAlFoqF2OK78J5XRzyf71sOcPOehn9WSXqnwpw7eJ\nPMEgA8G3T0+9YhPFu5Im\nYHfhGTvs0aVMJ0UiO7+7ARoOeaqctUcV2Tqm4drmNcFQAnb/xUisQtaQc3VvyitB\nVKCV3356WL02bKdiLFAPFeSJfV0tR9wGAGdqFCUkPdhPmjfc17ySEtHg3qL709hX\nOqHQb+PSpEhpQYxgayK440DDbqTxBzq+fgnUnm43gy8yu4ptH7G3miE1LJmsLV5M\n+PjwYMrjEnC/G020JjRtxSHQvXsJdQGQR9CW+tMT9m4yhO05uSpTUZ\nkII3XpiDYa\nJFINsxc3jZkHAGvZY/5tsEffT00+glYDUYSU3Lbdb31hriwJUkDFqSMg2hHF00wt\nz2FK/qeRcIZmT6OClE/1umghBIvKjFbMkws4x9QnvyFAMVIg+NId+2gw/7C//l31\nl1blwXp7aoPnARaUSQgl+mXVdqsVBDDvNSXHr5DgrcDMJjxYEmIU4FK5QW+Zcgl8\npXQf2DiwcbTRGJeuJrRsJhMCAwEAAQ==",true, "");
	reguser("dealerthomas"_n, "MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEA5VeQE4LiyanIoDVwvtuz\nJFgo4te1U9MDg5Xbb62zj8DFHBIYv1oT4pLwFB28hXvcpGdfQeUz5XFxcYCYGj/C\nV1uWEPq4fVq49KQphDUIw+IcVlMBP5oZOpzwXOwACpDOcWx2rp1Cb5Bh4y97lVBg\n2pJ/+AHGc00f1LNGh1sH+Vc2MA1cMxIo40ssGHhFQEB1\nrdI1aBKw7sUyMagOQqpS\nCtfEzk6/mvnclfxMLFheUoWJCG08jEC4SUThsQzMZex27Nuo8+H8MyMTXFDuPYcV\n68pM55XP5Ois32/ibfKKq1hRrhjlEaPi1G/3J7OX4eH6UfzT7J92J/36lR+nGc3j\ncmPBzQ8UQgxng2agyuLfLo8bMHllBfNsGS3db75c9umQnx6hvkh7TJ2Q+SLcmo0a\nkGOO1K4oiodqNjHgYPwqohcEkZpeunq4Q6x7GnTdzrT79aIQTN8+SH\nI8oupvQ8c4\npU1S34QQTiXK1cFxksbVgVbGto4p8yUAnK0Fu/hSH909EjukWcODJ0Z8hKRpAtta\nkcWLI42DAZwdMyrbPtNbfgcNZeU17E9hqhVak57lf2WM2ss2lhmyk87eaAuhKte0\nXD0ho3YckPoUq0oeGTUcRDxNbY56gt0yxhb1Oph/AOz9zd9YO1xbSIAgY1xu61Do\n8pMHCuurBJmpmKJ/+RekF4MCAwEAAQ==",true, "QmYZ6jNzSSXnWDVC4RCYN4RtMEMn3KpqmWYMpqRe76saE4");
    reguser("dealerdonald"_n, "MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEA3c44u0XYCj6s1aJ+y8yN\n/NqDiGpwEnkdzoiM2uUlVzxh21VohGjfkYFic3qrwEuSIUitPiUBjmudsmFRdyBs\njUii5wKIIN0UOG0wm8N2nzmX3briyGZ9Qotxfz/juc+9T3X6gm7ItVnhorKaFrAS\nKTMTSzosFoAWP/cAzT9RNcrPYQ/WHDtmxyIYudzrKP0B\n2NZ6syFfsNm49s8JPN3C\ngr8UGhMWjD3zLe/zPeSOe+pPbeTt8YqdXS7ZotXeJ4IFEiQSMRCViONfiNJbuihb\nmMaaosFxbEpR8gyrcG4bYU54aBHzTfdDEjMy6tdPmSm/chXfVxiMUtb09nCrqDTw\nvBjsCGG8Ldrv5X66CvgkB2W6HTJhMiD8LYCe3gTvIWueYkDgJ/C0Bf6i5jk7Ub1n\nZPDd0YzrJIiL710GB2vQltIokKLF787xZorJRnKGuf70igsGeIFRjE\nzaNBU0fepY\noazI1n5VUIt95DFATOq3RjI7WouGwXHMGqT0F0aE+t8dyQSmCpbNBm6XSyD0hr3w\nDfgW+AeNIpr2I1CdViU+jjsPise2xOQkpJihDhQP54X9nu16PdcFnemwVePsL3E8\nRKcwPRPMwaW2/KhIFnv3GoBu7mArI0xFJLtQdoNdUGKkzMg7Xo/QTXXTePFljAhl\nXJPZJFR9hmVLDsrC6oAJ6G0CAwEAAQ==",true, "QmUPbh3gQxvRteAyWGqh3ZB3ow2FtetZagbprTxFeX7gxW");
    reguser("dealerhelena"_n, "MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEArB488qKqhnQUlufw8xde\nnJHIyn0hXKNnjAj8l5N9a9+vK2EH1aAGT2aRCEJz2JmaLoCy2C1YoXvWlktISHKB\nTwnHhOInExLbDaU/WG0CHTU6l2rYzsb8kVAXsxz/zxMvXJjS9jELvtQfmT87/pMD\n0D94m14y6/2zMYCOr5a5wJmNZc4JtQQSWgi++hpuKqfI\n1TPCJLEmFs/lGzW43NFi\n0TpebY56uIpuGUikJ1gc1nX2uiFJG1dCA5mbCglj/RBRyrrPWomZNEty050LxDOq\nAliDqrCEoR8lbFv5f+Q/EJsHZD7P7dyZhJkQxK56W7927OdFLDWMWplbXif5RRNE\nHie0gEY425hdxveqPhQ18gLofvAI25CfPQbVPj8U4XgCoSCu4l2f2M0Xts9Z8yf5\ngGvczhY3lnzllreM557xGnXFwrIKaNPSygJbUd0KqN14kP/ySqES2C\nLacqRSSZSk\nRkvVPcqJ7V+4Lwz12PXb37CH5m5OFG77tA9bG55nLkBSzvuiLaE+r0F4LMfo5GGN\nQmuIawcHdhf05C2ZzlLkMmmq+OmEKpKfrhmfPJEe9emjKpXgT79xyUMQS5giBZKp\nKJ4z24clje6SciwMZIEoY0y+vPYe1vzhICjZ3NDi+hAWgrF+L7TJf86gS6c6u2u2\nO+PPjZWCDNv2g15fSFWID7kCAwEAAQ==",true, "QmYE8srF3n9t5cN62QL8MkC1W6mGDqmbYhB1cMhgYbVUE4");
    reguser("dealernadine"_n, "MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEArB488qKqhnQUlufw8xde\nnJHIyn0hXKNnjAj8l5N9a9+vK2EH1aAGT2aRCEJz2JmaLoCy2C1YoXvWlktISHKB\nTwnHhOInExLbDaU/WG0CHTU6l2rYzsb8kVAXsxz/zxMvXJjS9jELvtQfmT87/pMD\n0D94m14y6/2zMYCOr5a5wJmNZc4JtQQSWgi++hpuKqfI\n1TPCJLEmFs/lGzW43NFi\n0TpebY56uIpuGUikJ1gc1nX2uiFJG1dCA5mbCglj/RBRyrrPWomZNEty050LxDOq\nAliDqrCEoR8lbFv5f+Q/EJsHZD7P7dyZhJkQxK56W7927OdFLDWMWplbXif5RRNE\nHie0gEY425hdxveqPhQ18gLofvAI25CfPQbVPj8U4XgCoSCu4l2f2M0Xts9Z8yf5\ngGvczhY3lnzllreM557xGnXFwrIKaNPSygJbUd0KqN14kP/ySqES2C\nLacqRSSZSk\nRkvVPcqJ7V+4Lwz12PXb37CH5m5OFG77tA9bG55nLkBSzvuiLaE+r0F4LMfo5GGN\nQmuIawcHdhf05C2ZzlLkMmmq+OmEKpKfrhmfPJEe9emjKpXgT79xyUMQS5giBZKp\nKJ4z24clje6SciwMZIEoY0y+vPYe1vzhICjZ3NDi+hAWgrF+L7TJf86gS6c6u2u2\nO+PPjZWCDNv2g15fSFWID7kCAwEAAQ==",true,"QmSiogXzJpGenLurt3ofh33SBfPxc4sgwjoTteaTrVeGEs");
	reguser("dealerstefan"_n, "MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEA25CA8aDWxPhNHCoKFXvG\n97kljaDR/weEYVFdEiFlEgz8plEgcEoz73yRKa3ZbAu1dzVeh1YXBZAmG6vxrv+S\n6elSUUbCrUGEAhzV+099xTKqy+hRV0PpC+nG6lImRMlRqSwdKBqWIIoyDmGx80B3\nutZ9/xVIRDziImI1zhCApaWxNVzkB73xeBR8VNRk8cAG\nuE5wlYHL4uk21w9JtylA\nh9jIMVDPflWhuWzieirzOR01VFbLQWO97NmgKkx5PxgyDXosRqc2llms5kqfMPfH\nKN0byCA52d0A1XB7wnrhmnn/t3fTT2Wo1ivYvj/TxD1o7q3VFQRNDWD+ah8lA/co\n0gJIqP+xs9fnE5oPeRNBqAfYBACE3AjjXBGyyD+tupyhqsA7xf+e1sPEtl1N2ZC4\nOjZW9kaRFIY+cVpo4apr8Ea6hTX1It7Ai2x29SIQvLkwCM+rDb7u2s\nIV2Q7002x0\nwV/JMfdrssi1y82ZTY7zPLm+kMMgfMY45GuFOPyLm4h6iNlKva0y5rkSieLwQwjc\ns5awzwL0+1sgveOW8mQmCPVEk6S3y39TUuVBZGHbcC6J4iYxZ5IFwrhGCh6+aBrE\nRdquwRQiHhTmsZMAH9Ab93j8t6/1d1MhbeVxYeO5uO5se5H/WkOtEnOomNHJnb+E\nDMp15vaMDmYxwT3aJCvnBEkCAwEAAQ==",true,"QmeybGaHdwrt2TyML57Gsm6dwktT5WpGFpns1G21LoXBZt");
	reguser("dealersandie"_n, "MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEA25CA8aDWxPhNHCoKFXvG\n97kljaDR/weEYVFdEiFlEgz8plEgcEoz73yRKa3ZbAu1dzVeh1YXBZAmG6vxrv+S\n6elSUUbCrUGEAhzV+099xTKqy+hRV0PpC+nG6lImRMlRqSwdKBqWIIoyDmGx80B3\nutZ9/xVIRDziImI1zhCApaWxNVzkB73xeBR8VNRk8cAG\nuE5wlYHL4uk21w9JtylA\nh9jIMVDPflWhuWzieirzOR01VFbLQWO97NmgKkx5PxgyDXosRqc2llms5kqfMPfH\nKN0byCA52d0A1XB7wnrhmnn/t3fTT2Wo1ivYvj/TxD1o7q3VFQRNDWD+ah8lA/co\n0gJIqP+xs9fnE5oPeRNBqAfYBACE3AjjXBGyyD+tupyhqsA7xf+e1sPEtl1N2ZC4\nOjZW9kaRFIY+cVpo4apr8Ea6hTX1It7Ai2x29SIQvLkwCM+rDb7u2s\nIV2Q7002x0\nwV/JMfdrssi1y82ZTY7zPLm+kMMgfMY45GuFOPyLm4h6iNlKva0y5rkSieLwQwjc\ns5awzwL0+1sgveOW8mQmCPVEk6S3y39TUuVBZGHbcC6J4iYxZ5IFwrhGCh6+aBrE\nRdquwRQiHhTmsZMAH9Ab93j8t6/1d1MhbeVxYeO5uO5se5H/WkOtEnOomNHJnb+E\nDMp15vaMDmYxwT3aJCvnBEkCAwEAAQ==",true,"QmRK2YHmc59oNycvrjSCULYGYFfh19CKBZxKTVQqjCNffV");
	
	//insertitem("peter"_n, "8867b0f58bab0b0bc37a8ddf50f7d822f91614c8950abbc79e2b458ebb936889", 25, "Threat Actor Leveraging Attack Patterns and Malware", "Threat Actor and Attack Pattern", true, true);
	//insertitem("peter"_n, "e43c66c297dc4d3f680dfdaaa6b9380a57d7f25cdd1eda740e19e460e723cab6", 16, "A malicious URL was seen on the network and an indicator was generated to capture this information.", "Sighting of an Indicator", true, true);
	//insertitem("emma"_n, "2db44de5b12085cfc9a7a7cb5f3090fbae62ae2c728e2113f30834dee5ca4744", 12, "This scenario consists of an indicator for an URL which is known to be malicious", "	Indicator for Malicious URL", true, true);
	//insertitem("emma"_n, "01f3d8da8677434c96398d4bfea0761f4dc4c791599035fb6b42ab6b7ebc0c2e", 12, "A Description of a simple indicator that represents a pattern for a file", "Malware Indicator for File Hash", true, true);
	//insertitem("peter"_n, "5b5d716bbd9abd3d10ee0938cd0a104e37b8cec69e97e597f246fb4a08a0a8c3", 14, "Yet another attack pattern", "Latest Attack Pattern", true, true);
	//insertitem("emma"_n, "05bad41c57932c044a7002a9338e3b34b05009907e3f171f89b4fcb2b9e3c887", 17, "Recognized intrusion set", "Intrusion set", true, true);

	//reporting::warning("reporting"_n,"Emotet continues to be among the most costly and destructive malware affecting governments. Its worm-like features result in rapidly spreading network-wide infections");

	//insertorder("peter"_n, 3, true);
	//insertorder("emma"_n, 0, false);

	}
}

void reporting::insertorder(name buyer, uint64_t itemKey, bool keyupload){
	auto it_buyer = _users.find(buyer.value);
	auto it_item = _items.find(itemKey);

	_orders.emplace(_self, [&]( auto& row ) { 
	  row.key = _orders.available_primary_key();  
	  row.itemKey = itemKey;
	  row.seller = it_item->reporter;
	  row.buyer = buyer; 
	  row.finished = 0; 
	  row.bkeyupload = keyupload;
	  row.timestamp = eosio::current_time_point(); 	
	});
	
	if(it_item->price > 0) {
	  transferescrow(buyer, it_item->reporter, it_item->price);
	}

}

void reporting::insertitem(name reporter, string hash, int price, string description, string title, bool sale, bool report){


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


