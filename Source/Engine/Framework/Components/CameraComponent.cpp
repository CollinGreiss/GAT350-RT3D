#include "CameraComponent.h"
#include "Framework/Actor.h"
#include "Framework/Engine.h"

namespace nc {
	CLASS_DEFINITION( CameraComponent )

	bool CameraComponent::Initialize() {

		if ( aspect == 0 ) 
			aspect = (float) ENGINE.GetSystem<nc::Renderer>()->GetWidth() / ENGINE.GetSystem<nc::Renderer>()->GetHeight();

		return true;

	}

	void CameraComponent::Update( float dt ) {

		view = glm::lookAt( m_owner->transform.position, m_owner->transform.position + m_owner->transform.Forward(), m_owner->transform.Up() );
		projection = glm::perspective( glm::radians( fov ), aspect, near, far );

	}

	void CameraComponent::SetPerspective( float fov, float aspect, float near, float far ) {

		this->fov = fov;
		this->aspect = aspect;
		this->near = near;
		this->far = far;

		projection = glm::perspective( glm::radians( fov ), aspect, near, far );
	}

	void CameraComponent::SetLookAt( const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up ) {
		
		view = glm::lookAt( eye, center, up );

	}

	void CameraComponent::SetProgram( res_t<Program> program ) {

		program->SetUniform( "view", view );
		program->SetUniform( "projection", projection );

	}

	void CameraComponent::ProcessGui() {

		ImGui::SliderFloat( "FOV", &fov, 0.001, 180 );
		ImGui::SliderFloat( "Aspect", &aspect, 0.001, 3 );
		ImGui::SliderFloat( "Near Clip", &near, 0.001, far );
		ImGui::SliderFloat( "Far Clip", &far, near, 180 );

	}

	void CameraComponent::Read( const json_t& value ) {

		READ_DATA( value, fov );
		READ_DATA( value, aspect );
		READ_DATA( value, near );
		READ_DATA( value, far );

	}

}