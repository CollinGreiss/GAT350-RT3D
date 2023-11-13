#include "World06.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtx/color_space.hpp>

namespace nc {


	bool World06::Initialize() {

		m_scene = std::make_unique<Scene>();
		m_scene->Load( "json/scene06.json" );
		m_scene->Initialize();

		auto texture = std::make_shared<Texture>();
		texture->CreateTexture(1024, 1024);
		ADD_RESOURCE("fb_texture", texture);

		auto framebuffer = std::make_shared<Framebuffer>();
		framebuffer->CreateFramebuffer(texture);
		ADD_RESOURCE("fb", framebuffer);

		auto material = GET_RESOURCE(Material, "materials/postprocess.mtrl");
		if (material) {

			material->albedoTexture = GET_RESOURCE(Texture, "fb_texture");

		}

		return true;

	}

	void World06::Shutdown() {

	}

	void World06::Update( float dt ) {

		ENGINE.GetSystem<Gui>()->BeginFrame();

		m_scene->Update( dt );
		m_scene->ProcessGui();


		ImGui::Begin("Post Process");

		ImGui::SliderFloat("Blend", &blend, 0, 1);
		ImGui::SliderFloat3("Color Tint", glm::value_ptr(tint), 0, 1);

		bool effect = params & INVERT_MASK;
		if (ImGui::Checkbox("Invert", &effect))
			if (effect) params |= INVERT_MASK;
			else params ^= INVERT_MASK;

		effect = params & GREYSCALE_MASK;
		if (ImGui::Checkbox("Grey Scale", &effect))
			if (effect) params |= GREYSCALE_MASK;
			else params ^= GREYSCALE_MASK;

		effect = params & COLORTINT_MASK;
		if (ImGui::Checkbox("Color Tint", &effect))
			if (effect) params |= COLORTINT_MASK;
			else params ^= COLORTINT_MASK;

		ImGui::End();

		auto program = GET_RESOURCE(Program, "shaders/postprocess.prog");
		if (program) {

			program->Use();
			program->SetUniform("blend", blend);
			program->SetUniform("tint", tint);
			program->SetUniform("params", params);

		}

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
