#ifndef MPACK_EGLBUFFERCONFIGMANAGER_HPP
#define MPACK_EGLBUFFERCONFIGMANAGER_HPP

#include "Types.hpp"
#include "EGLBufferConfig.hpp"

namespace MPACK
{
	namespace Core
	{
		class EGLWindow;
	}
}

namespace MPACK
{
	namespace Core
	{
		class EGLBufferConfigManager
		{
		public:
			EGLBufferConfigManager(EGLWindow *pWindow);
			~EGLBufferConfigManager();

			void PrintAll() const;
			int GetCount() const;

			void Match(EGLint &redSize, EGLint &greenSize, EGLint &blueSize, EGLint &depthSize) const;

			void SafeGetConfigAttrib(EGLConfig config, EGLint attribute, EGLint *value);

		private:
			std::vector<EGLBufferConfig> m_config;

			EGLWindow *m_pWindow;
		};
	}
}

#endif
