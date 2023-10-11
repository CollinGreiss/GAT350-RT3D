#pragma once

#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Renderer/Program.h"

namespace nc {

	class World03 : public World {

	public:

		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:

		float m_angle = 0;
		float m_time = 0;
		float m_speed = 5;

		glm::vec3 m_position;
		std::vector<vec2> m_positions;

		Transform m_transform;

		GLuint m_vao;
		res_t<Program> m_program;

	};

}