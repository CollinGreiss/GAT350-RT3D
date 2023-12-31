#include "World03.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

namespace nc {


	bool World03::Initialize() {

		m_material = GET_RESOURCE( Material, "materials/quad.mtrl" );

		//m_program = GET_RESOURCE( Program, "shaders/unlit_texture.prog" );
		//m_program->Use();
		
		//m_texture = GET_RESOURCE( Texture, "textures/llama.jpg" );
		//m_texture->Bind();
		//m_texture->SetActive( GL_TEXTURE0 );

		float vertexData[] = {
			-0.8f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			 0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			-0.8f,  0.8f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.8f,  0.8f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f

		};

		m_vertexBuffer = std::make_shared<VertexBuffer>();

		m_vertexBuffer = GET_RESOURCE( VertexBuffer, "vb" );
		m_vertexBuffer->CreateVertexBuffer( sizeof( vertexData ), 4, vertexData );
		m_vertexBuffer->SetAttribute( 0, 3, 8 * sizeof( GLfloat ), 0 );
		m_vertexBuffer->SetAttribute( 1, 3, 8 * sizeof( GLfloat ), 3 * sizeof( float ) );
		m_vertexBuffer->SetAttribute( 2, 2, 8 * sizeof( GLfloat ), 6 * sizeof( float ) );

		return true;

	}

	void World03::Shutdown() {

	}

	void World03::Update( float dt ) {

		ENGINE.GetSystem<Gui>()->BeginFrame();

		ImGui::Begin( "Transform" );
		ImGui::DragFloat3( "Position", &m_transform.position[0] );
		ImGui::DragFloat3( "Rotation", &m_transform.rotation[0] );
		ImGui::DragFloat3( "Scale", &m_transform.scale[0] );
		ImGui::End();


		m_transform.rotation.z -= dt * ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_E ) ? m_speed * dt * 45 : 0;
		m_transform.rotation.z += dt * ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_Q ) ? m_speed * dt * 45 : 0;
		
		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_A ) ? m_speed * dt : 0;
		m_transform.position.x -= ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_D ) ? m_speed * dt : 0;

		m_transform.position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_LSHIFT ) ? m_speed * dt : 0;
		m_transform.position.y -= ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_LCTRL ) ? m_speed * dt : 0;

		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_W ) ? m_speed * dt : 0;
		m_transform.position.z -= ENGINE.GetSystem<InputSystem>()->GetKeyDown( SDL_SCANCODE_S ) ? m_speed * dt : 0;

		m_time += dt;

		m_material->Bind();
		m_material->ProcessGui();

		m_material->GetProgram()->SetUniform("model", m_transform.GetMatrix());

		glm::mat4 view = glm::lookAt( glm::vec3( 0, 4, -5 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );
		m_material->GetProgram()->SetUniform( "view", view );

		glm::mat4 projection = glm::perspective( glm::radians( 70.0f ), (float) ENGINE.GetSystem<nc::Renderer>()->GetWidth() / ENGINE.GetSystem<nc::Renderer>()->GetHeight(), 0.01f, 100.0f);
		m_material->GetProgram()->SetUniform( "projection", projection );

		ENGINE.GetSystem<Gui>()->EndFrame();

	}

	void World03::Draw( Renderer& renderer ) {

		// pre-render
		renderer.BeginFrame();

		// render
		
		m_vertexBuffer->Draw( GL_TRIANGLE_STRIP );
		ENGINE.GetSystem<Gui>()->Draw();

		// post-render
		renderer.EndFrame();

	}

}
