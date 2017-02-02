/*
 * test_type_stream.cpp
 *
 *  Created on: Jul 17, 2016
 *      Author: mad
 */

#include <vnl/io.h>
#include <vnl/Layer.h>
#include <test/TestType.hxx>


int main() {
	
	int N = 100000;
	
	vnl::Layer layer("test_type_stream");
	
	vnl::Page* data = vnl::Page::alloc();
	vnl::io::ByteBuffer buf(data);
	vnl::io::TypeOutput out(&buf);
	
	test::TestType input;
	input.time = 1337;
	input.text = "test_test_test_test_test_test_test_test_test";
	input.val.x = 1337;
	input.val.y = 133;
	input.val.z = 13;
	input.list.push_back(test::TestValue());
	std::cout << input.to_string() << std::endl;
	
	for(int i = 0; i < N; ++i) {
		vnl::write(out, input);
		assert(!out.error());
	}
	out.flush();
	
	std::cout << "buf: size = " << buf.position() << std::endl;
	buf.flip();
	
	vnl::io::TypeInput in(&buf);
	test::TestType output;
	for(int i = 0; i < N; ++i) {
		vnl::read(in, output);
		assert(!in.error());
		assert(output.text == "test_test_test_test_test_test_test_test_test");
	}
	
	std::cout << output.to_string() << std::endl;
	
	{
		vnl::String str = input.to_string();
		test::TestType tmp;
		tmp.from_string(str);
		std::cout << tmp.to_string() << std::endl;
		assert(tmp.time == input.time);
		assert(tmp.text == input.text);
		assert(tmp.list.size() == input.list.size());
		assert(tmp.val.x == input.val.x);
		assert(tmp.val.y == input.val.y);
		assert(tmp.val.z == input.val.z);
	}
	
	data->free_all();
	
	layer.shutdown();
	
}

