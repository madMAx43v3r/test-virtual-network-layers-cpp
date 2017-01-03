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
#include <vnl/TcpServer.h>
#include <vnl/Recorder.h>

#include <test/TestNode.h>


int main() {
	
	//vnl::Page::prealloc(1000);
	//vnl::Block::prealloc(10000);
	
	vnl::Layer layer("test_tcp_client");

	{
		vnl::TcpServer* module = new vnl::TcpServer(vnl::local_domain_name, "TcpServer");
		module->port = 8917;
		vnl::spawn(module);
	}
	
	if(false) {
		vnl::Recorder* module = new vnl::Recorder(vnl::local_domain_name);
		module->domains.push_back("test");
		vnl::spawn(module);
	}
	
	vnl::ThreadEngine engine;
	
	vnl::TcpClient* client = new vnl::TcpClient(vnl::local_domain_name, "TcpClient");
	client->endpoint = "localhost";
	vnl::UplinkClient uplink = vnl::spawn(client);
	uplink.connect(&engine);
	uplink.subscribe("test", "test.topic");
	
	vnl::spawn(new test::TestNode("test", "test.node"));
	
	vnl::run(new vnl::Terminal());
	
}

