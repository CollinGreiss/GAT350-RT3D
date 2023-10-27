#include "World05.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtx/color_space.hpp>

namespace nc {


	bool World05::Initialize() {

		m_scene = std::make_unique<Scene>();
		m_scene->Load("json/scene.json");
		m_scene->Initialize();

		/*{
			auto actor = CREATE_CLASS( Actor );
			actor->name = "actor1";
			actor->transform.position = glm::vec3 { 0, 0, 0 };
			auto modelComponent = CREATE_CLASS( ModelComponent );
			modelComponent->model = std::make_shared<Model>();
			modelComponent->model->SetMaterial( GET_RESOURCE( Material, "materials/squirrel.mtrl" ) );
			modelComponent->model->Load( "models/squirrel.glb", glm::vec3 { 0, -0.7f, 0 }, glm::vec3 { 0 }, glm::vec3 { 0.4f } );
			actor->AddComponent( std::move( modelComponent ) );
			m_scene->Add( std::move( actor ) );
		}*/

		{
			auto actor = CREATE_CLASS( Actor );
			actor->name = "light1";
			actor->transform.position = glm::vec3 { 3, 3, 3 };
			auto lightComponent = CREATE_CLASS( LightComponent );
			lightComponent->type = LightComponent::eType::Point;
			lightComponent->color = glm::rgbColor( glm::vec3 { randomf() * 360, 1, 1 } );
			lightComponent->intensity = 1;
			lightComponent->range = 20;
			lightComponent->innerAngle = 10.0f;
			lightComponent->outerAngle = 30.0f;
			actor->AddComponent( std::move( lightComponent ) );
			m_scene->Add( std::move( actor ) );
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

		m_scene->Draw(renderer);
		ENGINE.GetSystem<Gui>()->Draw();

		// post-render
		renderer.EndFrame();

	}

}
