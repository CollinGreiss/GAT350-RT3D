#include "Material.h"
#include "Program.h"
#include "Texture.h"
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

		std::vector<std::string> textures;
		READ_DATA( document, textures );

		for ( auto texture : textures )
			m_textures.push_back( GET_RESOURCE( Texture, texture ) );

		READ_DATA( document, diffuse );
		READ_DATA( document, specular );
		READ_DATA( document, shininess );
		READ_DATA( document, tiling );
		READ_DATA( document, offset );

		return true;

	}

	void Material::Bind() {

		m_program->Use();
		m_program->SetUniform( "material.diffuse", diffuse );
		m_program->SetUniform( "material.specular", specular );
		m_program->SetUniform( "material.shininess", shininess );

		m_program->SetUniform( "material.tiling", tiling );
		m_program->SetUniform( "material.offset", offset );

		for ( size_t i = 0; i < m_textures.size(); i++ ) {

			m_textures[i]->SetActive( GL_TEXTURE0 + (int) i );
			m_textures[i]->Bind();

		}

	}

	void Material::ProcessGui() {

		ImGui::Begin( "Material" );

		ImGui::ColorEdit3( "Diffuse", glm::value_ptr( diffuse ) );
		ImGui::ColorEdit3( "Specular", glm::value_ptr( specular ) );
		ImGui::DragFloat( "Shininess", &shininess, 0.1f, 2.0f, 200.0f );

		ImGui::DragFloat2( "Tiling", glm::value_ptr( tiling ) );
		ImGui::DragFloat2( "Offset", glm::value_ptr( offset ), 0.001f, -1, 1 );

		ImGui::End();

	}

}