/*
 * test_database.cpp
 *
 *  Created on: Nov 25, 2016
 *      Author: mad
 */

#include <vnl/Layer.h>
#include <vnl/ThreadEngine.h>

#include <test/TestDatabase.h>
#include <test/TestDatabaseClient.hxx>


int main() {
	
	vnl::Layer layer("test_database", "config/");
	vnl::ThreadEngine engine;
	
	test::TestDatabaseClient client = vnl::spawn(new test::TestDatabase());
	client.connect(&engine);
	
	vnl::String filename = client.get_filename();
	std::cout << "TestDatabase: filename=" << filename << std::endl;
	
	int32_t user_count = client.get_user_count();
	std::cout << "We have " << user_count << " users" << std::endl;
	
	for(int i = user_count; i < 100000; ++i) {
		test::User user;
		user.id = vnl::rand();
		user.name << "test_user_" << i;
		client.add_user(user);
	}
	
	{
		test::User user;
		user.id = vnl::rand();
		user.name << "test_user_" << 0;
		try {
			client.add_user(user);
			assert(false);
		} catch(vnl::Exception& ex) {
			//std::cout << "Could not insert user: " << ex.type_name() << std::endl;
		}
	}
	
	user_count = client.get_user_count();
	std::cout << "Now have " << user_count << " users" << std::endl;
	
	layer.shutdown();
	
}

