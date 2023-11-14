#include "PostProcessComponent.h"

#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Framework/Resource/ResourceManager.h"

namespace nc {

	CLASS_DEFINITION(PostProcessComponent)

		bool PostProcessComponent::Initialize() {

		m_program = GET_RESOURCE(Program, "shaders/postprocess.prog");

		auto texture = std::make_shared<Texture>();
		texture->CreateTexture(1024, 1024);
		ADD_RESOURCE("fb_texture", texture);

		auto framebuffer = std::make_shared<Framebuffer>();
		framebuffer->CreateFramebuffer(texture);
		ADD_RESOURCE("fb", framebuffer);

		auto material = GET_RESOURCE(Material, "materials/postprocess.mtrl");
		if (material) material->albedoTexture = GET_RESOURCE(Texture, "fb_texture");

		return true;

	}

	void PostProcessComponent::Update(float dt) {

		m_time += dt;

		if (m_program) {

			m_program->Use();
			m_program->SetUniform("blend", blend);
			m_program->SetUniform("tint", tint);
			m_program->SetUniform("params", params);
			m_program->SetUniform("time", m_time);
			m_program->SetUniform("lineSpace", lineSpace);

		}

	}

	void PostProcessComponent::Draw(Renderer& renderer) {

		if (!m_owner->active) return;

		m_owner->active = false;

		auto framebuffer = GET_RESOURCE(Framebuffer, "fb");
		renderer.SetViewport(framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();

		renderer.BeginFrame();

		// render

		m_owner->m_scene->Draw(renderer);

		framebuffer->Unbind();

		m_owner->active = true;

		renderer.ResetViewport();

	}

	void PostProcessComponent::ProcessGui() {

		ImGui::SliderFloat("Blend", &blend, 0, 1);

		bool effect = params & INVERT_MASK;
		if (ImGui::Checkbox("Invert", &effect))
			if (effect) params |= INVERT_MASK;
			else params &= ~INVERT_MASK;

		effect = params & GREYSCALE_MASK;
		if (ImGui::Checkbox("Grey Scale", &effect))
			if (effect) params |= GREYSCALE_MASK;
			else params &= ~GREYSCALE_MASK;

		effect = params & COLORTINT_MASK;
		if (ImGui::Checkbox("Color Tint", &effect))
			if (effect) params |= COLORTINT_MASK;
			else params &= ~COLORTINT_MASK;

		ImGui::SliderFloat3("Color Tint", glm::value_ptr(tint), 0, 1);

		effect = params & GRAIN_MASK;
		if (ImGui::Checkbox("Grain", &effect))
			if (effect) params |= GRAIN_MASK;
			else params &= ~GRAIN_MASK;

		effect = params & SCANLINE_MASK;
		if (ImGui::Checkbox("Scanline", &effect))
			if (effect) params |= SCANLINE_MASK;
			else params &= ~SCANLINE_MASK;

		ImGui::SliderInt("Scanline Spacing", &lineSpace, 2, 10);

		effect = params & GAMER_MASK;
		if (ImGui::Checkbox("Gamer", &effect))
			if (effect) params |= GAMER_MASK;
			else params &= ~GAMER_MASK;

	}

	void PostProcessComponent::Read(const nc::json_t& value) {

		READ_DATA(value, blend);
		READ_DATA(value, tint);
		READ_DATA(value, lineSpace);

		bool active = false;
		READ_NAME_DATA(value, "invert", active);
		if (active) params |= INVERT_MASK;

		active = false;
		READ_NAME_DATA(value, "greyscale", active);
		if (active) params |= GREYSCALE_MASK;

		active = false;
		READ_NAME_DATA(value, "colortint", active);
		if (active) params |= COLORTINT_MASK;

		active = false;
		READ_NAME_DATA(value, "grain", active);
		if (active) params |= GRAIN_MASK;

		active = false;
		READ_NAME_DATA(value, "scanline", active);
		if (active) params |= SCANLINE_MASK;

		active = false;
		READ_NAME_DATA(value, "gamer", active);
		if (active) params |= GAMER_MASK;


	}

}