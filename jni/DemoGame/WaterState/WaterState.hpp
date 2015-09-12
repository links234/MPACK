#ifndef WATERSTATE_HPP
#define WATERSTATE_HPP

#include "MPACK.hpp"

#include "GameState.hpp"
#include "WSInputController.hpp"
#include "WaterObject.hpp"

using namespace MPACK::Core;

namespace Game
{
	class WaterState: public GameState
	{
	public:
										WaterState();

		int 							Update();
		void 							Render();

		void 							Pause();
		void							Continue();

										~WaterState();

	private:
		WaterObject						m_water;

		WSInputController* 				m_pWSInputController;

		MPACK::Graphics::Texture2D*		m_pBackgroundTexture;
		MPACK::Graphics::Texture2D*		m_pWhiteTexture;
		MPACK::Graphics::Sprite* 		m_pBackgroundSprite;



	};
}

#endif
