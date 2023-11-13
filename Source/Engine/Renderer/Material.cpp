#include "Material.h"

#include "Program.h"
#include "Cubemap.h"
#include "Core/Core.h"

namespace nc {

	bool Material::Create( std::string filename, ... ) {

		rapidjson::Document document;

		bool success = Json::Load( filename, document );
		if ( !success ) {

			INFO_LOG( "Could not load program file (%s)." << filename );
			return false;

		}

		std::string program;
		READ_DATA( document, program );

		m_program = GET_RESOURCE( Program, program );

		std::string albedoTextureName;
		if ( READ_NAME_DATA( document, "albedoTexture", albedoTextureName ) ) {

			params |= ALBEDO_TEXTUE_MASK;
			albedoTexture = GET_RESOURCE( Texture, albedoTextureName );

		}

		std::string specularTextureName;
		if ( READ_NAME_DATA( document, "specularTexture", specularTextureName ) ) {

			params |= SPECULAR_TEXTUE_MASK;
			specularTexture = GET_RESOURCE( Texture, specularTextureName );

		}

		std::string emissiveTextureName;
		if ( READ_NAME_DATA( document, "emissiveTexture", emissiveTextureName ) ) {

			params |= EMISSIVE_TEXTUE_MASK;
			emissiveTexture = GET_RESOURCE( Texture, emissiveTextureName );

		}

		std::string normalTextureName;
		if ( READ_NAME_DATA( document, "normalTexture", normalTextureName ) ) {

			params |= NORMAL_TEXTUE_MASK;
			normalTexture = GET_RESOURCE( Texture, normalTextureName );

		}

		std::string cubemapName;
		if ( READ_NAME_DATA( document, "cubemap", cubemapName ) ) {

			params |= CUBMAP_TEXTUE_MASK;
			std::vector<std::string> cubemaps;
			READ_DATA( document, cubemaps );

			cubmapTexture = GET_RESOURCE( Cubemap, cubemapName, cubemaps);

		}

		READ_DATA( document, albedo );
		READ_DATA( document, specular );
		READ_DATA( document, emissive );
		READ_DATA( document, shininess );
		READ_DATA( document, tiling );
		READ_DATA( document, offset );

		return true;

	}

	void Material::Bind() {

		m_program->Use();

		m_program->SetUniform( "material.params", params );

		m_program->SetUniform( "material.albedo", albedo );
		m_program->SetUniform( "material.emissive", emissive );
		m_program->SetUniform( "material.specular", specular );
		m_program->SetUniform( "material.shininess", shininess );

		m_program->SetUniform( "material.tiling", tiling );
		m_program->SetUniform( "material.offset", offset );

		if ( albedoTexture ) {

			albedoTexture->SetActive( GL_TEXTURE0 );
			albedoTexture->Bind();

		}

		if ( specularTexture ) {

			specularTexture->SetActive( GL_TEXTURE1 );
			specularTexture->Bind();

		}

		if ( normalTexture ) {

			normalTexture->SetActive( GL_TEXTURE2 );
			normalTexture->Bind();

		}

		if ( emissiveTexture ) {

			emissiveTexture->SetActive( GL_TEXTURE3 );
			emissiveTexture->Bind();

		}

	}

	void Material::ProcessGui() {

		ImGui::TextColored( { 1, 1, 1, 1 }, "Material" );

		ImGui::ColorEdit3( "Albedo", glm::value_ptr( albedo ) );
		ImGui::ColorEdit3( "Emissive", glm::value_ptr( emissive ) );
		ImGui::ColorEdit3( "Specular", glm::value_ptr( specular ) );
		ImGui::DragFloat( "Shininess", &shininess, 0.1f, 2.0f, 200.0f );

		ImGui::DragFloat2( "Tiling", glm::value_ptr( tiling ) );
		ImGui::DragFloat2( "Offset", glm::value_ptr( offset ), 0.001f, -1, 1 );

	}

}