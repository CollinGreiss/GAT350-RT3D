#include "World08.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include <glm/glm/gtx/color_space.hpp>

namespace nc {

	bool World08::Initialize() {

		m_scene = std::make_unique<Scene>();
		m_scene->Load( "json/scene_editor.json" );
		m_scene->Load( "json/scene_shadow.json" );
		m_scene->Initialize();

		m_editor = std::make_shared<Editor>();

		auto texture = std::make_shared<Texture>();
		texture->CreateDepthTexture( 1024, 1024 );
		ADD_RESOURCE( "depth_texture", texture );

		auto framebuffer = std::make_shared<Framebuffer>();
		framebuffer->CreateDepthbuffer( texture );
		ADD_RESOURCE( "depth_buffer", framebuffer );

		auto material = GET_RESOURCE( Material, "materials/sprite.mtrl" );
		if ( material )
			material->albedoTexture = GET_RESOURCE( Texture, "depth_texture" );

		auto materials = GET_RESOURCES( Material );
		for ( auto& material : materials )
			material->depthTexture = texture;

		return true;
	}

	void World08::Shutdown() {}

	void World08::Update( float dt ) {


		ENGINE.GetSystem<Gui>()->BeginFrame();

		m_scene->Update( dt );
		m_editor->Update();

		m_editor->ProcessGui(m_scene.get());

		ImGui::Begin( "CEL Shading" );

		ImGui::SliderInt( "Levels", &celLevels, 1, 10 );
		ImGui::SliderFloat( "Specular Cutoff", &celSpecularCutoff, 0, 10 );
		ImGui::SliderFloat( "Outline", &celOutline, 0, 10 );

		ImGui::End();

		auto program = GET_RESOURCE( Program, "shaders/lit_phong_cel.prog" );
		program->Use();

		program->SetUniform( "celLevels", celLevels );
		program->SetUniform( "celSpecularCutoff", celSpecularCutoff );
		program->SetUniform( "celOutline", celOutline );

		ENGINE.GetSystem<Gui>()->EndFrame();
	}

	void World08::Draw( Renderer& renderer ) {
		// *** PASS 1 ***

		auto framebuffer = GET_RESOURCE( Framebuffer, "depth_buffer" );
		renderer.SetViewport( framebuffer->GetSize().x, framebuffer->GetSize().y );
		framebuffer->Bind();

		renderer.ClearDepth();
		auto program = GET_RESOURCE( Program, "shaders/shadow_depth.prog" );
		program->Use();

		auto lights = m_scene->GetComponents<LightComponent>();
		for ( auto light : lights ) {

			if ( light->castShadow ) {

				glm::mat4 shadowMatrix = light->GetShadowMatrix();
				program->SetUniform( "shadowVP", shadowMatrix );

			}

		}

		auto models = m_scene->GetComponents<ModelComponent>();
		for ( auto model : models ) {

			if ( model->castShadow ) {

				glCullFace( GL_FRONT );
				program->SetUniform( "model", model->m_owner->transform.GetMatrix() );
				model->model->Draw();

			}

		}

		framebuffer->Unbind();

		// *** PASS 2 ***

		renderer.ResetViewport();
		renderer.BeginFrame();
		m_scene->Draw( renderer );

		ENGINE.GetSystem<Gui>()->Draw();
		renderer.EndFrame();

	}

}