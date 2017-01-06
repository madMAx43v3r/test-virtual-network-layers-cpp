/*
 * test_table.cpp
 *
 *  Created on: Nov 25, 2016
 *      Author: mad
 */

#include <vnl/Type.hxx>
#include <vnl/Layer.h>
#include <vnl/ThreadEngine.h>

#include <test/UserTable.h>
#include <test/UserTableClient.hxx>


int main() {
	
	vnl::Layer layer("test_table", "config/");
	vnl::ThreadEngine engine;
	
	test::UserTableBase* table = new test::UserTable(vnl::local_domain_name, "UserTable");
	table->filename = "table_user.dat";
	test::UserTableClient client = vnl::spawn(table);
	client.connect(&engine);
	
	int32_t user_count = client.get_count();
	std::cout << "We have " << user_count << " users" << std::endl;
	
	for(int i = user_count; i < 100000; ++i) {
		test::User user;
		user.id = vnl::rand();
		user.name << "test_user_" << i;
		client.insert(user);
	}
	
	user_count = client.get_count();
	std::cout << "Now have " << user_count << " users" << std::endl;
	
	{
		test::User user;
		user.id = vnl::rand();
		user.name << "test_user_" << 0;
		try {
			client.insert(user);
			assert(false);
		} catch(vnl::Exception& ex) {
			//std::cout << "Could not insert user: " << ex.type_name() << std::endl;
		}
	}
	
	{
		test::User user = client.get_by_name("test_user_0");
		client.update(user.id, "name", "test_user_0_tmp");
		test::User user2 = client.get_by_name("test_user_0_tmp");
		assert(user.id == user2.id);
		client.update(user.id, "name", "test_user_0");
		user2 = client.get_by_name("test_user_0");
		assert(user.id == user2.id);
	}
	
	{
		test::User user;
		user.id = vnl::rand();
		user.name << "test_user_xxx";
		client.insert(user);
		client.remove(user.id);
		try {
			client.get(user.id);
			assert(false);
		} catch(vnl::Exception& ex) {
			//std::cout << "Could not get user: " << ex.type_name() << std::endl;
		}
	}
	
	layer.shutdown();
	
}

