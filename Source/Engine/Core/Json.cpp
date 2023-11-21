#include "Json.h"

#include "FileIO.h"

#include <rapidjson/include/rapidjson/istreamwrapper.h>
#include <sstream>

#include <rapidjson/include/rapidjson/writer.h>
#include <rapidjson/include/rapidjson/stringbuffer.h>

namespace nc {

	bool Json::Load( const std::string& filename, rapidjson::Document& document ) {

		std::string buffer;

		if ( !readFile( filename, buffer ) ) {

			WARNING_LOG( "Cannot open file: " << filename );
			return false;

		}

		std::stringstream stream( buffer );
		rapidjson::IStreamWrapper istream( stream );

		// parse stream to json
		document.ParseStream( istream );

		if ( !document.IsObject() ) {

			WARNING_LOG( "Json file cannot be parsed: " << filename );
			return false;

		}

		return true;

	}

	bool Json::Read( const rapidjson::Value& value, const std::string& name, int& data, bool required ) {

		if ( !value.HasMember( name.c_str() ) || !value[name.c_str()].IsInt() ) {

			if ( required ) ERROR_LOG( "Cannot read required json data: " << name.c_str() );
			return false;

		}

		data = value[name.c_str()].GetInt();

		return true;

	}

	bool Json::Read( const rapidjson::Value& value, const std::string& name, float& data, bool required ) {

		if ( !value.HasMember( name.c_str() ) || !value[name.c_str()].IsNumber() ) {

			if ( required ) ERROR_LOG( "Cannot read required json data: " << name.c_str() );
			return false;

		}

		data = value[name.c_str()].GetFloat();

		return true;

	}

	bool Json::Read( const rapidjson::Value& value, const std::string& name, bool& data, bool required ) {

		if ( !value.HasMember( name.c_str() ) || !value[name.c_str()].IsBool() ) {

			if ( required ) ERROR_LOG( "Cannot read required json data: " << name.c_str() );
			return false;

		}

		data = value[name.c_str()].GetBool();

		return true;

	}

	bool Json::Read( const rapidjson::Value& value, const std::string& name, std::string& data, bool required ) {

		if ( !value.HasMember( name.c_str() ) || !value[name.c_str()].IsString() ) {

			if ( required ) ERROR_LOG( "Cannot read required json data: " << name.c_str() );
			return false;

		}

		data = value[name.c_str()].GetString();

		return true;

	}

	bool Json::Read( const rapidjson::Value& value, const std::string& name, glm::vec2& data, bool required ) {

		if ( !value.HasMember( name.c_str() ) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2 ) {

			if ( required ) ERROR_LOG( "Cannot read required json data: " << name.c_str() );
			return false;

		}

		auto& array = value[name.c_str()];

		for ( rapidjson::SizeType i = 0; i < array.Size(); i++ ) {

			if ( !array[i].IsNumber() ) {

				ERROR_LOG( "Invalid json data type: " << name.c_str() );
				return false;

			}

			data[i] = array[i].GetFloat();

		}

		return true;

	}

	bool Json::Read( const rapidjson::Value& value, const std::string& name, glm::vec3& data, bool required ) {
		
		if ( !value.HasMember( name.c_str() ) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 3 ) {

			if ( required ) ERROR_LOG( "Cannot read required json data: " << name.c_str() );
			return false;

		}

		auto& array = value[name.c_str()];

		for ( rapidjson::SizeType i = 0; i < array.Size(); i++ ) {

			if ( !array[i].IsNumber() ) {

				ERROR_LOG( "Invalid json data type: " << name.c_str() );
				return false;

			}

			data[i] = array[i].GetFloat();

		}

		return true;

	}

	bool Json::Read( const rapidjson::Value& value, const std::string& name, glm::vec4& data, bool required ) {

		if ( !value.HasMember( name.c_str() ) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4 ) {

			if ( required ) ERROR_LOG( "Cannot read required json data: " << name.c_str() );
			return false;

		}

		auto& array = value[name.c_str()];

		for ( rapidjson::SizeType i = 0; i < array.Size(); i++ ) {

			if ( !array[i].IsNumber() ) {

				ERROR_LOG( "Invalid json data type: " << name.c_str() );
				return false;

			}

			data[i] = array[i].GetFloat();

		}

		return true;

	}


	bool Json::Read( const rapidjson::Value& value, const std::string& name, Rect& data, bool required ) {

		if ( !value.HasMember( name.c_str() ) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4 ) {

			if ( required ) ERROR_LOG( "Cannot read required json data: " << name.c_str() );
			return false;

		}

		auto& array = value[name.c_str()];

		for ( rapidjson::SizeType i = 0; i < array.Size(); i++ ) {

			if ( !array[i].IsNumber() ) {

				ERROR_LOG( "Invalid json data type: " << name.c_str() );
				return false;

			}

			data[i] = array[i].GetInt();

		}

		return true;

	}

	bool Json::Read( const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool required ) {

		if ( !value.HasMember( name.c_str() ) || !value[name.c_str()].IsArray() ) {

			if ( required ) ERROR_LOG( "Cannot read required json data: " << name.c_str() );
			return false;

		}

		auto& array = value[name.c_str()];

		for ( rapidjson::SizeType i = 0; i < array.Size(); i++ ) {

			if ( !array[i].IsString() ) {

				ERROR_LOG( "Invalid json data type: " << name.c_str() );
				return false;

			}

			data.push_back( array[i].GetString() );

		}

		return true;

	}

	bool Json::Read( const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool required ) {

		if ( !value.HasMember( name.c_str() ) || !value[name.c_str()].IsArray() ) {

			if ( required ) ERROR_LOG( "Cannot read required json data: " << name.c_str() );
			return false;

		}

		auto& array = value[name.c_str()];

		for ( rapidjson::SizeType i = 0; i < array.Size(); i++ ) {

			if ( !array[i].IsNumber() ) {

				ERROR_LOG( "Invalid json data type: " << name.c_str() );
				return false;

			}

			data.push_back( array[i].GetInt() );

		}

		return true;

	}

	bool Json::Write( rapidjson::Value& value, const std::string& name, float data, const std::string& filename ) {

		if ( !value.HasMember( name.c_str() ) || !value[name.c_str()].IsNumber() ) {

			ERROR_LOG( "Cannot read required json data: " << name.c_str() );
			return false;

		}

		 value[name.c_str()].SetFloat( data ); 

		 rapidjson::StringBuffer buffer;
		 rapidjson::Writer<rapidjson::StringBuffer> writer( buffer );
		 value.Accept( writer );

		 std::ofstream outFile( filename );

		 if ( !outFile.is_open() ) {

			 ERROR_LOG( "Failed to open file for writing: " << filename );
			 return false;

		 }

		 outFile << buffer.GetString();
		 outFile.close();

		return true;

	}

}
