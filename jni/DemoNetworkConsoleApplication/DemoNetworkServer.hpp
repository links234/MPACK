#ifndef DEMONETWORKSERVER_HPP
#define DEMONETWORKSERVER_HPP

#include "MPACK.hpp"

namespace Demo
{
    class NetworkServer
    {
    public:
    	NetworkServer(MPACK::Network::UDPSocket *sock, int searchPort);
    	~NetworkServer();

        int Run();

    private:
        int m_searchPort;
        MPACK::Network::UDPSocket *m_sock;
    };
}

#endif
