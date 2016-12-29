/*
 * test_module.cpp
 *
 *  Created on: Jul 15, 2016
 *      Author: mad
 */

#include <vnl/ThreadEngine.h>
#include <vnl/Terminal.h>

#include <test/TestNode.h>
#include <test/TroubleMaker.h>


int main() {
	
	vnl::Layer layer("test_module", "config/");
	
	test::TroubleMaker* trouble = new test::TroubleMaker(vnl::local_domain_name, "test.trouble");
	
	for(int i = 0; i < 1; ++i) {
		test::TestNode* node = new test::TestNode(vnl::local_domain_name, "test.node");
		vnl::connect(node->input, trouble->output);
		vnl::spawn(node);
	}
	
	vnl::spawn(trouble);
	
	vnl::run(new vnl::Terminal());
	
}


