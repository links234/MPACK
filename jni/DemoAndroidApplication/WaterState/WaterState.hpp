#ifndef WATERSTATE_HPP
#define WATERSTATE_HPP

#include "MPACK.hpp"

#include "GameState.hpp"
#include "WSInputController.hpp"
#include "WaterObject.hpp"
#include "WSRockObject.hpp"
#include <vector>

using namespace MPACK::Core;
using namespace MPACK::Physics;

namespace Demo
{
	class WaterState: public GameState
	{
	public:
										WaterState();

		int 							Update();
		void 							Render();

		void 							Pause();
		void							Continue();

		virtual							~WaterState();

	private:

		WSRockObject*					CreateRockObject(const Vector2f & pos);

		float							m_timeSinceLastWave;
		const float						m_timeBetweenWaves;

		WaterObject						m_water;

		WSInputController* 				m_pWSInputController;

		std::vector<WSRockObject*>		m_rockObjects;

		MPACK::Graphics::Texture2D*		m_pBackgroundTexture;
		MPACK::Graphics::Texture2D*		m_pWhiteTexture;
		MPACK::Graphics::Texture2D*		m_pRockTexture;

		MPACK::Graphics::Sprite* 		m_pBackgroundSprite;

		World							*m_world;




	};
}

#endif
