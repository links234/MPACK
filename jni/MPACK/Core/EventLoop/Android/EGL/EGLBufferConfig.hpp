#ifndef MPACK_EGLDISPLAY_HPP
#define MPACK_EGLDISPLAY_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		class EGLBufferConfig
		{
		public:
			EGLint m_alphaSize;
			EGLint m_bindToTextureRGB;
			EGLint m_bindToTextureRGBA;
			EGLint m_blueSize;
			EGLint m_bufferSize;
			EGLint m_configCaveat;
			EGLint m_configId;
			EGLint m_depthSize;
			EGLint m_greenSize;
			EGLint m_level;
			EGLint m_maxPBufferWidth;
			EGLint m_maxPBufferHeight;
			EGLint m_maxPBufferPixels;
			EGLint m_maxSwapInterval;
			EGLint m_minSwapInterval;
			EGLint m_nativeRenderable;
			EGLint m_redSize;

			EGLint m_alphaMaskSize;
			EGLint m_colorBufferType;
			EGLint m_luminanceSize;
			EGLint m_renderableType;

			EGLint m_conformant;
		};
	}
}

#endif
