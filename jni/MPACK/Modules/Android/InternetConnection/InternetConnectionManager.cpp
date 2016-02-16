#include "InternetConnectionManager.hpp"
#include "InternetConnection.hpp"
#include "Debug.hpp"

using namespace MPACK::SERVICES;


namespace MPACK
{
	namespace InternetConnectionManager
	{
		InternetConnection *m_InternetConnection;

		void Init()
		{
			m_InternetConnection = new InternetConnection();
		}

		bool IsConnected()
		{
			int ans = m_InternetConnection->IsConnected();
			if (ans == InternetConnection::DISCONNECTED)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}

