#ifndef DEMONETWORKCLIENT_HPP
#define DEMONETWORKCLIENT_HPP

#include "MPACK.hpp"

namespace Demo
{
    class NetworkClient
    {
    public:
    	NetworkClient(MPACK::Network::UDPSocket *sock, MPACK::Network::SocketAddress serverAddr);
    	~NetworkClient();

        int Run();

    private:
        MPACK::Network::UDPSocket *m_sock;
        MPACK::Network::SocketAddress m_serverAddress;
    };
}

#endif
