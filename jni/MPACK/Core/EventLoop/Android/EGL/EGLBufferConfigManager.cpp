#ifdef ANDROID_PLATFORM

#include "EGLBufferConfigManager.hpp"

#include "EGLBufferConfig.hpp"
#include "EGLWindow.hpp"

using namespace std;

namespace MPACK
{
	namespace Core
	{
		EGLBufferConfigManager::EGLBufferConfigManager(EGLWindow *pWindow)
			: m_pWindow(pWindow)
		{
			EGLint result = 0;
			EGLint numConfigs = 0;
			EGL_CHECK( result = eglGetConfigs(m_pWindow->m_display, NULL, 0, &numConfigs) );
			if(result == EGL_FALSE)
			{
				LOGE("EGLBufferConfigManager::EGLBufferConfigManager() error: failed to get number of configurations");
				return;
			}

			if(numConfigs <= 0)
			{
				LOGE("EGLBufferConfigManager::EGLBufferConfigManager() error: invalid number of configurations");
				return;
			}

			EGLConfig *configs = new EGLConfig[numConfigs];

			EGL_CHECK( result = eglGetConfigs(m_pWindow->m_display, configs, numConfigs, &numConfigs));

			if(result == EGL_FALSE)
			{
				LOGE("EGLBufferConfigManager::EGLBufferConfigManager() error: failed to get configurations");
				delete [] configs;
				return;
			}

			EGLBufferConfig newConfig;

			for(EGLint c=0;c<numConfigs;++c)
			{
				EGLConfig config = configs[c];

				SafeGetConfigAttrib(config, EGL_ALPHA_SIZE, &(newConfig.m_alphaSize));
				SafeGetConfigAttrib(config, EGL_BIND_TO_TEXTURE_RGB, &(newConfig.m_bindToTextureRGB));
				SafeGetConfigAttrib(config, EGL_BIND_TO_TEXTURE_RGBA, &(newConfig.m_bindToTextureRGBA));
				SafeGetConfigAttrib(config, EGL_BLUE_SIZE, &(newConfig.m_blueSize));
				SafeGetConfigAttrib(config, EGL_BUFFER_SIZE, &(newConfig.m_bufferSize));
				SafeGetConfigAttrib(config, EGL_CONFIG_CAVEAT, &(newConfig.m_configCaveat));
				SafeGetConfigAttrib(config, EGL_CONFIG_ID, &(newConfig.m_configId));
				SafeGetConfigAttrib(config, EGL_DEPTH_SIZE, &(newConfig.m_depthSize));
				SafeGetConfigAttrib(config, EGL_GREEN_SIZE, &(newConfig.m_greenSize));
				SafeGetConfigAttrib(config, EGL_LEVEL, &(newConfig.m_level));
				SafeGetConfigAttrib(config, EGL_MAX_PBUFFER_WIDTH, &(newConfig.m_maxPBufferWidth));
				SafeGetConfigAttrib(config, EGL_MAX_PBUFFER_HEIGHT, &(newConfig.m_maxPBufferHeight));
				SafeGetConfigAttrib(config, EGL_MAX_PBUFFER_PIXELS, &(newConfig.m_maxPBufferPixels));
				SafeGetConfigAttrib(config, EGL_MAX_SWAP_INTERVAL, &(newConfig.m_maxSwapInterval));
				SafeGetConfigAttrib(config, EGL_MIN_SWAP_INTERVAL, &(newConfig.m_minSwapInterval));
				SafeGetConfigAttrib(config, EGL_NATIVE_RENDERABLE, &(newConfig.m_nativeRenderable));
				SafeGetConfigAttrib(config, EGL_NATIVE_VISUAL_ID, &(newConfig.m_nativeVisualId));
				SafeGetConfigAttrib(config, EGL_NATIVE_VISUAL_TYPE, &(newConfig.m_nativeVisualType));
				SafeGetConfigAttrib(config, EGL_RED_SIZE, &(newConfig.m_redSize));
				SafeGetConfigAttrib(config, EGL_SAMPLE_BUFFERS, &(newConfig.m_sampleBuffers));
				SafeGetConfigAttrib(config, EGL_STENCIL_SIZE, &(newConfig.m_stencilSize));
				SafeGetConfigAttrib(config, EGL_SURFACE_TYPE, &(newConfig.m_surfaceType));
				SafeGetConfigAttrib(config, EGL_TRANSPARENT_TYPE, &(newConfig.m_transparentType));
				SafeGetConfigAttrib(config, EGL_TRANSPARENT_RED_VALUE, &(newConfig.m_transparentRedValue));
				SafeGetConfigAttrib(config, EGL_TRANSPARENT_GREEN_VALUE, &(newConfig.m_transparentGreenValue));
				SafeGetConfigAttrib(config, EGL_TRANSPARENT_BLUE_VALUE, &(newConfig.m_transparentBlueValue));

				if(m_pWindow->GetMajorVersion() >= 1 && m_pWindow->GetMinorVersion()>=2)
				{
					SafeGetConfigAttrib(config, EGL_ALPHA_MASK_SIZE, &(newConfig.m_alphaMaskSize));
					SafeGetConfigAttrib(config, EGL_COLOR_BUFFER_TYPE, &(newConfig.m_colorBufferType));
					SafeGetConfigAttrib(config, EGL_LUMINANCE_SIZE, &(newConfig.m_luminanceSize));
					SafeGetConfigAttrib(config, EGL_RENDERABLE_TYPE, &(newConfig.m_renderableType));
				}

				if(m_pWindow->GetMajorVersion()>= 1 && m_pWindow->GetMinorVersion()>=3)
				{
					SafeGetConfigAttrib(config, EGL_CONFORMANT, &(newConfig.m_conformant));
				}
				m_config.push_back(newConfig);
			}
		}

