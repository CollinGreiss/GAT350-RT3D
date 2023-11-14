#include "World06.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtx/color_space.hpp>

namespace nc {


	bool World06::Initialize() {

		m_scene = std::make_unique<Scene>();
		m_scene->Load( "json/scene06.json" );
		m_scene->Initialize();

		return true;

	}

	void World06::Shutdown() {

	}

	void World06::Update( float dt ) {

		ENGINE.GetSystem<Gui>()->BeginFrame();

		m_scene->Update( dt );
		m_scene->ProcessGui();

		ENGINE.GetSystem<Gui>()->EndFrame();

	}

	void World06::Draw( Renderer& renderer ) {

		// pre-render

		if (m_scene->GetActorByName("postprocess")->active) {

			m_scene->GetActorByName("postprocess")->active = false;

			auto framebuffer = GET_RESOURCE(Framebuffer, "fb");
			renderer.SetViewport(framebuffer->GetSize().x, framebuffer->GetSize().y);
			framebuffer->Bind();

			renderer.BeginFrame();

			// render

			m_scene->Draw(renderer);

			framebuffer->Unbind();

			m_scene->GetActorByName("postprocess")->active = true;

			renderer.ResetViewport();

		}

		renderer.BeginFrame();

		m_scene->Draw(renderer);

		ENGINE.GetSystem<Gui>()->Draw();

		// post-render
		renderer.EndFrame();

	}

}
