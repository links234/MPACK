#include "Application.hpp"

namespace MPACK
{
	namespace Core
	{
		Application::Application()
		{
			m_applicationType = APP_BLANK;
		}

		Application::~Application()
		{
		}

		ApplicationType Application::GetType() const
		{
			return m_applicationType;
		}
	}
}
