/*
 * TroubleMaker.h
 *
 *  Created on: Jul 18, 2016
 *      Author: mad
 */

#ifndef TEST_TEST_TROUBLEMAKER_H_
#define TEST_TEST_TROUBLEMAKER_H_

#include <vnl/Object.h>
#include <test/TestType.hxx>


namespace test {

class TroubleMaker : public vnl::Object {
public:
	TroubleMaker(const vnl::String& domain_, const vnl::String& topic_)
		:	Object(domain_, topic_)
	{
		vnl_msg_timeout = 1000;
		const vnl::String* value = vnl::get_config(domain_, topic_, "interval");
		if(value) {
			vnl::from_string(*value, interval);
		}
	}
	
	int interval = 0;
	int counter = 0;
	
	vnl::TypedOutputPin<TestType> output;
	
protected:
	void main() {
		log(INFO).out << "trouble begins with interval=" << interval << " ..." << vnl::endl;
		set_timeout(1000*1000, std::bind(&TroubleMaker::print_stats, this), VNL_TIMER_REPEAT);
		set_timeout(interval, std::bind(&TroubleMaker::fire_machine_gun, this), VNL_TIMER_REPEAT);
		add_output(output);
		output.set_timeout(1000);
		run();
	}
	
	void print_stats() {
		log(INFO).out << "counter=" << counter << vnl::endl;
		counter = 0;
	}
	
	void fire_machine_gun() {
		TestType* data = TestType::create();
		data->time = vnl::currentTimeMicros();
		data->text = "sdfswdfasfasfafasdasdasdasdsd";
		data->list.push_back();
		data->list.push_back();
		data->list.push_back();
		output.transmit(data->clone());
		publish(data, "test", "test.topic");
		counter++;
		//std::this_thread::yield();	// for valgrind to switch threads
	}
	
};

}



#endif /* TEST_TEST_TROUBLEMAKER_H_ */
