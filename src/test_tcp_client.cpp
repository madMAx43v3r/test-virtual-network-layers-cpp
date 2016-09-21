/*
 * test_tcp_client.cpp
 *
 *  Created on: Jul 18, 2016
 *      Author: mad
 */

#include <vnl/TcpClient.h>
#include <vnl/UplinkClient.hxx>
#include <vnl/ThreadEngine.h>
#include <vnl/Terminal.h>

#include <test/TestNode.h>


int main() {
	
	vnl::Layer layer("test_tcp_client");
	
	vnl::ThreadEngine engine;
	
	vnl::UplinkClient uplink;
	uplink = vnl::spawn(new vnl::TcpClient("localhost"));
	uplink.connect(&engine);
	
	vnl::Topic topic;
	topic.domain = "test";
	topic.name = "test.topic";
	uplink.subscribe(topic);
	
	vnl::spawn(new test::TestNode("test", "test/node"));
	
	vnl::run(new vnl::Terminal());
	
}

