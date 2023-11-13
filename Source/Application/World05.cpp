#include "World05.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtx/color_space.hpp>

namespace nc {


	bool World05::Initialize() {

		m_scene = std::make_unique<Scene>();
		m_scene->Load( "json/scene.json" );
		m_scene->Initialize();

		for ( int i = 0; i < 15; i++ ) {

			auto actor = CREATE_CLASS_BASE( Actor, "tree" );
			actor->transform.position = glm::vec3( randomf(-10, 10), 0, randomf( -10, 10 ) );
			actor->Initialize();
			m_scene->Add( std::move( actor) );

		}

		return true;

	}

	void World05::Shutdown() {

	}

	void World05::Update( float dt ) {

		ENGINE.GetSystem<Gui>()->BeginFrame();

		m_scene->Update( dt );
		m_scene->ProcessGui();

		ENGINE.GetSystem<Gui>()->EndFrame();

	}

	void World05::Draw( Renderer& renderer ) {

		// pre-render
		renderer.BeginFrame();

		// render

		m_scene->Draw( renderer );
		ENGINE.GetSystem<Gui>()->Draw();

		// post-render
		renderer.EndFrame();

	}

}
