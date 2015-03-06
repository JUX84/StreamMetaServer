#include "Server.h"

#include <list>

using namespace Player;

class StreamMetaServer : public Server {
	private:
		std::list<ServerPrx> servers;
	public:
		StreamMetaServer();
		std::string selectSong(const Song& s, const Ice::Current&);
		void playSong(const std::string& token, const Ice::Current&);
		void stopSong(const std::string& token, const Ice::Current&);
		void addSong(const Song& s, const Ice::Current&);
		void removeSong(const Song& s, const Ice::Current&);
		SongSeq searchSong(const std::string& artist, const std::string& title, const Ice::Current&);
};
