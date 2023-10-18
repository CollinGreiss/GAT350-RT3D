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

		READ_DATA( document, color );
		READ_DATA( document, tiling );
		READ_DATA( document, offset );

		return true;

	}

	void Material::Bind() {

		m_program->Use();
		m_program->SetUniform( "color", color );
		m_program->SetUniform( "tiling", tiling );
		m_program->SetUniform( "offset", offset );

		for ( size_t i = 0; i < m_textures.size(); i++ ) {

			m_textures[i]->SetActive( GL_TEXTURE0 + (int) i );
			m_textures[i]->Bind();

		}

	}

	void Material::ProcessGui() {

		ImGui::Begin( "Material" );

		ImGui::ColorEdit4( "Color", glm::value_ptr( color ) );
		ImGui::DragFloat2( "Tiling", glm::value_ptr( tiling ) );
		ImGui::DragFloat2( "Offset", glm::value_ptr( offset ), 0.001f, -1, 1 );

		ImGui::End();

	}

}