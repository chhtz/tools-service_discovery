/**
 * @file
 * a example source file for browsing services using simple poll
 */
 
#include <csignal>
#include <stdlib.h>
#include <iostream>
#include "../afAvahiFramework.h"
 
//create a client with simple poll
dfki::communication::afSimplePoll simplepoll;
dfki::communication::afAvahiClient client(&simplepoll, (AvahiClientFlags) 0);
 
void handleSIGINT(int sig) {
	std::cout << ".CAUGHT SIG " << sig << std::endl;
	client.stop();
} 
 
void testAdded (dfki::communication::afRemoteService rms) {
	std::cout << " -=- TESTING SIGNAL: ADDED SERVICE: " << rms.getName() << std::endl;
}

 
int main(int argc, char** argv)
{
	
	signal(SIGTERM, handleSIGINT);
	signal(SIGINT, handleSIGINT);
	
	//create a service browser
	dfki::communication::afServiceBrowser sbrowser(&client, "_rimres._tcp");

	//connect a callback to the service added signal. Method can also be a class member. Look at sigc++ api
	sbrowser.serviceAddedConnect(sigc::ptr_fun(testAdded));
	
	//publish a sample service to test the callbacks
	std::list<std::string> strlst;
	strlst.push_back("service_year=1999");
	dfki::communication::afLocalService serv(&client, "MyLocalService", "_rimres._tcp", 10000, strlst);
	
	//run the main event loop
	client.dispatch();
	
}