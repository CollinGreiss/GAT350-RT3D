#include "World07.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtx/color_space.hpp>

namespace nc {


	bool World07::Initialize() {

		m_scene = std::make_unique<Scene>();
		m_scene->Load( "json/scene_shadow.json" );
		m_scene->Initialize();

		return true;

	}

	void World07::Shutdown() {

	}

	void World07::Update( float dt ) {

		ENGINE.GetSystem<Gui>()->BeginFrame();

		

		m_scene->Update( dt );
		m_scene->ProcessGui();

		ENGINE.GetSystem<Gui>()->EndFrame();

	}

	void World07::Draw( Renderer& renderer ) {

		// pre-render

		renderer.BeginFrame();

		m_scene->Draw(renderer);

		ENGINE.GetSystem<Gui>()->Draw();

		// post-render
		renderer.EndFrame();

	}

}
