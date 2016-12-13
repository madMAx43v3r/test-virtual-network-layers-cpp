/*
 * TestTable.h
 *
 *  Created on: Dec 13, 2016
 *      Author: mad
 */

#ifndef SRC_TEST_USERTABLE_H_
#define SRC_TEST_USERTABLE_H_

#include <test/UserTableSupport.hxx>

namespace test {

class UserTable : public UserTableBase {
public:
	UserTable(const vnl::String& domain_, const vnl::String& topic_)
		:	UserTableBase(domain_, topic_)
	{
		add_view(&index_name);
	}
	
protected:
	User get_by_name(const vnl::String& name) const {
		return index_name.get(name);
	}
	
	int32_t get_count() const {
		return table.size();
	}
	
private:
	VNL_UNIQUE_INDEX(test::User, vnl::String, name, index_name);
	
};


} // test

#endif /* SRC_TEST_USERTABLE_H_ */
