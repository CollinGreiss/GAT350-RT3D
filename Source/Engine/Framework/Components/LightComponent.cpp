#include "LightComponent.h"
#include "Framework/Actor.h"

namespace nc {

	CLASS_DEFINITION( LightComponent )

	bool LightComponent::Initialize() {
		return true;
	}

	void LightComponent::Update( float dt ) { }

	void LightComponent::SetProgram( const res_t<Program> program, const std::string& name ) {

		program->SetUniform( name + ".type", type );
		program->SetUniform( name + ".position", m_owner->transform.position );
		program->SetUniform( name + ".direction", m_owner->transform.Forward() );
		program->SetUniform( name + ".color", color );
		program->SetUniform( name + ".intensity", intensity );
		program->SetUniform( name + ".range", range );
		program->SetUniform( name + ".innerAngle", glm::radians( innerAngle ) );
		program->SetUniform( name + ".outerAngle", glm::radians( outerAngle ) );

	}

	void LightComponent::ProcessGui() {

		const char* types[] = { "Point", "Directional", "Spot" };
		ImGui::Combo( "Type", (int*) ( &type ), types, 3 );

		if ( type == Spot ) {

			ImGui::SliderFloat( "Inner Angle", &innerAngle, 0, outerAngle );
			ImGui::SliderFloat( "Outer Angle", &outerAngle, innerAngle, 90 );

		}

		ImGui::ColorEdit3( "Color", glm::value_ptr( color ) );
		ImGui::DragFloat( "Intensity", &intensity, 0.1f, 0, 10 );
		if ( type != Directional ) ImGui::DragFloat( "Range", &range, 0.1f, 0.1f, 50 );


	}

	void LightComponent::Read( const nc::json_t& value ) {

		std::string lightType = "";
		
		READ_DATA(value, lightType);

		if (lightType == "Point") type = eType::Point;
		else if (lightType == "Directional") type = eType::Directional;
		else if (lightType == "Spot") type = eType::Spot;
		else ERROR_LOG("Light Type Not Found!")

		READ_DATA(value, color);
		READ_DATA(value, intensity);
		READ_DATA(value, range);
		READ_DATA(value, innerAngle);
		READ_DATA(value, outerAngle);

	}

}