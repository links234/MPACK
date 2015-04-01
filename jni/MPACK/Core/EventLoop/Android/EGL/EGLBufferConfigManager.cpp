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
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_ALPHA_SIZE, &(newConfig.m_alphaSize)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_BIND_TO_TEXTURE_RGB, &(newConfig.m_bindToTextureRGB)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_BIND_TO_TEXTURE_RGBA, &(newConfig.m_bindToTextureRGBA)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_BLUE_SIZE, &(newConfig.m_blueSize)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_BUFFER_SIZE, &(newConfig.m_bufferSize)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_CONFIG_CAVEAT, &(newConfig.m_configCaveat)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_CONFIG_ID, &(newConfig.m_configId)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_DEPTH_SIZE, &(newConfig.m_depthSize)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_GREEN_SIZE, &(newConfig.m_greenSize)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_LEVEL, &(newConfig.m_level)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_MAX_PBUFFER_WIDTH, &(newConfig.m_maxPBufferWidth)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_MAX_PBUFFER_HEIGHT, &(newConfig.m_maxPBufferHeight)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_MAX_PBUFFER_PIXELS, &(newConfig.m_maxPBufferPixels)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_MAX_SWAP_INTERVAL, &(newConfig.m_maxSwapInterval)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_MIN_SWAP_INTERVAL, &(newConfig.m_minSwapInterval)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_NATIVE_RENDERABLE, &(newConfig.m_nativeRenderable)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_NATIVE_VISUAL_ID, &(newConfig.m_nativeVisualId)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_NATIVE_VISUAL_TYPE, &(newConfig.m_nativeVisualType)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_RED_SIZE, &(newConfig.m_redSize)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_SAMPLE_BUFFERS, &(newConfig.m_sampleBuffers)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_STENCIL_SIZE, &(newConfig.m_stencilSize)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_SURFACE_TYPE, &(newConfig.m_surfaceType)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_TRANSPARENT_TYPE, &(newConfig.m_transparentType)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_TRANSPARENT_RED_VALUE, &(newConfig.m_transparentRedValue)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_TRANSPARENT_GREEN_VALUE, &(newConfig.m_transparentGreenValue)) );
				EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_TRANSPARENT_BLUE_VALUE, &(newConfig.m_transparentBlueValue)) );

				if(m_pWindow->GetMajorVersion() >= 1 && m_pWindow->GetMinorVersion()>=2)
				{
					EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_ALPHA_MASK_SIZE, &(newConfig.m_alphaMaskSize)) );
					EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_COLOR_BUFFER_TYPE, &(newConfig.m_colorBufferType)) );
					EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_LUMINANCE_SIZE, &(newConfig.m_luminanceSize)) );
					EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_RENDERABLE_TYPE, &(newConfig.m_renderableType)) );
				}

				if(m_pWindow->GetMajorVersion()>= 1 && m_pWindow->GetMinorVersion()>=3)
				{
					EGL_CHECK( eglGetConfigAttrib(m_pWindow->m_display, config, EGL_CONFORMANT, &(newConfig.m_conformant)) );
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
	}
}
