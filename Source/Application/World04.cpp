#include "World04.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

namespace nc {


	bool World04::Initialize() {

		auto material = GET_RESOURCE( Material, "materials/squirrel.mtrl" );
		m_model = std::make_shared<Model>();
		m_model->SetMaterial( material );
		m_model->Load( "models/squirrel.glb", glm::vec3 { 0, -0.7f, 0 }, glm::vec3 { 0 }, glm::vec3 { 0.4f } );

		for ( int i = 0; i < 3; i++ ) {

			m_lights[i].type = light_t::eType::Point;
			m_lights[i].position = glm::vec3 { 0, 0, 0 };
			m_lights[i].direction = glm::vec3 { 0, 0, -1 };
			m_lights[i].color = glm::vec3 { 1, 1, 1 };
			m_lights[i].innerAngle = 10.0f;
			m_lights[i].outerAngle = 30.0f;
			m_lights[i].intensity = 1.0f;
			m_lights[i].range = 5.0f;

		}

		return true;

	}

	void World04::Shutdown() {

	}

	void World04::Update( float dt ) {

		ENGINE.GetSystem<Gui>()->BeginFrame();

		ImGui::Begin( "Scene" );
		ImGui::ColorEdit3( "Ambient Color", glm::value_ptr( ambientColor ) );
		ImGui::Separator();

		for ( int i = 0; i < 3; i++ ) {

			std::string name = "light" + std::to_string( i );

			if ( ImGui::Selectable( name.c_str(), selected == i ) ) selected = i;

		}

		ImGui::End();

		ImGui::Begin( "Light" );

		const char* types[] = { "Point", "Dircectional", "Spot" };
		ImGui::Combo( "Type", (int*) ( &m_lights[selected].type ), types, 3 );

		if ( m_lights[selected].type != light_t::eType::Directional ) {

			ImGui::DragFloat3( "Position", glm::value_ptr( m_lights[selected].position ), 0.1f );
			ImGui::SliderFloat( "Range", &m_lights[selected].range, 0.01f, 100 );

		}

		if ( m_lights[selected].type != light_t::eType::Point )
			ImGui::DragFloat3( "Direction", glm::value_ptr( m_lights[selected].direction ), 0.01f, -1, 1 );

		if ( m_lights[selected].type == light_t::eType::Spot ) {

			ImGui::SliderFloat( "Inner Angle", &m_lights[selected].innerAngle, 0, m_lights[selected].outerAngle );
			ImGui::SliderFloat( "Outer Angle", &m_lights[selected].outerAngle, m_lights[selected].innerAngle, 180);

		}
		
		ImGui::SliderFloat( "Intensity", &m_lights[selected].intensity, 0, 10);


		ImGui::ColorEdit3( "Color", glm::value_ptr( m_lights[selected].color ) );

		ImGui::End();


		m_transform.rotation.y -= dt * ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_E ) ? m_speed * dt * 45 : 0;
		m_transform.rotation.y += dt * ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_Q ) ? m_speed * dt * 45 : 0;

		m_transform.position.x -= ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_A ) ? m_speed * dt : 0;
		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_D ) ? m_speed * dt : 0;

		m_transform.position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_LSHIFT ) ? m_speed * dt : 0;
		m_transform.position.y -= ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_LCTRL ) ? m_speed * dt : 0;

		m_transform.position.z -= ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_W ) ? m_speed * dt : 0;
		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_S ) ? m_speed * dt : 0;

		m_time += dt;

		auto material = m_model->GetMaterial();
		material->ProcessGui();
		material->Bind();

		material->GetProgram()->SetUniform( "model", m_transform.GetMatrix() );

		glm::mat4 view = glm::lookAt( glm::vec3( 0, 0, 3 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );
		material->GetProgram()->SetUniform( "view", view );

		glm::mat4 projection = glm::perspective( glm::radians( 70.0f ), (float) ENGINE.GetSystem<nc::Renderer>()->GetWidth() / ENGINE.GetSystem<nc::Renderer>()->GetHeight(), 0.01f, 100.0f );
		material->GetProgram()->SetUniform( "projection", projection );

		for ( int i = 0; i < 3; i++ ) {

			std::string name = "lights[" + std::to_string( i ) + "]";

			material->GetProgram()->SetUniform( name + ".type", (int) m_lights[i].type );

			material->GetProgram()->SetUniform( name + ".direction", glm::normalize( m_lights[i].direction ) );
			material->GetProgram()->SetUniform( name + ".position", m_lights[i].position );
			material->GetProgram()->SetUniform( name + ".range", m_lights[i].range );

			material->GetProgram()->SetUniform( name + ".innerAngle", glm::radians( m_lights[i].innerAngle ) );
			material->GetProgram()->SetUniform( name + ".outerAngle", glm::radians( m_lights[i].outerAngle ) );

			material->GetProgram()->SetUniform( name + ".color", m_lights[i].color );
			material->GetProgram()->SetUniform( name + ".intensity", m_lights[i].intensity );

		}

		material->GetProgram()->SetUniform( "ambientLight", ambientColor );

		ENGINE.GetSystem<Gui>()->EndFrame();

	}

	void World04::Draw( Renderer& renderer ) {

		// pre-render
		renderer.BeginFrame();

		// render

		m_model->Draw( GL_TRIANGLES );
		ENGINE.GetSystem<Gui>()->Draw();

		// post-render
		renderer.EndFrame();

	}

}
