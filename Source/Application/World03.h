#pragma once

#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include "Renderer/Program.h"

namespace nc {

	class World03 : public World {

	public:

		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:

		float m_time;
		float m_speed = 5;

		glm::vec2 m_tiling = { 1, 1 };
		glm::vec2 m_offset = { 0, 0 };

		Transform m_transform;

		res_t<VertexBuffer> m_vertexBuffer;
		res_t<Program> m_program;
		res_t<Texture> m_texture;
		res_t<Material> m_material;

	};

}