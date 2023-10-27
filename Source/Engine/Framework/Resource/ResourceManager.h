#pragma once

#include "Core/Logger.h"
#include "Resource.h"
#include "Framework/Singleton.h"
#include <map>
#include <memory>
#include <vector>
#include <string>

#define GET_RESOURCE(type, filename, ...) nc::ResourceManager::Instance().Get<type>(filename, __VA_ARGS__)

namespace nc {

	class ResourceManager : public Singleton<ResourceManager> {

	public:

		template<typename T, typename ... TArgs>
		res_t<T> Get( const std::string& filename, TArgs ... args );

		template<typename T>
		std::vector<res_t<T>> GetAllOfType();

	private:

		std::map<std::string, res_t<Resource>> m_resources;

	};

	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get( const std::string& filename, TArgs ...args ) {

		if ( m_resources.find( filename ) != m_resources.end() )
			return std::dynamic_pointer_cast<T>( m_resources[filename] );

		res_t<T> resource = std::make_shared<T>();
		if ( !resource->Create( filename, args... ) ) {

			WARNING_LOG( "Could not create resource: " << filename );
			return res_t<T>();
		}

		m_resources[filename] = resource;
		return resource;
	}

	template<typename T>
	inline std::vector<res_t<T>> ResourceManager::GetAllOfType() {

		std::vector<res_t<T>> result;

		for ( auto& resource : m_resources ) {
			auto res = std::dynamic_pointer_cast<T>( resource.second );
			if ( res ) result.push_back( res );

		}

		return result;

	}

}