		EGLBufferConfigManager::~EGLBufferConfigManager()
		{
		}

		void EGLBufferConfigManager::PrintAll() const
		{
			int config=0;
			for(vector<EGLBufferConfig>::const_iterator it=m_config.begin();it!=m_config.end();++it)
			{
				++config;
				LOGI("EGL Configuration #%d: (R:%d G:%d B:%d depth:%d)",config,it->m_redSize,it->m_greenSize,it->m_blueSize,it->m_depthSize);
			}
		}

		int EGLBufferConfigManager::GetCount() const
		{
			return m_config.size();
		}

		void EGLBufferConfigManager::Match(EGLint &redSize, EGLint &greenSize, EGLint &blueSize, EGLint &depthSize) const
		{
			EGLint bestRedSize=0;
			EGLint bestGreenSize=0;
			EGLint bestBlueSize=0;
			EGLint bestDepthSize=0;
			for(vector<EGLBufferConfig>::const_iterator it=m_config.begin();it!=m_config.end();++it)
			{
				if(bestRedSize<=it->m_redSize && bestGreenSize<=it->m_greenSize && bestBlueSize<=it->m_blueSize && bestDepthSize<=it->m_depthSize)
				{
					bestRedSize=it->m_redSize;
					bestGreenSize=it->m_greenSize;
					bestBlueSize=it->m_blueSize;
					bestDepthSize=it->m_depthSize;
				}
				else
				{
					if(depthSize!=0 && it->m_depthSize==0)
					{
						continue;
					}
					if(it->m_redSize+it->m_greenSize+it->m_blueSize>bestRedSize+bestGreenSize+bestBlueSize)
					{
						bestRedSize=it->m_redSize;
						bestGreenSize=it->m_greenSize;
						bestBlueSize=it->m_blueSize;
						bestDepthSize=it->m_depthSize;
					}
				}
			}
			redSize=bestRedSize;
			greenSize=bestGreenSize;
			blueSize=bestBlueSize;
			if(depthSize!=0)
			{
				depthSize=bestDepthSize;
			}
		}

		void EGLBufferConfigManager::SafeGetConfigAttrib(EGLConfig config, EGLint attribute, EGLint *value)
		{
			eglGetConfigAttrib(m_pWindow->m_display, config, attribute, value);
			if(Debug::EGL::GetError(false) != EGL_SUCCESS) {
				(*value) = 0;
			}
		}
	}
}

#endif
