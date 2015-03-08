#include "StreamMetaServer.hpp"

#include <Ice/Ice.h>

StreamMetaServer::StreamMetaServer() {
	Ice::CommunicatorPtr ic;
	try {
		ic = Ice::initialize();
		Ice::ObjectPrx base = ic->stringToProxy("StreamServer:tcp -h zouxe.ovh -p 10000");
		serverAM = ServerPrx::checkedCast(base);
		if(!serverAM)
			std::cerr << "Invalid proxy\n";
		base = ic->stringToProxy("StreamServer:tcp -h zouxe.ovh -p 10002");
		serverNZ = ServerPrx::checkedCast(base);
		if(!serverNZ)
			std::cerr << "Invalid proxy\n";
	} catch (const Ice::Exception& e) {
		std::cerr << e << '\n';
	}
}

std::string StreamMetaServer::selectSong(const Song& s, const Ice::Current& c) {
	std::string token;
	char tmp = s.artist.at(0);
	if((tmp>'a' && tmp<='m') || (tmp>'A' && tmp<='M')) {
		token = serverAM->selectSong(s);
		tokensAM.emplace(token);
	} else {
		token = serverNZ->selectSong(s);
		tokensNZ.emplace(token);
	}
	return token;
}

void StreamMetaServer::playSong(const std::string& token, const Ice::Current&) {
	if(tokensAM.find(token) != tokensAM.end())
		serverAM->playSong(token);
	else if(tokensNZ.find(token) != tokensNZ.end())
		serverNZ->playSong(token);
}

void StreamMetaServer::stopSong(const std::string& token, const Ice::Current&) {
	if(tokensAM.find(token) != tokensAM.end())
		serverAM->stopSong(token);
	else if(tokensNZ.find(token) != tokensNZ.end())
		serverNZ->stopSong(token);
}

void StreamMetaServer::addSong(const Song& s, const Ice::Current&) {
	char tmp = s.artist.at(0);
	if((tmp>'a' && tmp<='m') || (tmp>'A' && tmp<='M'))
		serverAM->addSong(s);
	else
		serverNZ->addSong(s);
}

void StreamMetaServer::removeSong(const Song& s, const Ice::Current&) {
	char tmp = s.artist.at(0);
	if((tmp>'a' && tmp<='m') || (tmp>'A' && tmp<='M'))
		serverAM->removeSong(s);
	else
		serverNZ->removeSong(s);
}

std::vector<Song> StreamMetaServer::searchSong(const std::string& artist, const std::string& title, const Ice::Current&) {
	std::vector<Song> az, am, nz;
	am = serverAM->searchSong(artist, title);
	nz = serverNZ->searchSong(artist, title);
	az.insert(az.end(), am.begin(), am.end());
	az.insert(az.end(), nz.begin(), nz.end());
	return az;
}
