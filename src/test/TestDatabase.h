/*
 * TestDatabase.h
 *
 *  Created on: Nov 25, 2016
 *      Author: mad
 */

#ifndef SRC_TEST_TESTDATABASE_H_
#define SRC_TEST_TESTDATABASE_H_

#include <test/TestDatabaseSupport.hxx>
#include <vnl/DuplicateKeyException.hxx>


namespace test {

class TestDatabase : public TestDatabaseBase {
public:
	TestDatabase(const vnl::String& topic_ = "TestDatabase")
		:	TestDatabaseBase(vnl::local_domain_name, topic_)
	{
	}
	
protected:
	void add_user(const User& user) {
		if(user_by_name.find(user.name)) {
			throw vnl::DuplicateKeyException();
		}
		user_table[user.id] = user;
		user_by_name[user.name] = user.id;
	}
	
	void update_user_name(const vnl::Hash64& id, const vnl::String& new_name) {
		User* user = user_table.find(id);
		if(user) {
			user_by_name.erase(user->name);
			user_by_name[new_name] = user->id;
			user->name = new_name;
		}
	}
	
	void del_user(const vnl::Hash64& id) {
		User* user = user_table.find(id);
		if(user) {
			user_by_name.erase(user->name);
			user_table.erase(id);
		}
	}
	
	User get_user_by_id(const vnl::Hash64& id) const {
		const User* user = user_table.find(id);
		if(user) {
			return *user;
		}
		return User();
	}
	
	User get_user_by_name(const vnl::String& name) const {
		const vnl::Hash64* id = user_by_name.find(name);
		if(id) {
			const User* user = user_table.find(*id);
			if(user) {
				return *user;
			}
		}
		return User();
	}
	
	int32_t get_user_count() const {
		return user_table.size();
	}
	
private:
	vnl::Map<vnl::Hash64, User> user_table;
	vnl::Map<vnl::String, vnl::Hash64> user_by_name;
	
};


} // test

#endif /* SRC_TEST_TESTDATABASE_H_ */
