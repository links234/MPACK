#ifndef BROADCASTSEARCHSERVER_HPP
#define BROADCASTSEARCHSERVER_HPP

#include "MPACK.hpp"

class BroadcastSearchServer
{
public:
	BroadcastSearchServer();
	~BroadcastSearchServer();

	void Init(int port);
	void Update();

private:
	MPACK::Network::UDPSocket *m_sock;
};

#endif
