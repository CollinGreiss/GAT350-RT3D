#pragma once

#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include "Renderer/Program.h"

namespace nc {

	class World05 : public World {

	public:

		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:

		float m_time = 0;

	};

}