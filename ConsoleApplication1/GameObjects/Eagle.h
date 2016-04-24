#pragma once
#include "GameObjects\GameObject.h"

namespace GameObjects
{
	class Eagle : public GameObject
	{
		private:

		public:
			Eagle(World* world, int x, int y);

			virtual void paint(World* context) const;

			void update();
	};
}