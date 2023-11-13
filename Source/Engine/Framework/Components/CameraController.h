#pragma once
#include "Component.h"

namespace nc {

	class CameraController : public Component {

	public:

		CLASS_DECLARATION( CameraController )

		bool Initialize() override;
		void Update( float dt ) override;

		void ProcessGui();

	public:

		float sensitivity = 1.0f;
		float speed = 5;
		float yaw = 0;
		float pitch = 0;

	};

}