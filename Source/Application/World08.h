#pragma once

#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include "Renderer/Program.h"

namespace nc {

	class World08 : public World {

	public:

		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	public:

		int celLevels = 5;
		float celSpecularCutoff = 0.3f;
		float celOutline = 0.3f;

		std::shared_ptr< class Editor> m_editor;

	};

}