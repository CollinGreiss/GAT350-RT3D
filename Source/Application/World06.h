#pragma once

#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include "Renderer/Program.h"

namespace nc {

	class World06 : public World {

	public:

		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:

		float m_time = 0;

		float blend = 1;
		glm::vec3 tint{ 0 };


		uint32_t params{ 0 };
		const uint32_t INVERT_MASK = (1 << 0);
		const uint32_t GREYSCALE_MASK = (1 << 1);
		const uint32_t COLORTINT_MASK = (1 << 2);

	};

}