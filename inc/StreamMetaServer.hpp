#include "Server.h"

#include <unordered_set>

using namespace Player;

class StreamMetaServer : public Server {
	private:
		ServerPrx serverAM;
		ServerPrx serverNZ;
		std::unordered_set<std::string> tokensAM;
		std::unordered_set<std::string> tokensNZ;
	public:
		StreamMetaServer();
		std::string selectSong(const Song& s, const Ice::Current&);
		void playSong(const std::string& token, const Ice::Current&);
		void stopSong(const std::string& token, const Ice::Current&);
		void addSong(const Song& s, const Ice::Current&);
		void removeSong(const Song& s, const Ice::Current&);
		SongSeq searchSong(const std::string& artist, const std::string& title, const Ice::Current&);
		void uploadFile(const std::string& path, const ByteSeq& data, const Ice::Current&);
};
