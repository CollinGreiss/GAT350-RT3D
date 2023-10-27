#pragma once

#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include "Renderer/Program.h"

namespace nc {

	struct light_t {

		enum eType {

			Point,
			Directional,
			Spot

		};

		eType type;

		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 color;

		float innerAngle;
		float outerAngle;
		float intensity;
		float range;

	};

	class World04 : public World {

	public:

		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:

		float m_time;
		float m_speed = 5;
		
		int selected = 0;
		light_t m_lights[3];

		glm::vec3 ambientColor = glm::vec3 { 0.1 };

		Transform m_transform;
		res_t<Model> m_model;

	};

}