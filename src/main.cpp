#include "StreamMetaServer.hpp"

#include <Ice/Ice.h>

int main(int argc, char **argv) {
	int status = 0;
	Ice::CommunicatorPtr ic;
	try {
		ic = Ice::initialize(argc, argv);
		Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("StreamMetaServerAdapter", "tcp -p 10001");
		Ice::ObjectPtr object = new StreamMetaServer;
		adapter->add(object, ic->stringToIdentity("StreamMetaServer"));
		adapter->activate();
		ic->waitForShutdown();
	} catch (const Ice::Exception& e) {
		std::cerr << e << '\n';
		status = 1;
	} catch (const char* msg) {
		std::cerr << msg << '\n';
		status = 1;
	}
	if (ic) {
		try {
			ic->destroy();
		} catch (const Ice::Exception& e) {
			std::cerr << e << '\n';
			status = 1;
		}
	}
	return status;
}
