/*
 * test_tcp_server.cpp
 *
 *  Created on: Jul 18, 2016
 *      Author: mad
 */

#include <vnl/TcpServer.h>
#include <vnl/ThreadEngine.h>
#include <vnl/Terminal.h>

#include <test/TroubleMaker.h>


int main() {
	
	vnl::Layer layer("test_tcp_server", "config/");
	
	vnl::TcpServer* server = new vnl::TcpServer("TcpServer");
	vnl::spawn(server);
	
	vnl::spawn(new test::TroubleMaker(vnl::local_domain_name, "test.trouble"));
	
	vnl::run(new vnl::Terminal());
	
}


