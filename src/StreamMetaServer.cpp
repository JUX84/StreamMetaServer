#include "StreamMetaServer.hpp"

#include <Ice/Ice.h>

StreamMetaServer::StreamMetaServer() {
	Ice::CommunicatorPtr ic;
	try {
		ic = Ice::initialize();
		Ice::ObjectPrx base = ic->stringToProxy("StreamServer:tcp -h zouxe.ovh -p 10000");
		ServerPrx server = ServerPrx::checkedCast(base);
		if(!server)
			std::cerr << "Invalid proxy\n";
		servers.push_back(server);
	} catch (const Ice::Exception& e) {
		std::cerr << e << '\n';
	}
}

std::string StreamMetaServer::selectSong(const Song& s, const Ice::Current& c) {
	return servers.front()->selectSong(s);
}

void StreamMetaServer::playSong(const std::string& token, const Ice::Current&) {
	servers.front()->playSong(token);
}

void StreamMetaServer::stopSong(const std::string& token, const Ice::Current&) {
	servers.front()->stopSong(token);
}

void StreamMetaServer::addSong(const Song& s, const Ice::Current&) {
	servers.front()->addSong(s);
}

void StreamMetaServer::removeSong(const Song& s, const Ice::Current&) {
	servers.front()->removeSong(s);
}

std::vector<Song> StreamMetaServer::searchSong(const std::string& artist, const std::string& title, const Ice::Current&) {
	return servers.front()->searchSong(artist, title);
}
