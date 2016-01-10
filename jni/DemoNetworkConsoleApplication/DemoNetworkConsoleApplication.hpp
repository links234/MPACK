#ifndef DEMONETWORKCONSOLEAPPLICATION_HPP
#define DEMONETWORKCONSOLEAPPLICATION_HPP

#include "MPACK.hpp"

namespace Demo
{
    class NetworkConsoleApplication : public MPACK::Core::ConsoleApplication
    {
    public:
    	NetworkConsoleApplication();
    	~NetworkConsoleApplication();

        int Main();

    private:
        bool SearchLANForServer();

        void NoServerResponding();
        void ServerFound();

        void ClientMode(MPACK::Network::UDPSocket *sock);
        void ServerMode(MPACK::Network::UDPSocket *sock);

        MPACK::Network::SocketAddress m_serverAddr;
    };
}

#endif
