#pragma once

#include "RenderComponent.h"
#include "Renderer/Program.h"

namespace nc {

	class PostProcessComponent : public RenderComponent {

	public:

		CLASS_DECLARATION(PostProcessComponent)

		bool Initialize() override;
		void Update( float dt ) override;
		void Draw(class Renderer& renderer) override;

		void ProcessGui() override;

	private:

		float m_time = 0;

		float blend = 1;

		glm::vec3 tint{ 0 };
		int lineSpace = 2;

		res_t<Program> m_program;

		uint32_t params{ 0 };
		const uint32_t INVERT_MASK =	(1 << 0);
		const uint32_t GREYSCALE_MASK = (1 << 1);
		const uint32_t COLORTINT_MASK = (1 << 2);
		const uint32_t GRAIN_MASK =		(1 << 3);
		const uint32_t SCANLINE_MASK =	(1 << 4);
		const uint32_t GAMER_MASK =		(1 << 5);

	};

}
